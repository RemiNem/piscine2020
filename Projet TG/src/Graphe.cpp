#include "Graphe.h"
#include "svgfile.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

#define NON_MARQUE  0
#define MARQUE      1
#define INCONNU     -1

///DESTRUCTION
Graphe::~Graphe()
{
    //dtor
}

/// ------------------------CHARGEMENT GRAPHE-----------------

///topologique
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

///pondération
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

/// -----------------AFFICHAGE---------------------

///afficher le graphe
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

///affichage degre de centralité
void Graphe::afficher_degre_centralite() const
{
    std::cout << "La centralite de degre des sommets : " << std::endl;
    //pour tous les sommets du graphe
    for(size_t i = 0; i < m_ordre; ++i)
    {
        //on affiche le nom
        std::cout << sommets[i]->get_nom() << " : " << centralite_degre[i] << std::endl;;
    }
    std::cout << std::endl << std::endl;
}

///affichage graphe en html
//multiplier les coordonnées par 100 pour l'echelle
void Graphe::afficher_graphe_internet() const
{
    Svgfile svgout;
    //SOMMETS
    for(size_t i = 0; i < m_ordre; ++i)
    {
        svgout.addDisk(sommets[i]->get_x()*100, sommets[i]->get_y()*100, 5, "black"); //placer le sommet
        svgout.addText(sommets[i]->get_x()*100, sommets[i]->get_y()*100 - 5, sommets[i]->get_nom(), "black"); //Afficher son nom
    }
    //ARRETES + POIDS
    for(size_t i = 0; i < m_taille; ++i)
    {
        //Arrete
        svgout.addLine(sommets[arretes[i].get_indice_s1()]->get_x()*100, sommets[arretes[i].get_indice_s1()]->get_y()*100, sommets[arretes[i].get_indice_s2()]->get_x()*100, sommets[arretes[i].get_indice_s2()]->get_y()*100, "black");

        //Ajouter une fleche si le graphe est orienté (sommet 2 = pointe de la flèche)
        if(m_orientation == true)
        {
            /*
            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*100, sommets[arretes[i].get_indice_s2()]->get_y()*100, sommets[arretes[i].get_indice_s2()]->get_x()*100 - 10, sommets[arretes[i].get_indice_s2()]->get_y()*100 - 10, "black");
            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*100, sommets[arretes[i].get_indice_s2()]->get_y()*100, sommets[arretes[i].get_indice_s2()]->get_x()*100 - 10, sommets[arretes[i].get_indice_s2()]->get_y()*100 + 10, "black");
            */
        }
        //Ajouter le poids
        //on récupere les coordonnées du point à mi chemin entre les deux sommets
        int x1 = sommets[arretes[i].get_indice_s1()]->get_x()*100;
        int y1 = sommets[arretes[i].get_indice_s1()]->get_y()*100;
        int x2 = sommets[arretes[i].get_indice_s2()]->get_x()*100;
        int y2 = sommets[arretes[i].get_indice_s2()]->get_y()*100;

        int x = (max(x1, x2) - min(x1,x2))/2 + min(x1,x2);
        int y = (max(y1,y2) - min(y1,y2))/2 + min(y1,y2);

        svgout.addText(x + 5, y - 5, arretes[i].get_poids(), "black");
    }
}







/// -------------CALCUL DES INDICES DE CENTRALITE -------------

///CENTRALITE DE DEGRE

///calcul de la centralité de degré pour 1 sommet dont l'indice est passé en parametre
float Graphe::calculer_Cd(int indice) const
{
    //1) récuperer le nombre d'arretes entrantes et sortantes du sommet = le degré
    float degre = 0;
    //pour toutes les arretes du graphe
    for(size_t i = 0; i < m_taille; ++i)
    {
        //si l'une des extremitées de cette arrete correspond à notre sommet alors le degré augmente
        if(indice == arretes[i].get_indice_s1() || indice == arretes[i].get_indice_s2())
            degre++;
    }
    /*
    //si le graphe est non orienté on divise l'ordre par 2 car chaque arete est comptée deux fois
    if(m_orientation == false)
        degre = degre/2;
    */

    //2) Calcul de la centralité normalisé de degré du sommet
    float Cd = degre/(m_ordre - 1);
    return Cd;
}

