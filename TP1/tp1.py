import time
import re
import algos
import argparse
from quicksort import Quicksort


def parse_arguments():
    parser = argparse.ArgumentParser()

    parser.add_argument('file')
    parser.add_argument('-a')
    parser.add_argument('-t', action='store_true')
    parser.add_argument('-p', action='store_true')

    namespace = parser.parse_args()
    return namespace


def read(file):
    with open(file) as f:
        content = f.readlines()
    content = [int(x.strip()) for x in content]
    return content


def compute(algo):
    start_time = time.perf_counter()

    array = algo()

    end_time = time.perf_counter()

    if ns.p:
        for el in array:
            print(el)

    if ns.t:
        print("%s" % (end_time - start_time))


def main():
    array = read(ns.file)

    if ns.a == 'counting_sort':
        max_val = int(re.search(r'(.*)_(.*)_(.*)', ns.file, re.M | re.I).group(2))
        compute(lambda: algos.counting_sort(array, max_val))

    elif ns.a.startswith('quicksort'):
        qs_type = ns.a.replace('quicksort_', '')

        if qs_type == 'fp':
            qs = Quicksort()
        elif qs_type == 'rp':
            qs = Quicksort(True)
        elif qs_type == 'fp_t':
            # TODO: Broken?
            qs = Quicksort(False, 10)
        elif qs_type == 'rp_t':
            qs = Quicksort(True, len(array) / 10)
        else:
            raise ValueError('Wrong quicksort type')

        compute(lambda: qs.sort(array))


ns = parse_arguments()
main()
