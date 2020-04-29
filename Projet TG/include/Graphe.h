#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <vector>
#include "Sommet.h"
#include <iostream>
#include <fstream>
#include "Arrete.h"
#include <math.h>
class Graphe
{
    private:
        bool m_orientation; //orientation graphe
        size_t m_ordre; //nombre de sommets
        std::vector<Sommet*> sommets; //tous les sommets
        Arrete *arretes; //toutes les arretes
        size_t m_taille; //nombre d'arretes
        /// INDICES DE CENTRALITE
        float *centralite_degre; //le degr� de centralit� de chaque sommet dans un vecteur
        float *centralite_vecteurp; // degr� de centralit� Vp de chaque sommet
        float *centralite_proximite; //le degre de proximit� de chaque sommet dans un vecteur
    public:
        ///DESTRUCTION
        Graphe();
        virtual ~Graphe();

        /// --------CHARGEMENT GRAPHE------
        Graphe(std::string txt); //topologique
        void charger_ponderation(std::string txt); //pond�ration

        /// ---------AFFICHAGE--------
        void afficher() const; //affichage du graphe sur console
        void afficher_graphe_internet() const; //html
        void afficher_degre_centralite() const; //affichage du degr� de centralit� de chaque sommet
        void afficher_centralite_proximite() const; //affichage de la centrlite de proximite de chaque sommet
        void afficher_centralite_vp() const; //affichage de la centralite de vecteur pour chaque sommet
        void afficher_tous_indices() const; //affiche tous les indices de centralite


        /// ------------GETTERS-------------------
        Arrete get_arrete(int s1, int s2) const;

        /// --------CALCULS INDICES DE CENTRALITE---------

        //CENTRALITE DE DEGRE
        float calculer_Cd(int indice) const;
        void calculer_tous_Cd();

        //CENTRALITE DE PROXIMITE
        float calculer_Cp(int indice) const;
        void calculer_tous_Cp();
        int Dijkstra(int debut, int fin) const;
        bool EstSuccesseurDe(int s1, int s2) const;

        //CENTRALITE DE VECTEUR PROPRE
        void calculer_Cvp();

        //CENTRALITE D'INTERMEDIARITE
        int Dijkstra_adapte(int debut, int fin) ;

        //CALCULER TOUS
        void calculer_tous_indices();


};

#endif // GRAPHE_H
