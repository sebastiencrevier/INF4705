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
