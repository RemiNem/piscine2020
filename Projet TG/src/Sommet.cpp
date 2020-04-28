#include "C:\Users\trani\OneDrive\Documents\GitHub\piscine2020\Projet TG\include\Sommet.h"

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


///getters
int Sommet::get_indice() const
{
    return m_indice;
}

std::string Sommet::get_nom() const
{
    return m_nom;
}
int Sommet::get_x() const
{
    return xs;
}
int Sommet::get_y() const
{
    return ys;
}

///setters

void Sommet::ajouter_adjacent(Sommet* s)
{
    sommet_adjacent.push_back(s);
}
