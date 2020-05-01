#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <vector>
#include "Sommet.h"
#include <iostream>
#include <fstream>
#include "Arrete.h"
#include <math.h>
#include <bits/stdc++.h>
#include <map>

class Graphe
{
    private:
        bool m_orientation; //orientation graphe
        size_t m_ordre; //nombre de sommets
        std::vector<Sommet*> sommets; //tous les sommets
        std::vector<Arrete> arretes; //toutes les arretes
        size_t m_taille; //nombre d'arretes
        std::string nomfichiergraphe; // nom du dossier dans lequel se trouvent les ponderations autorisees a charger sur ce graphe
        std::vector<std::vector<int>> CC;//le tableau des composantes connexes (chaque case contient un lot de sommets)
        /// INDICES DE CENTRALITE (NON NORMALISES)
        float *centralite_degre; //le degr� de centralit� de chaque sommet dans un vecteur
        float *centralite_vecteurp; // degr� de centralit� Vp de chaque sommet
        float *centralite_proximite; //le degre de proximit� de chaque sommet dans un vecteur
        float *centralite_intermediarite; //bon vous avez compris le concept
        ///INDICES DE CENTRALITE NORMALISES
        float *Cd_norm;
        float *Cvp_norm;
        float *Cp_norm;
        float* Ci_norm;
    public:
        ///DESTRUCTION
        Graphe();
        virtual ~Graphe();

        /// --------CHARGEMENT GRAPHE------
        void charger_graphe(bool &graphe_charge); //chargement du graphe global
        void changer_ponderation(); //pour modifier ou charger la ponderation via un choix de fichier
        void charger_topologique(std::string txt); //topologique
        void charger_ponderation(std::string txt); //pond�ration
        void reinitialiser_graphe(); //

        /// ---------AFFICHAGE--------
        void afficher() const; //affichage du graphe sur console
        void afficher_arretes() const; //affiche seulement les arretes du graphe avec leur poids
        void afficher_graphe_internet() const; //html
        void afficher_tous_indices(int y, int x) const; //affiche tous les indices de centralite
        void afficher_centralite(float* vecteur, int dx, int y) const;
        void afficher_tous_indices_normalises(int dy, int dx) const;


        /// ------------GETTERS-------------------
        void get_arrete(int s1, int s2, Arrete &arrete) const;

        ///--------------SETTERS------------------
        void set_m_taille(size_t taille);
        //void set_arretes(Arrete *nouv_arretes);

        /// --------CALCULS INDICES DE CENTRALITE---------

        //CENTRALITE DE DEGRE
        float calculer_Cd(int indice) const;
        void calculer_tous_Cd();
        void Cd_normalise();

        //CENTRALITE DE PROXIMITE
        float calculer_Cp(int indice) const;
        void calculer_tous_Cp();
        int Dijkstra(int debut, int fin) const;
        void Cp_normalise();

        //CENTRALITE DE VECTEUR PROPRE
        void calculer_Cvp();
        void Cvp_normalise();

        //CENTRALITE D'INTERMEDIARITE
        float Dijkstra_ameliore(int s0, int sf,int straverse) const;
        std::vector<int> retourner_chemin(int sf,std::vector<int> pred) const;
        void calcul_tous_Ci();
        float calcul_Ci(int s) const;
        void Ci_normalise();

        //CALCULER TOUS
        void calculer_tous_indices();
        void calculer_tous_indices_normalises();

        //VULNERABILITE
        void vulnerabilite();
        void supprimer_arrete();
        void comparaison_centralites() const;

        //CONEXITE
        std::vector<int> BFS(int num_s0)const;
        void afficher_CC() const;
        void rechercher_CC();
        void quelle_CC(int s, int &num_CC) const;


        //SAUVEGARDE
        void sauvegarde_centralites();
        void ecrire_centralite(float* vecteur, std::ofstream &fichier);

        //CHARGEMENT
        void chargement_centralites(float* &prec_Cd, float* &prec_Cvp, float* &prec_Cp, float* &prec_Ci) const;
        void recuperer_centralite(float* &vecteur, std::ifstream &fichier) const;


};

#endif // GRAPHE_H
