from dag import Graph
import time
import sys
from backtrack import backtrack
from vorace import vorace
from dynamic import dynamic


def read(file):
    with open(file) as f:
        vertexCount = f.readline().split()[0]
        content = f.readlines()
    content = [tuple(x.split()) for x in content]

    return vertexCount, content


def compute(a, p, t):
    start_time = time.perf_counter()
    extensions = a()
    end_time = time.perf_counter()
    compute_time = end_time - start_time

    if p:
        print(extensions)

    if t:
        print("%s" % compute_time)

    return extensions, compute_time


def main(file, a, t, p):
    sys.setrecursionlimit(500000)

    vertexCount, edges = read(file)
    G = Graph(vertexCount, edges)

    if a == 'vorace':
        e, t = compute(lambda: vorace(G), p, t)

    elif a == 'dynamique':
        e, t = compute(lambda: dynamic(G), p, t)

    elif a == 'retourArriere':
        e, t = compute(lambda: backtrack(G), p, t)

    else:
        return 0

    return e, t
