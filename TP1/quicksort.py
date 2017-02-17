import random
from algos import insertion_sort


class Quicksort(object):
    def __init__(self, random_pivot=False, threshold=None):
        self.random_pivot = random_pivot
        self.threshold = threshold

    def sort(self, numList, first, last):
        if first < last:
            sizeArr = last - first + 1

            if self.threshold and sizeArr < self.threshold:
                insertion_sort(numList, first, last)
            else:
                mid = self.partition(numList, first, last)
                self.sort(numList, first, mid - 1)
                self.sort(numList, mid + 1, last)

            return numList

    def partition(self, numList, first, last):
        piv = random.choice(numList) if self.random_pivot else numList[first]
        i = first - 1
        for j in range(first, last):
            if numList[j] < piv:
                i += 1
                temp = numList[i]
                numList[i] = numList[j]
                numList[j] = temp

        tempo = numList[i + 1]
        numList[i + 1] = numList[last]
        numList[last] = tempo

        return i + 1
