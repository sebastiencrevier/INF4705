
def backtrack_recursive(G, ext):
    exts = 0
    nodes = [x for x in G.vertices if x not in ext]

    for n in nodes:
        has_predecessors = False

        for x in nodes:
            if G.has_edge(x, n):
                has_predecessors = True
                break

        if has_predecessors:
            continue

        temp = ext[:]
        temp.append(n)

        result = backtrack_recursive(G, temp)

        # add the recursively found extensions to the list
        exts += result

        # if last node, add a new extension to the list
        if len(nodes) == 1:
            exts += 1

    return exts


def backtrack(G):
    extensions = backtrack_recursive(G, [])
    return extensions
