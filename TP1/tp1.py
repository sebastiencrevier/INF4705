import time
import algos
import sys
from quicksort import Quicksort


def read(file):
    with open(file) as f:
        content = f.readlines()
    content = [int(x.strip()) for x in content]
    return content


def compute(a, p, t):
    start_time = time.perf_counter()
    arr = a()
    end_time = time.perf_counter()
    compute_time = end_time - start_time

    if p:
        for el in arr:
            print(el)

    if t:
        print("%s" % compute_time)

    return compute_time


def main(file, a, t, p):
    sys.setrecursionlimit(500000)
    array = read(file)

    if a == 'counting_sort':
        max_val = max(array)
        compute_time = compute(lambda: algos.counting_sort(array, max_val), p, t)

    elif a.startswith('quicksort'):
        qs_type = a.replace('quicksort_', '')

        if qs_type == 'fp':
            qs = Quicksort()
        elif qs_type == 'rp':
            qs = Quicksort(True)
        elif qs_type == 'fp_t':
            qs = Quicksort(False, 10)
        elif qs_type == 'rp_t':
            qs = Quicksort(True, 10)
        else:
            raise ValueError('Wrong quicksort type')

        compute_time = compute(lambda: qs.sort(array, 0, len(array) - 1), p, t)

    else:
        return 0

    return compute_time
