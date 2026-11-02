class KacRing:
    def __init__(self, n, marked):
        self.n = n
        self.period = 2 * n
        is_marked = [0] * n
        for p in marked:
            is_marked[p] = 1

        # precompute (W - B) / N for every time t in one full period: O(N^2)
        balls = [0] * n                 # 0 = white, 1 = black; all white at start
        self.table = []
        for _ in range(self.period):
            black = sum(balls)
            self.table.append(str(Fraction(n - 2 * black, n)))
            new = [0] * n
            for i in range(n):
                color = balls[i]
                if is_marked[i]:
                    color = 1 - color
                new[(i + 1) % n] = color
            balls = new

        self.t = 0                       # current time, kept mod period

    def step(self):
        self.t = (self.t + 1) % self.period

    def kstep(self, k):
        self.t = (self.t + k) % self.period

    def color(self):
        return self.table[self.t]


def solution(N, marked, operations):
    ring = KacRing(N, marked)
    out = []
    for op in operations:
        if op[0] == "step":
            ring.step()
        elif op[0] == "kstep":
            ring.kstep(op[1])
        else:
            out.append(ring.color())
    return out
