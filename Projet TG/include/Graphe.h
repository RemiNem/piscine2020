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
        bool m_orientation;
        size_t m_ordre;
        std::vector<Sommet*>sommets;// tous les sommets de mon graphe
        size_t m_taille;
        Arrete *arretes;

    public:
        Graphe(std::string txt);
        virtual ~Graphe();
        //chargement
        void charger_ponderation(std::string txt);
        //affichage
        void afficher() const;
};

#endif // GRAPHE_H
