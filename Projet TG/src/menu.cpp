#include <iostream>
#include "../include/Graphe.h"
#include "../include/erreur.h"

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
        std::cin >> choix;
        switch(choix)
        {
            case 1: //CHARGER UN GRAPHE
                //charger le graphe avec les blindages
                G.charger_graphe(graphe_charge);
                //calculer les indices de centralit�
                G.calculer_tous_indices();
                //a la fin
                graphe_charge = true;
                break;
            case 2: // CHANGER LE SYSTEME DE PONDERATION DU GRAPHE
                if(graphe_charge)
                {

                }
                else
                    erreur("le graphe n'est pas encore charge");
                break;
            case 3: // AFFICHER LES INDICES DE CENTRALITE DU GRAPHE
                if(graphe_charge)
                {
                    //affichage du graphe
                    G.afficher();
                    G.afficher_graphe_internet();
                    //Affichage des degres de centralite
                    G.afficher_tous_indices();
                    //SAUVEGARDE:
                    //A faire

                }
                else
                    erreur("le graphe n'est pas encore charge");
                break;
            case 4: // SUPPRIMER UNE ARRETE DU GRAPHE
                // = creer un sspg "vulnerabilite" qui appellera d'autres programme pour :
                // 1) supprimer une arrete
                // 2) tester la connexite
                // 3) recalculer les nouveaux indices de centralit� et les comparer avec les anciens (dans la sauvegarde)
                // 4) sauvegarder les nouveaux indices de centralite ?
                if(graphe_charge)
                {

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

    }while(!quitter);
}
