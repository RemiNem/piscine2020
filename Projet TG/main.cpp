#include <iostream>
#include "Graphe.h"

int main()
{
    ///charger graphe
    //chargement du format topologique du graphe
    Graphe G("Load Graph/graphe_etoile1_topo.txt");
    //pondération
    G.charger_ponderation("Load Graph/graphe_etoile1_pond.txt");
    ///afficher graphe
    G.afficher();
    //G.afficher_matrice_indice();

    G.calculer_tous_Cd();
    G.afficher_degre_centralite();
    G.afficher_graphe_internet();


    return 0;
}
