import numpy as np
import networkx as nx

def vorace(arr, max_val):
    m = max_val + 1
    count = [0] * m  # init with zeros
    for a in arr:
        count[a] += 1  # count occurences
    i = 0
    for a in range(m):  # emit
        for c in range(count[a]):  # - emit 'count[a]' copies of 'a'
            arr[i] = a
            i += 1
    return arr


def dynamique(numList, first, last):
    for x in range(first, last + 1):
        key = numList[x]
        y = x - 1
        while y > -1 and numList[y] > key:
            numList[y + 1] = numList[y]
            y = y - 1
        numList[y + 1] = key

#def retourArriere(arr, max_val):

def transitive_reduction(G):
    TR = nx.DiGraph()
    TR.add_nodes_from(G.nodes())
    for u in G:
        u_edges = set(G[u])
        for v in G[u]:
            u_edges -= {y for x, y in nx.dfs_edges(G, v)}
        TR.add_edges_from((u, v) for v in u_edges)
    return TR

def dag_longest_path(G, weight='weight', default_weight=1):
    dist = {} # stores {v : (length, u)}
    for v in nx.topological_sort(G):
        us = [(dist[u][0] + data.get(weight, default_weight), u)
            for u, data in G.pred[v].items()]
        # Use the best predecessor if there is one and its distance is non-negative, otherwise terminate.
        maxu = max(us, key=lambda x: x[0]) if us else (0, v)
        dist[v] = maxu if maxu[0] >= 0 else (0, v)
    u = None
    v = max(dist, key=lambda x: dist[x][0])
    path = []
    while u != v:
        path.append(v)
        u = v
        v = dist[v][1]
    path.reverse()
    return path

def transitive_reduction(G):
    TR = nx.DiGraph()
    TR.add_nodes_from(G.nodes())
    for u in G:
        u_edges = set(G[u])
        for v in G[u]:
            u_edges -= {y for x, y in nx.dfs_edges(G, v)}
        TR.add_edges_from((u, v) for v in u_edges)
    return TR


def calculateAllChains(G):
    L =[]
    c = dag_longest_path(G)

    while c != []:
        G.remove_nodes_from(c)
        L = c
        c = dag_longest_path(G)


if __name__ == "__main__":


    G = nx.DiGraph();
    G.add_edges_from([(1, 0), (1, 4), (1,8), (2, 5), (5,8), (6, 0), (6, 2), (6, 4), (7, 2), (9, 3), (9, 6), (9, 7)])
    print(G.number_of_nodes(), G.number_of_edges())
    t = transitive_reduction(G)
    print(t.nodes())
    print(dag_longest_path(G))

    calculateAllChains(G)