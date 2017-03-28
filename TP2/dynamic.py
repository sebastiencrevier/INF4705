from dag import Graph
import numpy as np
import utilities as util

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




def create_array_recursive(G):
    chains = G.chain_decomposition()
    nbDimension = len(chains)
    y=0
    nb_ext = 0
    max_val = max_value(chains)
    tab= np.ones(1,int)
    for i in range(nbDimension):
        tab = util.add_dimension(tab, len(chains[i]+1))
    n=nbDimension

    create_array_recursion(n,G,chains,nbDimension, tab[0])


def create_array_recursion(n,G,chains,nbDimension, tab):

    if n>1:
        index = []
        val = parcours(tab, 0, 0, index)
        create_array_recursion(n-1,G, chains,nbDimension,tab[x])


    if n == 0:
        arr = tab[-1]
        while nbDimension > 1:
            arr = arr[-1]
            nbDimension -= 1

        return arr[-1]


def parcours(array, x, y, index):
    for i in range(len(array)):
        elem = array[i]
        if elem is int:
            index.append(i)
            return elem
        else:
            return parcours(elem, x, y, index)
