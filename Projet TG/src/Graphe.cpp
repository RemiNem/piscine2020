#include "Graphe.h"

Graphe::Graphe(std::string txt)
{
std::ifstream flux(txt);
flux>>orientation;
flux>>ordre;
 for(size_t i=0; i<ordre; i++) ///remplissage sommet
        {
            int indice,x,y;
            std::string nom;
            flux>>indice>>nom>>x>>y;
            Sommet *nouv=new Sommet(indice,nom,x,y);///nouveau sommet actualisé
            sommets.push_back(nouv);
        }
flux>>m_taille;
///allocation de la matrice
initialiser_matrices();

       for(size_t i=0;i<m_taille;i++){
        int s1,s2,indice;///sommet 1 sommet 2 et l'indice de l'arrete
        flux>>indice>>s1>>s2;
        matrice_indice[s1][s2]=indice;
        sommets[s1]->sommet_adjacent.push_back(sommets[s2]);
        if(orientation==false){
            sommets[s2]->sommet_adjacent.push_back(sommets[s1]);
        }
       }

flux.close();
}

void Graphe::charger_ponderation(std::string txt){
std::ifstream flux(txt);
int taille;
flux>>taille;
for(size_t i=0;i<taille;i++){
    flux
}

flux.close();
}

void Graphe::afficher() const
{

if(orientation==true){
    std::cout<<"Graphe oriente"<<std::endl;}
    else{std::cout<<"Graphe non oriente"<<std::endl;}


    std::cout<<" Ordre: "<<ordre<<std::endl;
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
}

void Graphe::initialiser_matrices(){
matrice_indice=new int*[ordre];///on alloue
matrice_poids=new int*[ordre];
for(int s=0;s<ordre;s++)
    {
    matrice_indice[s]=new int[ordre];
    matrice_poids[s]=new int[ordre];
    }
    for(int s1=0;s1<ordre;s1++){///on rempli par defaut
            for(int s2=0;s2<ordre;s2++){
    matrice_indice[s1][s2]=-1;
    matrice_poids[s1][s2]=-1;

    }}
}

void Graphe::afficher_matrice_indice(){
std::cout<<"   ";
for(int i=0;i<m_taille;i++)
{std::cout<<sommets[i]->m_nom<<"   ";}
std::cout<<std::endl;
for(int i=0;i<m_taille;i++){
        std::cout<<sommets[i]->m_nom<<" ";
    for(int a=0;a<m_taille;a++){
  std::cout<<matrice_indice[i][a]<<"  ";

}std::cout<<std::endl;

}
}

Graphe::~Graphe()
{
    //dtor
}
