import math


def entropy(nodes, chains):
    h = 0

    for c in chains:
        val = len(c) / nodes
        h -= val * math.log(val, 2)

    return 2 ** (1 / 2 * nodes * h)


def vorace(G):
    nodes = len(G.vertices)
    chains = G.chain_decomposition()
    return entropy(nodes, chains)
