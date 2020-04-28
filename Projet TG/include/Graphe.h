#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <vector>
#include "Sommet.h"
#include <iostream>
#include <fstream>
#include "Arrete.h"
class Graphe
{
    private:
        bool m_orientation; //orientation graphe
        size_t m_ordre; //nombre de sommets
        std::vector<Sommet*> sommets; //tous les sommets
        Arrete *arretes; //toutes les arretes
        size_t m_taille; //nombre d'arretes
        /// INDICES DE CENTRALITE
        float *centralite_degre; //le degré de centralité de chaque sommet dans un vecteur

    public:
        ///DESTRUCTION
        virtual ~Graphe();

        /// --------CHARGEMENT GRAPHE------
        Graphe(std::string txt); //topologique
        void charger_ponderation(std::string txt); //pondération

        /// ---------AFFICHAGE--------
        void afficher() const; //affichage du graphe sur console
        void afficher_degre_centralite() const; //affichage du degré de centralité de chaque sommet
        void afficher_graphe_internet() const; //html

        /// --------CALCULS INDICES DE CENTRALITE---------
        //CENTRALITE DE DEGRE
        float calculer_Cd(int indice) const;
        void calculer_tous_Cd();


};

#endif // GRAPHE_H
