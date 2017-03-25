from dag import Graph
import numpy as np

#Pour linstant fonctionne seulement avec l<exemplaire mit dans "main" en dessous
#TODO: Il faudrait plutot faire les 2 premieres dimensions dans create_arr_recursive() et apres dans create_arr_recursion ()  faire les calculs pour chaque dimensions supp
# voir http://stackoverflow.com/questions/33498457/how-can-i-save-3d-array-results-to-a-4d-array-in-python-numpy Pour ajouter une dimensiion

def dynamic(G):
    fermeture_transitive(G)
    return create_arr_recursive(G)

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

#TESTER LES 2 ALGOS QUON A LES TABLEAUX
# if __name__ == '__main__':
#     edges = [(0, 2), (1, 2), (2, 3)]
#     G = Graph(4, edges)
#     dynamic(G)

