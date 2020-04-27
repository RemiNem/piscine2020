#ifndef SOMMET_H
#define SOMMET_H
#include <vector>
#include <string>
class Sommet
{
    private:
        int m_indice;
        std::string m_nom;
        //coords
        int xs;
        int ys;

    public:
        //attribut
        std::vector<Sommet*> sommet_adjacent;

        ///construction/destruction
        Sommet(int indice,std::string nom,int x0,int y0);
        virtual ~Sommet();

        ///getters
        int get_indice() const;
        std::string get_nom() const;
        int get_x() const;
        int get_y() const;

        ///setters
        void ajouter_adjacent(Sommet* s);
};

#endif // SOMMET_H
