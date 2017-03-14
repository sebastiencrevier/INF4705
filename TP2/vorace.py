import networkx as nx
import math
from networkx.algorithms import dag


def transitive_reduction(G):
    TR = nx.DiGraph()
    TR.add_nodes_from(G.nodes())
    for u in G:
        u_edges = set(G[u])
        for v in G[u]:
            u_edges -= {y for x, y in nx.dfs_edges(G, v)}
        TR.add_edges_from((u, v) for v in u_edges)
    return TR


def chain_decomposition(G):
    g = transitive_reduction(G)
    L = []
    c = dag.dag_longest_path(g)
    while c:
        g.remove_nodes_from(c)
        L.append(c)
        c = dag.dag_longest_path(g)
    for n in g.nodes():
        L.append([n])

    return L


def entropy(G, L):
    h = 0

    for l in L:
        val = len(l) / len(G.nodes())
        h -= val * math.log(val, 2)

    return 2 ** (1 / 2 * len(G.nodes()) * h)


if __name__ == "__main__":
    G = nx.DiGraph()
    G.add_edges_from([(1, 0), (1, 4), (1, 8), (2, 5), (5, 8), (6, 0), (6, 2), (6, 4), (7, 2), (9, 3), (9, 6), (9, 7)])

    L = chain_decomposition(G)
    e = entropy(G, L)
    print(e)
