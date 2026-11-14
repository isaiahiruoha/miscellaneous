from instrumentation import Instrumentation

ins = Instrumentation.Instance()


# adapted from https://www.geeksforgeeks.org/quick-sort/
class QuickSort:

    def __init__(self, instrumented=False):
        self.instrumented = instrumented

    def partition(self, arr, low, high):
        if self.instrumented:
            ins.startTiming("partition")
        pivot = arr[high]
        i = low - 1
        for j in range(low, high):
            if arr[j] < pivot:
                i += 1
                arr[i], arr[j] = arr[j], arr[i]
        arr[i + 1], arr[high] = arr[high], arr[i + 1]
        if self.instrumented:
            ins.stopTiming("partition")
        return i + 1

    def quickSort(self, arr, low, high):
        if low < high:
            pi = self.partition(arr, low, high)
            self.quickSort(arr, low, pi - 1)
            self.quickSort(arr, pi + 1, high)
