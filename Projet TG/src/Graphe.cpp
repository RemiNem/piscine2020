#include "Graphe.h"

///CHARGEMENT GRAPHE
Graphe::Graphe(std::string txt)
{
    std::ifstream flux(txt);
    //orientation
    flux >> m_orientation;
    //ordre
    flux >> m_ordre;
    ///remplissage sommet
    for(size_t i=0; i<m_ordre; i++)
    {
        int indice,x,y;
        std::string nom;
        flux>>indice>>nom>>x>>y;
        Sommet *nouv=new Sommet(indice,nom,x,y);//nouveau sommet actualisé
        sommets.push_back(nouv);
    }
    //Arretes
    flux >> m_taille;
    arretes=new Arrete[m_taille];

    for(size_t i=0; i < m_taille; i++)
    {
        int s1,s2,indice;//sommet 1 sommet 2 et l'indice de l'arrete
        //recupération
        flux >> indice >> s1 >> s2;
        sommets[s1]->ajouter_adjacent(sommets[s2]);
        arretes[i].set_indice_s1(s1);
        arretes[i].set_indice_s2(s2);
        //si le graphe n'est pas orienté l'arrete va dans les deux sens
        if(m_orientation==false)
        {
            sommets[s2]->ajouter_adjacent(sommets[s1]);
        }
    }
    //Fermeture fichier
    flux.close();
}

///PONDERATION

void Graphe::charger_ponderation(std::string txt)
{
    std::ifstream flux(txt);
    int taille;
    int indice_arrete;
    int poids;
    flux>>taille;

    for(int i=0; i < taille; i++)
    {
        flux>>indice_arrete>>poids;
        arretes[i].set_indice(i);
        arretes[i].set_poids(poids);
    }

    flux.close();
}

///AFFICHAGE
void Graphe::afficher() const
{

    if(m_orientation==true)
    {
        std::cout<<"Graphe oriente"<<std::endl;
    }
    else
    {
        std::cout << "Graphe non oriente" << std::endl;
    }

    std::cout << " Ordre: " << m_ordre << std::endl;
    std::cout << " Taille: " << m_taille << std::endl << std::endl;

    std::cout<<"Liste d'adjacences : "<<std::endl;
    for(size_t i=0; i < sommets.size(); i++)
    {
        std::cout<<"  Sommet "<< sommets[i]->get_nom() <<"("<< sommets[i]->get_x() <<","<< sommets[i]->get_y() <<")"<<" : ";///affiche numero sommet

        for(size_t j = 0; j < sommets[i]->sommet_adjacent.size(); j++)
        {
            std::cout<< sommets[i]->sommet_adjacent[j]->get_nom() <<" ";
        }

        std::cout<<std::endl;

    }
    std::cout<<std::endl;

    for(size_t i=0; i < m_taille; i++)
    {
        std::cout<< arretes[i].get_indice() <<" : "<< arretes[i].get_indice_s1() <<" "<< arretes[i].get_indice_s2() << " Poids: "
                 << arretes[i].get_poids()
                 <<std::endl;
    }

}

///DESTRUCTION
Graphe::~Graphe()
{
    //dtor
}


