from data_reader import read
from arg_parser import parse_arguments
import time
import random


def quickSort(arr):
    less = []
    pivotList = []
    more = []
    if len(arr) <= 1:
        return arr
    else:
        pivot = random.choice(arr)
        for i in arr:
            if i < pivot:
                less.append(i)
            elif i > pivot:
                more.append(i)
            else:
                pivotList.append(i)
        less = quickSort(less)
        more = quickSort(more)
        return less + pivotList + more

ns = parse_arguments()
array = read(ns.file)
start_time = time.perf_counter()
array = quickSort(array)
end_time = time.perf_counter()

if ns.p:
    for el in array:
        print(el)

if ns.t:
    print("%s" % (end_time - start_time))


