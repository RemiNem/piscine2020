#ifndef SOMMET_H
#define SOMMET_H
#include <vector>
#include <string>
class Sommet
{
    private:
        int m_indice;
        std::string m_nom;
        ///coords :
        int xs;
        int ys;
        int m_couleur;

    public:
        ///attribut
        std::vector<Sommet*> sommet_adjacent;

        ///construction/destruction
        Sommet(int indice,std::string nom,int x0,int y0);
        virtual ~Sommet();

        ///getters
        int get_indice() const;
        std::string get_nom() const;
        int get_x() const;
        int get_y() const;
        int get_degre() const;
        int get_couleur();

        ///setters
        void ajouter_adjacent(Sommet* s);
        void set_couleur(int frequ);


        ///supprimer successeur
        void supprimer_succ(int indice);

        ///test adjacent
        bool EstSuccesseurDe(int sommet);


};

#endif // SOMMET_H
