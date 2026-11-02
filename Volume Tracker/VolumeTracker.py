from collections import deque, defaultdict
import heapq

class MarketVolume:
    def __init__(self, window=60):
        self.window = window 
        self.dict = defaultdict(lambda: [0, deque()])
        
    def record_trade(self, symbol, timestamp, qty):
        # add to the queue and the total then evict old trades
        self.dict[symbol][0] += qty
        self.dict[symbol][1].append((timestamp, qty))
        self._evict(symbol, timestamp)
        return 
    
    def get_volume(self, symbol, timestamp):
        if symbol not in self.dict:
            return 0
        self._evict(symbol, timestamp)
        return self.dict[symbol][0]
        
    def _evict(self, symbol, now):
        # while the oldest trade is out of the window pop it and subtract its qty 
        queue = self.dict[symbol][1]
        while queue and queue[0][0] <= now - self.window:
            _, qty = queue.popleft()
            self.dict[symbol][0] -= qty 
        return 

    def top_k(self, timestamp, k):
        items = []
        for symbol in self.dict:
            vol = self.get_volume(symbol, timestamp)
            if vol > 0:
                items.append((-vol, symbol))

        top = heapq.nsmallest(k, items)
        return [symbol for _, symbol in top]
 
class POVExecutor:
    def __init__(self, market, symbol, total_qty, rate):
        self.market = market        # shared MarketVolume, not a copy
        self.symbol = symbol
        self.total_qty = total_qty
        self.rate = rate
        self.filled = 0
        self.last_ts = None         # so on_fill knows when the fill happened

    def on_tick(self, timestamp):
        self.last_ts = timestamp
        vol = self.market.get_volume(self.symbol, timestamp)
        target = int(self.rate * vol)           # 1. how much we *should* have done
        target = min(target, self.total_qty)    # 2. never beyond the parent order
        return max(0, target - self.filled)     # 3. send the gap, never negative

    def on_fill(self, qty):
        self.filled += qty
        self.market.record_trade(self.symbol, self.last_ts, qty)  # our fills are market volume too
    
mv = MarketVolume()
mv.record_trade("AAPL", 0, 100)
mv.record_trade("MSFT", 10, 300)
mv.record_trade("AAPL", 20, 50)
mv.record_trade("GOOG", 30, 150)

print(mv.get_volume("AAPL", 30))   # expect 150
print(mv.get_volume("TSLA", 30))   # expect 0
print(mv.top_k(30, 2))             # expect ['MSFT', 'AAPL']
print(mv.top_k(65, 2))             # expect ['MSFT', 'GOOG']
