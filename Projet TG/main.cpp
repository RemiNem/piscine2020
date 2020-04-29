#include <iostream>
#include "include\Graphe.h"
#include "include/menu.h"

int main()
{
    ///INITIALISATION
    //demander quel graphe charger
    //+ blinder

    //+sauvegarde
    ///MENU
    //Appeler le menu

    Graphe G("Load Graph/graphe_cycle4_topo.txt");
    //pond�ration
    G.charger_ponderation("Load Graph/graphe_etoile1_pond.txt");
    G.Dijkstra_adapte(0,2);

    return 0;
}







