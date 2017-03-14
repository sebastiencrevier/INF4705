import time
import vorace
import sys


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

    if a == 'vorace':
        max_val = max(array)
        compute_time = compute(lambda: vorace.vorace(array, max_val), p, t)

    elif a == 'dynamique':
        compute_time = compute(lambda: vorace.dynamique(array, max_val), p, t)

    elif a == 'retourArriere':
        compute_time = compute(lambda: vorace.retourArriere(array, max_val), p, t)

    else:
        return 0

    return compute_time
