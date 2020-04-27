#include <iostream>
#include "Graphe.h"

int main()
{
Graphe G("Graphe topo/graphe_etoile1_topo.txt");///charge le format topologique

G.afficher();
//G.afficher_matrice_indice();

    return 0;
}
