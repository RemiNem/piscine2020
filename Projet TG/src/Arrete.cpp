#include "../include/Arrete.h"

///CONSTRUCTEURS / DESTRUCTEUR
//constructeur par default

Arrete::Arrete()
{

}

//constructeur avec parametres
Arrete::Arrete(int indice,int s1,int s2)
{
    indice_s1=s1;
    indice_s2=s2;
    m_indice=indice;
}
//destructeur

Arrete::~Arrete()
{
    //dtor
}
/// GETTERS

int Arrete::get_indice() const
{
    return m_indice;
}
int Arrete::get_indice_s1() const
{
    return indice_s1;
}
int Arrete::get_indice_s2() const
{
    return indice_s2;
}
int Arrete::get_poids() const
{
    return m_poids;
}

/// SETTERS

void Arrete::set_indice_s1(int indice)
{
    indice_s1 = indice;
}

void Arrete::set_indice_s2(int indice)
{
    indice_s2 = indice;
}

void Arrete::set_indice(int i)
{
    m_indice = i;
}

void Arrete::set_poids(int p)
{
    m_poids = p;
}
