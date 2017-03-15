import networkx as nx

def backtrack_recursive(G, ext):
    exts = []

    for n in G.nodes():
        if G.edges() and not G.successors(n) and G.predecessors(n):
            continue

        temp = ext.copy()
        temp.append(n)

        g = G.copy()
        g.remove_node(n)

        result = backtrack_recursive(g, temp)

        for r in result:
            exts.append(r)

        if len(G.nodes()) == 1:
            exts.append(temp)

    return exts

if __name__ == "__main__":
    G = nx.DiGraph()
    G.add_edges_from([(1,3), (2,3), (2,0)])

    nodes = backtrack_recursive(G, [])
    print(nodes)
