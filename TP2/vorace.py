import math

def entropy(G, L):
    h = 0

    for l in L:
        val = len(l) / len(G.vertices)
        h -= val * math.log(val, 2)

    return 2 ** (1 / 2 * len(G.vertices) * h)


def vorace(G):
    L = G.chain_decomposition()
    return entropy(G, L)
