#include "Sommet.h"

Sommet::Sommet(int indice,std::string nom,int x0,int y0)
{
    m_indice=indice;
    xs=x0;
    ys=y0;
    m_nom=nom;
}

Sommet::~Sommet()
{
    //dtor
}
