from tp1 import main
import numpy as np


def execute_algo(n, x, y, a, run_time_times=False):
    for nn in n:
        for xx in x:
            # Don't compute the 2nd serie with counting sort => values are too large
            if a == "counting_sort" and xx == 1:
                continue

            arr = []
            for yy in y:
                i = 10 if run_time_times else 1
                value_arr = []

                while i != 0:
                    value_arr.append(main("./ex/testset_{}_{}.txt".format(nn, xx * 10 + yy), a, False, False))
                    i -= 1

                arr.append(np.mean(value_arr))

            print("{},{},{},{}".format(a, nn, xx + 1, np.mean(arr)))


n = [1000, 5000, 10000, 50000, 100000, 500000]
x = range(3)
y = range(10)
a = ["counting_sort", "quicksort_fp", "quicksort_rp", "quicksort_fp_t", "quicksort_rp_t"]

print("Algorithme,N,Série,Temps moyen")

for aa in a:
    # If random pivot, execute 10 times
    if "rp" in aa:
        execute_algo(n, x, y, aa, True)
    else:
        execute_algo(n, x, y, aa)
