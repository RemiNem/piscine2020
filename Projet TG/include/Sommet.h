#ifndef SOMMET_H
#define SOMMET_H
#include <vector>
#include <string>
class Sommet
{
    public:
        Sommet(int indice,std::string nom,int x0,int y0);
        virtual ~Sommet();

std::vector<Sommet*>sommet_adjacent;
int m_indice;
std::string m_nom;
int xs;
int ys;
};

#endif // SOMMET_H
