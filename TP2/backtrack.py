import networkx as nx

def backtrack_recursive(G, ext):
    exts = []
    nodes = G.nodes()

    for n in nodes:
        pred = G.predecessors(n)
        if pred and pred not in ext:
            continue

        temp = ext.copy()
        temp.append(n)

        g = G.copy()
        g.remove_node(n)

        result = backtrack_recursive(g, temp)

        # add the recursively found extensions to the list
        for r in result:
            exts.append(r)

        # if last node, add a new extension to the list
        if len(nodes) == 1:
            exts.append(temp)

    return exts

if __name__ == "__main__":
    G = nx.DiGraph()
    # G.add_edges_from([(1,3), (2,3), (2,0)])
    # G.add_edges_from([(1,4),(2,4),(2,5),(3,4),(3,5),(5,6)])
    G.add_edges_from([(1, 0), (1, 4), (1, 8), (2, 5), (5, 8), (6, 0), (6, 2), (6, 4), (7, 2), (9, 3), (9, 6), (9, 7)])

    nodes = backtrack_recursive(G, [])

    print(len(nodes))
