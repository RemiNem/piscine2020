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
        std::vector<Sommet*>sommets; //tous les sommets
        Arrete *arretes; //toutes les arretes
        size_t m_taille; //nombre d'arretes


    public:
        Graphe(std::string txt);
        virtual ~Graphe();
        //chargement
        void charger_ponderation(std::string txt);
        //affichage
        void afficher() const;
};

#endif // GRAPHE_H
