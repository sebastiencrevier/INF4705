import random
from algos import insertion_sort


class Quicksort(object):
    def __init__(self, random_pivot=False, threshold=None):
        self.random_pivot = random_pivot
        self.threshold = threshold

    def sort(self, arr):
        less = []
        pivotList = []
        more = []
        if len(arr) <= 1:
            return arr
        else:
            pivot = random.choice(arr) if self.random_pivot else arr[0]

            # TODO : Find optimal threshold
            if self.threshold and (len(arr) - pivot) < self.threshold:
                insertion_sort(arr)

            for i in arr:
                if i < pivot:
                    less.append(i)
                elif i > pivot:
                    more.append(i)
                else:
                    pivotList.append(i)
            less = self.sort(less)
            more = self.sort(more)

            return less + pivotList + more
