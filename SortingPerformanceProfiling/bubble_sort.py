from instrumentation import Instrumentation

ins = Instrumentation.Instance()


# adapted from https://www.geeksforgeeks.org/bubble-sort/
class BubbleSort:

    def __init__(self, instrumented=False):
        self.instrumented = instrumented

    def bubbleSort(self, arr):
        n = len(arr)
        for i in range(n):
            if self.instrumented:
                ins.startTiming("pass")
            swapped = False

            # last i elements are already in place
            for j in range(0, n - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    swapped = True

            if self.instrumented:
                ins.stopTiming("pass")
            if not swapped:
                break
