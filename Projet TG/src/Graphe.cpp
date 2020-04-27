#include "Graphe.h"

Graphe::Graphe(std::string txt)
{
    std::ifstream flux(txt);
    flux>>m_orientation;
    flux>>m_ordre;
    for(size_t i=0; i<m_ordre; i++) ///remplissage sommet
    {
        int indice,x,y;
        std::string nom;
        flux>>indice>>nom>>x>>y;
        Sommet *nouv=new Sommet(indice,nom,x,y);///nouveau sommet actualisé
        sommets.push_back(nouv);
    }
    flux>>m_taille;
arretes=new Arrete[m_taille];

    for(size_t i=0; i<m_taille; i++)
    {
        int s1,s2,indice;///sommet 1 sommet 2 et l'indice de l'arrete
        flux>>indice>>s1>>s2;
        sommets[s1]->sommet_adjacent.push_back(sommets[s2]);
        arretes[i].indice_s1=s1;
        arretes[i].indice_s2=s2;
        if(m_orientation==false)
        {
            sommets[s2]->sommet_adjacent.push_back(sommets[s1]);
        }
    }

    flux.close();
}

void Graphe::charger_ponderation(std::string txt)
{
    std::ifstream flux(txt);
    int taille;
    int indice_arrete;
    int poids;
    flux>>taille;

    for(size_t i=0; i<taille; i++)
    {
        flux>>indice_arrete>>poids;
        arretes[i].m_indice=i;
        arretes[i].m_poids=poids;
    }

    flux.close();
}

void Graphe::afficher() const
{

    if(m_orientation==true)
    {
        std::cout<<"Graphe oriente"<<std::endl;
    }
    else
    {
        std::cout<<"Graphe non oriente"<<std::endl;
    }


    std::cout<<" Ordre: "<<m_ordre<<std::endl;
    std::cout<<" Taille: "<<m_taille<<std::endl<<std::endl;

    std::cout<<"Liste d'adjacences : "<<std::endl;
    for(size_t i=0; i<sommets.size(); i++)
    {
        std::cout<<"  Sommet "<<sommets[i]->m_nom<<"("<<sommets[i]->xs<<","<<sommets[i]->ys<<")"<<" : ";///affiche numero sommet
        for(size_t j=0; j<sommets[i]->sommet_adjacent.size(); j++)
        {
            std::cout<<sommets[i]->sommet_adjacent[j]->m_nom<<" ";
        }
        std::cout<<std::endl;

    }
    std::cout<<std::endl;
    for(int i=0;i<m_taille;i++){
        std::cout<<arretes[i].m_indice<<" : "<<arretes[i].indice_s1<<" "<<arretes[i].indice_s2<<" Poids: "
        <<arretes[i].m_poids
        <<std::endl;
    }

}





Graphe::~Graphe()
{
    //dtor
}
