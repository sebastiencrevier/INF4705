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


def vorace(G):
    L = chain_decomposition(G)
    return entropy(G, L)
