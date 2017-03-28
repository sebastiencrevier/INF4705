
def backtrack_recursive(G, nodes):
    exts = 0

    for n in nodes:
        has_predecessors = False

        for x in nodes:
            if G.has_edge(x, n):
                has_predecessors = True
                break

        if has_predecessors:
            continue

        temp = nodes[:]
        temp.remove(n)

        result = backtrack_recursive(G, temp)

        # add the recursively found extensions to the list
        exts += result

        # if last node, add a new extension to the list
        if len(nodes) == 1:
            exts += 1

    return exts


def backtrack(G):
    extensions = backtrack_recursive(G, G.vertices)
    return extensions
