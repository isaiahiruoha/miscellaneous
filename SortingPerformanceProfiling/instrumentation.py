import time
from datetime import datetime

class Instrumentation:
    _instance = None

    def __init__(self):
        # only Instance() should create this
        if Instrumentation._instance is not None:
            raise Exception("Instrumentation is a singleton, use Instrumentation.Instance()")
        self.active = False
        self.stack = []
        self.lines = []
        self.total = 0

    @staticmethod
    def Instance():
        if Instrumentation._instance is None:
            Instrumentation._instance = Instrumentation()
        return Instrumentation._instance

    def activate(self, onoff):
        self.active = onoff

    def startTiming(self, comment):
        if not self.active:
            return
        self.lines.append("| " * len(self.stack) + "STARTTIMING: " + comment)
        self.stack.append(time.perf_counter_ns())

    def stopTiming(self, comment):
        if not self.active:
            return
        end = time.perf_counter_ns()
        elapsed = end - self.stack.pop()
        if len(self.stack) == 0:
            self.total += elapsed
        ms = elapsed / 1000000
        self.lines.append("| " * len(self.stack) + "STOPTIMING: " + comment + " %.4fms" % ms)

    def comment(self, comment):
        if not self.active:
            return
        self.lines.append("| " * len(self.stack) + "COMMENT: " + comment)

    def dump(self, filename=None):
        if not self.active:
            return
        if filename is None:
            filename = "instrumentation" + datetime.now().strftime("%d%y%m%H%M%S") + ".log"
        # lines are kept in memory until now so writing the file doesn't add to the timings
        f = open(filename, "w")
        for line in self.lines:
            f.write(line + "\n")
        f.write("TOTAL TIME: %.4fms\n" % (self.total / 1000000))
        f.close()
