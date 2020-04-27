#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <vector>
#include "Sommet.h"
#include <iostream>
#include <fstream>
class Graphe
{
    public:
        Graphe(std::string txt);
        void afficher() const;
        void initialiser_matrices();
        void afficher_matrice_indice();
        void charger_ponderation(std::string txt);
        virtual ~Graphe();

        bool orientation;
		size_t ordre;
		std::vector<Sommet*>sommets;// tous les sommets de mon graphe
		size_t m_taille;
		int **matrice_poids;///arretes
		int **matrice_indice;///arretes

};

#endif // GRAPHE_H
