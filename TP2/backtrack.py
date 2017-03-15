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


def backtrack(G):
    extensions = backtrack_recursive(G, [])
    return len(extensions)