///Calcul de la  centralité de tous les sommets (placées dans un tableau)
void Graphe::calculer_tous_Cd()
{
    //allocation du tab de centralite de degre
    centralite_degre = new float[m_ordre];

    std::cout << std::endl << std::endl;
    //on calcule la centralité de chacun des sommets du graphe
    for(size_t i = 0; i < m_ordre; ++i)
    {
        centralite_degre[i] = calculer_Cd(i);
    }
}

/// CENTRALITE DE PROXIMITE

///algorithme de Dijkstra

int Graphe::Dijkstra(int debut, int fin) const
{
    //1) INITIALISATION
    std::vector<int> marquage((int)sommets.size(), NON_MARQUE); //aucun sommet n'est marqué
    std::vector<int> distance_S0((int)sommets.size(), 999); //le tableau des distances à S0 (=debut)
    std::vector<int> preds((int)sommets.size(), INCONNU); //vecteur de predecesseur de chaque sommet
    Sommet* s = sommets[debut]; //varaible tampon
    int distance, d_min, id_d_min; //variables

    //distance de S0 à S0 = 0
    distance_S0[debut] = 0;
    marquage[debut] = MARQUE;

    //2) RECHERCHE DU CHEMIN.
    //tant qu'on a pas trouvé le plus court chemin jusqu'à la fin
    do
    {
        d_min = 999;
        //CHEMIN LE PLUS PROCHE DE S0
        //pour tous les sommets
        for(auto it:sommets)
        {
            //si le sommet est adjacent à s
            if(EstSuccesseurDe(s->get_indice(), it->get_indice()))
            {
                //on récupère la distance entre ces deux sommets (arrete[s,it] -> poids)
                distance = get_arrete(s->get_indice(), it->get_indice()).get_poids();
                //Si c'est plus court d'aller de S0 à it en passant par s
                if(distance_S0[it->get_indice()] > distance_S0[s->get_indice()] + distance)
                {
                    //on met à jour la distance S0 -> it avec celle qui passe par s
                    distance_S0[it->get_indice()] = distance_S0[s->get_indice()] + distance;
                    //predecesseur de it devient s
                    preds[it->get_indice()] = s->get_indice();
                }
            }
        }

        //le plus proche sommet de S0 qui n'est pas marqué
        for(size_t i=0; i < sommets.size(); ++i)
        {
            //si ce sommet n'est pas marqué
            if(marquage[i] != MARQUE)
            {
                //et si c'est le plus proche de S0
                if(distance_S0[i]<d_min)
                {
                    //on change la distance minimale à S0
                    d_min = distance_S0[i];
                    //on garde en mémoire son identifiant
                    id_d_min=i;
                }
            }
        }
        //le sommet le plus proche qui n'a pas encore été étudié est le prochain que nous allons parcourir
        s = sommets[id_d_min];
        //on marque le sommet s
        marquage[s->get_indice()] = MARQUE;
    }while(marquage[fin] != MARQUE);

    //on retourn la distance de debut à fin
    return distance_S0[fin];
}

///Cherche à savoir si s1 est adjacent à s2 (s1 -> s2 si graphe orienté)
bool Graphe::EstSuccesseurDe(int s1, int s2) const
{
    //GRAPHE ORIENTE
    if(m_orientation == true)
    {
        //pour toutes les arretes du graphe
        for (size_t i = 0; i < m_taille; ++i)
        {
            //si on a une arrete s1 -> s2
            if(s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())
                return true; // alors s2 est successeur de s1
        }
    }
    //GRAPHE NON ORIENTE
    else
    {
        for (size_t i = 0; i < m_taille; ++i)
        {
            //si s1 est lié à s2
            if((s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())||(s2 == arretes[i].get_indice_s1() && s1 == arretes[i].get_indice_s2()))
                return true;
        }
    }
    //les sommets ne sont pas adjacents
    return false;
}

/// ----------GETTERS----------

///retourne l'arrete correspondante à ces deux sommets
Arrete Graphe::get_arrete(int s1, int s2) const
{
    //GRAPHE ORIENTE
    if(m_orientation == true)
    {
        for(size_t i = 0; i < m_taille; ++i)
        {
            if(s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())
                return arretes[i];
        }
    }
    //GRAPHE NON ORIENTE
    else
    {
        for (size_t i = 0; i < m_taille; ++i)
        {
            if((s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())||(s2 == arretes[i].get_indice_s1() && s1 == arretes[i].get_indice_s2()))
                return arretes[i];
        }
    }
}




