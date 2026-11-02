import heapq, itertools

class OrderBook:
    def __init__(self):
        self.bids, self.asks = [], []      # (-price|price, ts, order_id, qty)
        self.clock = itertools.count()
        self.status = {}                   # id -> OPEN | FILLED | CANCELLED | PENDING
        self.stops = []                    # pending stop orders, in arrival order
        self.last_price = None             # price of the most recent trade

    # ---------- helpers ----------
    def _clean(self, book):                # lazy deletion: only check the top
        while book and self.status.get(book[0][2]) != "OPEN":
            heapq.heappop(book)

    def best_bid(self):
        self._clean(self.bids)
        return -self.bids[0][0] if self.bids else None

    def best_ask(self):
        self._clean(self.asks)
        return self.asks[0][0] if self.asks else None

    def cancel(self, order_id):
        if self.status.get(order_id) in ("OPEN", "PENDING"):
            self.status[order_id] = "CANCELLED"
            return True
        return False

    # ---------- public entry ----------
    def submit(self, order_id, side, qty, price=None, stop=None):
        if stop is not None:                      # park it; don't touch the book
            self.stops.append((order_id, side, qty, price, stop))
            self.status[order_id] = "PENDING"
            return self._run_stops()              # triggers now if already crossed
        trades = self._execute(order_id, side, qty, price)
        return trades + self._run_stops()

    # ---------- stop handling ----------
    def _triggered(self, side, stop):
        if self.last_price is None:
            return False
        return self.last_price >= stop if side == "BUY" else self.last_price <= stop

    def _run_stops(self):
        trades = []
        fired = True
        while fired:                              # repeat until nothing triggers
            fired = False
            for s in list(self.stops):            # copy, because we remove while looping
                oid, side, qty, price, stop = s
                if self.status.get(oid) != "PENDING":     # cancelled: drop it
                    self.stops.remove(s)
                    continue
                if self._triggered(side, stop):
                    self.stops.remove(s)
                    trades += self._execute(oid, side, qty, price)  # may move last_price
                    fired = True
                    break                         # restart scan in arrival order
        return trades

    # ---------- matching (Parts 1-3, one copy for both sides) ----------
    def _execute(self, order_id, side, qty, price):
        trades = []
        if side == "BUY":
            book, opp, best = self.bids, self.asks, self.best_ask
            crosses = lambda p: price is None or p <= price
        else:
            book, opp, best = self.asks, self.bids, self.best_bid
            crosses = lambda p: price is None or p >= price

        while qty > 0 and (p := best()) is not None and crosses(p):
            key, ts, r_id, r_qty = heapq.heappop(opp)
            fill = min(qty, r_qty)
            trades.append((order_id, r_id, p, fill) if side == "BUY" else (r_id, order_id, p, fill))
            self.last_price = p
            qty -= fill
            if r_qty > fill:                      # partial: keep original ts/priority
                heapq.heappush(opp, (key, ts, r_id, r_qty - fill))
            else:
                self.status[r_id] = "FILLED"

        if price is not None and qty > 0:         # rest the limit remainder
            key = -price if side == "BUY" else price
            heapq.heappush(book, (key, next(self.clock), order_id, qty))
            self.status[order_id] = "OPEN"
        else:                                     # filled, or market remainder dropped
            self.status[order_id] = "FILLED"
        return trades
    
ob = OrderBook()
ob.submit(1, "BUY", 5, 100.0)            -> []
ob.submit(2, "BUY", 5, 98.0)             -> []
ob.submit(10, "SELL", 5, None, stop=99.0) -> []     # waits
ob.submit(11, "SELL", 5, None, stop=98.0) -> []     # waits
ob.submit(3, "SELL", 5, 100.0)           -> [(1, 3, 100.0, 5)]   # last = 100, no trigger
ob.submit(4, "BUY", 2, 99.0)             -> []                    # rests at 99
ob.submit(5, "SELL", 2, 99.0)            -> [(4, 5, 99.0, 2), (2, 10, 98.0, 5)]
  # trade at 99 triggers stop 10 (99 <= 99), which sells into the 98 bid,
  # which makes last = 98 and triggers stop 11; no bids left, so 11 does nothing
