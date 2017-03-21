import math
import copy


def path(m):
    """ Returns a path matrix """
    p = [list(row) for row in m]
    n = len(p)
    for i in range(0, n):
        for j in range(0, n):
            if i == j:
                continue
            if p[j][i]:
                for k in range(0, n):
                    if p[j][k] == 0:
                        p[j][k] = p[i][k]
    return p


def hsu(m):
    """ Transforms a given directed acyclic graph into its minimal equivalent """
    n = len(m)
    for j in range(n):
        for i in range(n):
            if m[i][j]:
                for k in range(n):
                    if m[j][k]:
                        m[i][k] = 0


def chain_decomposition(G):
    g = copy.deepcopy(G)

    # TODO: Vérifier transitive reduction??
    m = path(g.adj)
    hsu(m)
    g.adj = m

    L = []
    c = longest_path(g)
    while c:
        g.remove_vertices(c)
        L.append(c)
        c = longest_path(g)
    for n in g.vertices:
        L.append([n])

    return L


def longest_path(G):
    if not G.vertices:
        return []

    dist = {}  # stores {v : (length, u)}
    for v in topological_sort(G):
        us = [(dist[u][0] + 1, u)
              for u in G.predecessors(v)]
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


def topological_sort(G):
    indegree_map = {v: d for v, d in G.in_degree() if d > 0}
    zero_indegree = [v for v, d in G.in_degree() if d == 0]

    while zero_indegree:
        node = zero_indegree.pop()
        for _, child in G.find_edges(node):
            try:
                indegree_map[child] -= 1
            except KeyError:
                raise RuntimeError("Graph changed during iteration")
            if indegree_map[child] == 0:
                zero_indegree.append(child)
                del indegree_map[child]

        yield node


def entropy(G, L):
    h = 0

    for l in L:
        val = len(l) / len(G.vertices)
        h -= val * math.log(val, 2)

    return 2 ** (1 / 2 * len(G.vertices) * h)


def vorace(G):
    L = chain_decomposition(G)
    return entropy(G, L)
