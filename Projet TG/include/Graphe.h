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
        ///indices de centralité
        float *centralite_degre; //le degré de centralité de chaque sommet dans un vecteur

    public:
        ///construction / destruction
        Graphe(std::string txt);
        virtual ~Graphe();
        //chargement
        void charger_ponderation(std::string txt);

        ///affichage
        void afficher() const;
        void afficher_degre_centralite() const;
        void afficher_graphe_internet() const;

        ///calcul des indices de centralité
        //CENTRALITE DE DEGRE
        float calculer_Cd(int indice) const;
        void calculer_tous_Cd();

};

#endif // GRAPHE_H
