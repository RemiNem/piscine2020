#include <iostream>
#include "Graphe.h"

int main()
{
Graphe G("Load Graph/graphe_etoile1_topo.txt");///charge le format topologique
G.charger_ponderation("Load Graph/graphe_etoile1_pond.txt");
G.afficher();
//G.afficher_matrice_indice();

    return 0;
}
