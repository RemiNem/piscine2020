#include "..\include\Sommet.h"

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

///suppr sucesseur
void Sommet::supprimer_succ(int indice)
{
    int i =0;
    int nbr_succ = sommet_adjacent.size();
    while(indice != sommet_adjacent[i]->get_indice())   // pour trouver le sommet a retirer des successeurs
    {
        i++;
    }
    Sommet *tampon = sommet_adjacent[nbr_succ-1]; //on intervertit le sommet a supprimer avec le dernier
    sommet_adjacent[nbr_succ-1]=sommet_adjacent[i];
    sommet_adjacent[i]=tampon;

    sommet_adjacent.pop_back();

}

///affichage successeurs
