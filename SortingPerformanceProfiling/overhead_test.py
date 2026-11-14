import time
import tracemalloc
from instrumentation import Instrumentation

ins = Instrumentation.Instance()
ins.activate(True)

for n in [1000, 10000, 100000]:
    # baseline so the cost of the for loop itself can be subtracted
    ins.startTiming("empty loop n=%d" % n)
    for i in range(n):
        pass
    ins.stopTiming("empty loop n=%d" % n)

    # each start/stop pair reads the clock twice
    ins.startTiming("clock reads n=%d" % n)
    for i in range(n):
        time.perf_counter_ns()
        time.perf_counter_ns()
    ins.stopTiming("clock reads n=%d" % n)

    ins.startTiming("start/stop pairs n=%d" % n)
    for i in range(n):
        ins.startTiming("x")
        ins.stopTiming("x")
    ins.stopTiming("start/stop pairs n=%d" % n)

# memory is measured separately because tracemalloc slows everything down
tracemalloc.start()
before = tracemalloc.get_traced_memory()[0]
for i in range(10000):
    ins.startTiming("x")
    ins.stopTiming("x")
after = tracemalloc.get_traced_memory()[0]
tracemalloc.stop()
print("memory per start/stop pair: %.1f bytes" % ((after - before) / 10000))
print("log lines in memory:", len(ins.lines))

start = time.perf_counter_ns()
ins.dump("logs/overhead.log")
print("dump time: %.2fms" % ((time.perf_counter_ns() - start) / 1000000))
