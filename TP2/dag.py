import copy


class Graph:
    def __init__(self, vertex_count, edges):
        vertex_count = int(vertex_count)

        self.vertices = list(range(vertex_count))
        self.adj = [[0 for col in range(vertex_count)] for row in range(vertex_count)]

        for edge in edges:
            self.add_edge(int(edge[0]), int(edge[1]))

    def add_edge(self, start, end):
        self.adj[start][end] = 1

    def has_edge(self, start, end):
        return self.adj[start][end] == 1

    def predecessors(self, vertex):
        p = []
        for v in self.vertices:
            if self.has_edge(v, vertex):
                p.append(v)
        return p

    def remove_vertex(self, vertex):
        self.vertices.remove(vertex)

    def remove_vertices(self, vertices):
        for v in vertices:
            self.vertices.remove(v)

    def in_degree(self):
        degrees = {v: 0 for v in self.vertices}
        for v in self.vertices:
            for vv in self.vertices:
                if self.has_edge(v, vv):
                    degrees[vv] += 1

        for key in degrees.keys():
            yield key, degrees[key]

    def find_edges(self, vertex):
        if vertex not in self.vertices:
            return

        for index, item in enumerate(self.adj[vertex]):
            if item == 1 and index in self.vertices:
                yield vertex, index

    def path(self, m):
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

    def hsu(self, m):
        """ Transforms a given directed acyclic graph into its minimal equivalent """
        n = len(m)
        for j in range(n):
            for i in range(n):
                if m[i][j]:
                    for k in range(n):
                        if m[j][k]:
                            m[i][k] = 0

    def topological_sort(self):
        indegree_map = {v: d for v, d in self.in_degree() if d > 0}
        zero_indegree = [v for v, d in self.in_degree() if d == 0]

        while zero_indegree:
            node = zero_indegree.pop()
            for _, child in self.find_edges(node):
                try:
                    indegree_map[child] -= 1
                except KeyError:
                    raise RuntimeError("Graph changed during iteration")
                if indegree_map[child] == 0:
                    zero_indegree.append(child)
                    del indegree_map[child]

            yield node

    def longest_path(self):
        if not self.vertices:
            return []

        dist = {}  # stores {v : (length, u)}
        for v in self.topological_sort():
            us = [(dist[u][0] + 1, u)
                  for u in self.predecessors(v)]
            # Use the best predecessor if there is one and its distance is non-negative, otherwise terminate.
            maxu = max(us, key=lambda x: x[0]) if us else (0, v)
            dist[v] = maxu  # if maxu[0] >= 0 else (0, v)
        u = None
        v = max(dist, key=lambda x: dist[x][0])
        path = []
        while u != v:
            path.append(v)
            u = v
            v = dist[v][1]
        path.reverse()
        return path



    def chain_decomposition(self):
        g = copy.deepcopy(self)

        # TODO: Vérifier transitive reduction??
        m = self.path(g.adj)
        self.hsu(m)
        g.adj = m

        L = []
        c = g.longest_path()
        while c:
            g.remove_vertices(c)
            L.append(c)
            c = g.longest_path()
        for n in g.vertices:
            L.append([n])

        return L