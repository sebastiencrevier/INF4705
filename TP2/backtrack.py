
def backtrack_recursive(G, ext, removed_nodes):
    exts = []
    nodes = [x for x in G.vertices if x not in removed_nodes]

    for n in nodes:
        pred = G.predecessors(n, removed_nodes)
        if pred and pred not in ext:
            continue

        temp = ext[:]
        temp.append(n)

        temp2 = removed_nodes[:]
        temp2.append(n)

        result = backtrack_recursive(G, temp, temp2)

        # add the recursively found extensions to the list
        for r in result:
            exts.append(r)

        # if last node, add a new extension to the list
        if len(nodes) == 1:
            exts.append(temp)

    return exts


def backtrack(G):
    extensions = backtrack_recursive(G, [], [])
    return len(extensions)
