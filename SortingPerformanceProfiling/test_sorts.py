import random
import sys
from instrumentation import Instrumentation
from bubble_sort import BubbleSort
from quick_sort import QuickSort

ins = Instrumentation.Instance()

SIZES = [1000, 5000, 10000]
RUNS = 5


class TestSorts:

    def __init__(self, instrumented):
        self.instrumented = instrumented

    def populateArray(self, size, almostSorted):
        name = "populateArray n=%d" % size
        ins.startTiming(name)
        # seeded with the size so every run and both sorts get the same numbers
        rng = random.Random(size)
        arr = [rng.randint(1, 99999) for i in range(size)]
        if almostSorted:
            arr.sort()
            # swap 1% of the elements to random spots
            for i in range(size // 100):
                a = rng.randrange(size)
                b = rng.randrange(size)
                arr[a], arr[b] = arr[b], arr[a]
        ins.stopTiming(name)
        return arr

    def runBubbleSort(self, arr, label):
        ins.startTiming("runBubbleSort " + label)
        BubbleSort(self.instrumented).bubbleSort(arr)
        ins.stopTiming("runBubbleSort " + label)

    def runQuickSort(self, arr, label):
        ins.startTiming("runQuickSort " + label)
        QuickSort(self.instrumented).quickSort(arr, 0, len(arr) - 1)
        ins.stopTiming("runQuickSort " + label)


def main():
    mode = sys.argv[1]
    test = TestSorts(mode == "instrumented")

    ins.activate(True)
    ins.startTiming("main")
    for size in SIZES:
        for almostSorted in [False, True]:
            label = "n=%d %s" % (size, "almost-sorted" if almostSorted else "random")
            for run in range(RUNS):
                arr = test.populateArray(size, almostSorted)
                test.runBubbleSort(arr.copy(), label)
                test.runQuickSort(arr.copy(), label)
                print(label, "run", run + 1, "done")
    ins.stopTiming("main")
    ins.dump("logs/sorts_" + mode + ".log")


if __name__ == "__main__":
    main()
