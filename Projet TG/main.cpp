#include <iostream>
#include "include\Graphe.h"



int main()
{
    ///charger graphe
    //chargement du format topologique du graphe
    Graphe G("Load Graph/graphe_cycle4_topo.txt");
    //pond�ration
    G.charger_ponderation("Load Graph/graphe_etoile1_pond.txt");
    ///afficher graphe
    G.afficher();
    //G.afficher_matrice_indice();
    //degre de centralite
    G.calculer_tous_Cd();
    G.afficher_degre_centralite();
    //centralite de proximite
    G.calculer_tous_Cp();
    G.afficher_centralite_proximite();

    G.afficher_graphe_internet();
    G.calculer_Cvp();
    G.afficher_centralite_vp();

G.Dijkstra_adapte(0,2);

    return 0;
}






