#include <iostream>
#include "../include/Graphe.h"
#include "../include/fonctions.h"

void menu()
{
    bool quitter = false;
    bool graphe_charge = false;
    int choix;
    Graphe G;
    do
    {
        std::cout << std::endl << "Que voulez vous faire ? " << std::endl
                  << "1) Charger un graphe " << std::endl
                  << "2) Changer le systeme de ponderation du graphe " << std::endl
                  << "3) Afficher les indices de centralite du graphe " << std::endl
                  << "4) Supprimer une arrete du graphe " << std::endl
                  << "5) Quitter " << std::endl;
        entree_blindee(1, 5, choix);
        system("cls");
        switch(choix)
        {
            case 1: //CHARGER UN GRAPHE
                //charger le graphe avec les blindages
                G.charger_graphe(graphe_charge);
                //calculer ses CC
                G.rechercher_CC();
                //G.afficher_graphe_internet();
                //calculer les indices de centralite du graphe
                G.calculer_tous_indices();
                G.calculer_tous_indices_normalises();
                G.sauvegarde_centralites(); // + sauvegarde des donnees
                //afficher le graphe charge
                system("cls");
                G.afficher();
                G.afficher_CC();
                G.afficher_graphe_internet(); //en html
                break;
            case 2: // CHANGER LE SYSTEME DE PONDERATION DU GRAPHE
                if(graphe_charge)
                {
                    G.changer_ponderation();
                    G.calculer_tous_indices(); // recalculer les indices de centralite qui ont change
                    G.calculer_tous_indices_normalises();
                    G.sauvegarde_centralites(); //on les sauvegarde
                    G.afficher_graphe_internet(); //actualiser l'affichage du graphe sur html
                }
                else
                    erreur("le graphe n'est pas encore charge");
                break;
            case 3: // AFFICHER LES INDICES DE CENTRALITE DU GRAPHE
                if(graphe_charge)
                {
                    //affichage du graphe
                    G.afficher_graphe_internet();
                    //Affichage des degres de centralite
                    G.afficher_tous_indices(8, 26);
                    system("pause");
                    system("cls");
                    G.afficher_tous_indices_normalises(8, 26);
                }
                else
                    erreur("le graphe n'est pas encore charge");
                break;
            case 4: // SUPPRIMER UNE ARRETE DU GRAPHE
                if(graphe_charge)
                {
                    G.vulnerabilite();
                    G.afficher_graphe_internet(); //actualiser le graphe internet
                }
                else
                    erreur("le graphe n'est pas encore charge");
                break;
            case 5: // QUITTER
                quitter = true;
                break;

            default: // mettre un catch pour les erreurs
                break;
        }
        system("pause");
        system("cls");

    }while(!quitter);
}
