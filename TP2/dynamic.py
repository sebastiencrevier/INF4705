from dag import Graph
import numpy as np

#Pour linstant fonctionne seulement avec l<exemplaire mit dans "main" en dessous
#TODO: Il faudrait plutot faire les 2 premieres dimensions dans create_arr_recursive() et apres dans create_arr_recursion ()  faire les calculs pour chaque dimensions supp
# voir http://stackoverflow.com/questions/33498457/how-can-i-save-3d-array-results-to-a-4d-array-in-python-numpy Pour ajouter une dimensiion

def dynamic(G):
    fermeture_transitive(G)
    return reconstructPath(G)

def max_value(list):
    return max(len(slist) for slist in list)

def fermeture_transitive(G):

    m = G.adj
    c = [[0] * len(G.vertices) for i in range(len(G.vertices))]
    #Fermeture transitive
    for k in range(len(m)):
        for i in range(len(m[0])):
            for j in range(len(m)):
                if(c[i][j] < m[i][k] * m[k][j]):
                    m[i][j] +=   m[i][k] * m[k][j]


def create_arr_recursive(G):
    chains = G.chain_decomposition()
    nbDimension = len(chains)
    y=0
    max_val = max_value(chains)
    tab=[]

    return create_arr_recursion(G,chains,y,nbDimension, tab, max_val-1,0)

def create_arr_recursion(G,chains,y,taille, tab, max_val,nb_ext):

    if (taille == 0):
        return nb_ext

    tab.append([0]* (max_val+1))
    for i in range(max_val+1):

        if i == 0 or y == 0:
            tab[y][i]= 1
        else:
            premier = tab[y - 1][i]
            deuxieme = tab[y][i-1]
            #Si les predecesseurs du noeud quon ajoute sont deja présent ont doit multiplier par 0
            h = G.predecessors(chains[y-1][0 if len(chains[y-1]) == 1 else i-1])
            if len(h) > 0 and (y or i) in h :
                premier = 0 * premier

            tab[y][i] = premier + deuxieme
            if(taille==1):
                nb_ext= tab[y][i]
    return create_arr_recursion(G, chains, y + 1, taille - 1, tab, max_val, nb_ext)

def create_arr_recursive2(G):
    chains = G.chain_decomposition()
    nbDimension = len(chains)
    y=0
    nb_ext = 0
    max_val = max_value(chains)
    tab=np.array([])
    taille = max_val -1

    if (taille == 0):
        return nb_ext


    for i in range(nbDimension):
        tab = tab[..., None]
        return create_arr_recursion(G,chains,y,nbDimension, tab, max_val-1,nb_ext)

def create_arr_recursion2(G,chains,y,taille, tab, max_val,nb_ext):

    if (taille == 0):
        return nb_ext

    tab.append([0]* (max_val+1))
    for i in range(max_val+1):

        if i == 0 or y == 0:
            tab[y][i]= 1
        else:
            premier = tab[y - 1][i]
            deuxieme = tab[y][i-1]
            #Si les predecesseurs du noeud quon ajoute sont deja présent ont doit multiplier par 0
            h = G.predecessors(chains[y-1][0 if len(chains[y-1]) == 1 else i-1])
            if len(h) > 0 and (y or i) in h :
                premier = 0 * premier

            tab[y][i] = premier + deuxieme
            if(taille==1):
                nb_ext= tab[y][i]
    return create_arr_recursion(G, chains, y + 1, taille - 1, tab, max_val, nb_ext)

# ReconstructPath ( from vertex i to j )        # finds the path from i to j
#     If (shortest path from i to j represents the edge between them) Then
#         Return a path composed of i and j
#     Else
#         Let k be the intermediate vertex of the path from i to j
#         Return the path: [ ReconstructPath(i,k) ] concatenated with [ ReconstructPath(k,j) without first vertex k ]
#     End If
# End ReconstructPath

def reconstructPath_recursion(start,end,G,i,g, chains, nbDimensions):
    # if G.adj[start][end] == 1 :
    #     return 1
    # else:
    #     return reconstructPath_recursion(G.adj[start][end-1] + G.adjp[start-1][end], G)
    if(nbDimensions == 0):
        return 0

    g.append(np.ones(((len(chains[i])+1), (len(chains[i+1])+1)),np.int))

    for y in range(len(chains[i])):
        for z in range(len(chains[i+1])):
            # if G.adj[chains[i][y]][chains[i+1][z]] == 1:
                # g[1][chains[i][y],chains[i+1][z]] +=
            if G.adj[chains[i][y]][chains[i+1][z]] == 0:
                # g[1][chains[i][y], chains[i + 1][z]] +=
                g.append(reconstructPath_recursion(G.adj[chains[i][y]][chains[i+1][z] - 1] + G.adj[chains[i][y] - 1][chains[i+1][z]], G))

def reconstructPath_recursion2(start,end,G):
    if G.adj[start][end] == 1 :
        return 1
    else:
        return reconstructPath_recursion(G.adj[start][end-1] + G.adj[start-1][end], G)



def reconstructPath(G):
    chains = G.chain_decomposition()
    nbDimension = len(chains)
    tab=[]
    g=[]
    y=0

    array = [1] * len(chains[0])
    for i in range(1, len(chains) - 1):
        array = [array] * len(chains[i])
    print(len(chains))

    reconstructPath_recursion(chains[i][y], chains[i+1][0], G,i,g,chains, nbDimension)



def recurisive_path(i, chains,tab,max_val,nbDimension, G):

    if (i == nbDimension):
        return tab

    for k in range(max_val):
        tab[i][k]=path(G,i,k)



def path (G, i, j ) :

    if i == 0 or i == j:
        return 1

    else:
        return path(G, i, G.predecessors(j))+j

# def meow(G):
#     N = len(G.chain_decomposition())
#     nodeArray = [N]
#     nodeArray[0] = 1
#     for K in range(N):
#         for L in range (1,K - 1 ):
#             if(L < K):
#                 if (nodeArray[L]+1 > nodeArray[K]):
#                     nodeArray[K] = nodeArray[L] +1



#TESTER LES 2 ALGOS QUON A LES TABLEAUX
if __name__ == '__main__':
    edges = [(0, 2), (1, 2), (2, 3)]
    G = Graph(4, edges)
    create_arr_recursive2(G)

