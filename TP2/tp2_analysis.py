import numpy as np
import argparse
from tp2 import main


def parse_arguments():
    parser = argparse.ArgumentParser()

    parser.add_argument('-e')
    parser.add_argument('-a')

    namespace = parser.parse_args()
    return namespace

ns = parse_arguments()

e = ["10-4", "10-6", "10-8",
     "14-4", "14-6", "14-8", "14-10",
     "18-4", "18-6", "18-8", "18-10",
     "22-4", "22-6", "22-8", "22-10",
     "26-4", "26-6", "26-8", "26-10",
     "30-4", "30-6", "30-8", "30-10"]
if ns.e is not None:
    e = [ns.e]

n = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]

a = ["retourArriere", "vorace", "dynamique"]
if ns.a is not None:
    a = [ns.a]

print("Algorithme,Série,Extensions linéaires,Temps")

for aa in a:
    for ee in e:
        arr = []
        for nn in n:
            ext, t = main("./ex/poset{}{}".format(ee, nn), aa, False, False)
            arr.append((ext, t))
            print("{}{} - {}".format(ee, nn, t))

        print("{},{},{},{}".format(aa, ee, np.mean([x[0] for x in arr]), np.mean([x[1] for x in arr])))
