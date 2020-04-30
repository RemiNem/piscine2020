#include "../include/Graphe.h"
#include "../include/svgfile.h"
#include "../include/fonctions.h"
#include <dirent.h>
#include <string.h>
#include <vector>
#include <map>
#include <bits/stdc++.h>


#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)


#define NON_MARQUE          0
#define MARQUE              1
#define INCONNU             -1
#define NORMALISE           (m_ordre - 1)
#define AUCUNE_PONDERATION (int(fichiers.size()) + 1)

#define VAR_LAMBDA 4

///DESTRUCTION
Graphe::~Graphe()
{
    //dtor
}

/// CONSTRUCTION
//default
Graphe::Graphe()
{

}

/// ------------------------CHARGEMENT GRAPHE--------------------------


void Graphe::charger_graphe(bool &graphe_charge)
{
    if(graphe_charge == true) //si le graphe a deja été chargé auparavent il faut reinitialiser le graphe
        reinitialiser_graphe();
    ///CHARGER GRAPHE TOPOLOGIQUE
    std::vector<std::string> fichiers = recuperer_fichiers("Load topologique"); // on récupère les fichiers du dossier des graphes topo
    std::cout << "Quel graphe souhaitez vous charger ? " << std::endl; //affichage de chacun des fichiers à selectionner
    for(size_t i = 0; i < fichiers.size(); ++i)
        std::cout << i + 1 << ") " << fichiers[i] << std::endl; // i + 1 car on affiche à partir de 1 et non 0
    int choix;
    //on recupere le choix du fichier a charger mais l'entree est blindee
    entree_blindee(1, int(fichiers.size()), choix);
    charger_topologique(fichiers[choix - 1].insert(0, "Load topologique/")); // chargement du graphe topologique

    ///CHARGER GRAPHE PODOLOGIQUE
    nomfichiergraphe = fichiers[choix - 1].erase(0, 17); //Recuperation du nom du fichier pour charger la ponderation
    changer_ponderation(); //chargement ponderation
    graphe_charge = true; //le graphe devient charge
}

void Graphe::changer_ponderation()
{
    int choix;
    std::vector<std::string> fichiers = recuperer_fichiers("Load podologique/" + nomfichiergraphe); //recuperation des ponderations qu'on a le droit de charger depuis le graphe topo actuel
    std::cout << "Quelle ponderaiton souhaitez vous charger ? " << std::endl; //recuperation du fichier ponderation a charger
    for(size_t i = 0; i < fichiers.size(); ++i)
        std::cout << i + 1 << ") " << fichiers[i] << std::endl;
    std::cout << fichiers.size() + 1 << ") Aucune" << std::endl; //si aucune ponderation souhaitee (ou si aucune disponible)
    //on recupere le choix de l'utilisateur en blindant l'entree
    entree_blindee(1, int(fichiers.size()) + 1, choix);
    //si on a choisi aucune ponderation, le poids de toutes les arretes doit etre initialisé a 0
    if (choix == AUCUNE_PONDERATION)
        for(size_t i = 0; i < m_taille; ++i)
            arretes[i].set_poids(1);
    else //sinon on charge la ponderation depuis le bon dossier
    {
        charger_ponderation(fichiers[choix - 1].insert(0, "Load podologique/" + nomfichiergraphe + "/"));
    }

}

///topologique
void Graphe::charger_topologique(std::string txt)
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
        Sommet *nouv=new Sommet(indice,nom,x,y);//nouveau sommet actualis�
        sommets.push_back(nouv);
    }
    //Arretes
    flux >> m_taille;
    for(size_t i = 0; i < m_taille; ++i)
    {
        Arrete a;
        a.set_indice(i);
        arretes.push_back(a);
    }

    for(size_t i=0; i < m_taille; i++)
    {
        int s1,s2,indice;//sommet 1 sommet 2 et l'indice de l'arrete
        //recup�ration
        flux >> indice >> s1 >> s2;
        sommets[s1]->ajouter_adjacent(sommets[s2]);
        arretes[i].set_indice_s1(s1);
        arretes[i].set_indice_s2(s2);
        //si le graphe n'est pas orient� l'arrete va dans les deux sens
        if(m_orientation==false)
        {
            sommets[s2]->ajouter_adjacent(sommets[s1]);
        }
    }
    //Fermeture fichier
    flux.close();
}


///pond�ration

void Graphe::charger_ponderation(std::string txt)
{
    std::ifstream flux(txt);
    int taille;
    int indice_arrete;
    float poids;
    flux>>taille;

    for(int i=0; i < taille; i++)
    {
        flux>>indice_arrete>>poids;
        arretes[i].set_indice(i);
        arretes[i].set_poids(poids);
    }

    flux.close();
}

void Graphe::reinitialiser_graphe()
{
    sommets.clear();
    arretes.clear();
}

/// -----------------AFFICHAGE---------------------

///afficher le graphe
void Graphe::afficher() const
{

    if(m_orientation==true)
    {
        std::cout<< std::endl<< "Graphe oriente"<<std::endl;
    }
    else
    {
        std::cout << std::endl << "Graphe non oriente" << std::endl;
    }

    std::cout << "Ordre: " << m_ordre << std::endl;
    std::cout << "Taille: " << m_taille << std::endl << std::endl;

    std::cout<<"Liste d'adjacences : "<<std::endl;
    for(size_t i=0; i < sommets.size(); i++)
    {
        std::cout<<"Sommet "<< sommets[i]->get_nom() <<"("<< sommets[i]->get_x() <<","<< sommets[i]->get_y() <<")"<<" : ";///affiche numero sommet

        for(size_t j = 0; j < sommets[i]->sommet_adjacent.size(); j++)
        {
            std::cout<< sommets[i]->sommet_adjacent[j]->get_nom() <<" ";
        }

        std::cout<<std::endl;

    }
    std::cout<<std::endl;

    afficher_arretes();
}

///affichage de toutes les arretes du graphe
void Graphe::afficher_arretes() const
{
    for(size_t i=0; i < m_taille; i++)
    {
        std::cout<< "Arrete "<< arretes[i].get_indice() <<" : "<< sommets[arretes[i].get_indice_s1()]->get_nom() << "-"
                 << sommets[arretes[i].get_indice_s2()]->get_nom() << "   Poids: "
                 << arretes[i].get_poids()
                 <<std::endl;
    }
}

///affichage graphe en html
//multiplier les coordonn�es par 100 pour l'echelle
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

        //Ajouter une fleche si le graphe est orient� (sommet 2 = pointe de la fl�che)
        if(m_orientation == true)
        {

            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*100, sommets[arretes[i].get_indice_s2()]->get_y()*100, sommets[arretes[i].get_indice_s2()]->get_x()*100 - 10, sommets[arretes[i].get_indice_s2()]->get_y()*100 - 10, "black");
            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*100, sommets[arretes[i].get_indice_s2()]->get_y()*100, sommets[arretes[i].get_indice_s2()]->get_x()*100 - 10, sommets[arretes[i].get_indice_s2()]->get_y()*100 + 10, "black");

        }
        //Ajouter le poids
        //on r�cupere les coordonn�es du point � mi chemin entre les deux sommets
        int x1 = sommets[arretes[i].get_indice_s1()]->get_x()*100;
        int y1 = sommets[arretes[i].get_indice_s1()]->get_y()*100;
        int x2 = sommets[arretes[i].get_indice_s2()]->get_x()*100;
        int y2 = sommets[arretes[i].get_indice_s2()]->get_y()*100;

        int x = (max(x1, x2) - min(x1,x2))/2 + min(x1,x2);
        int y = (max(y1,y2) - min(y1,y2))/2 + min(y1,y2);

        svgout.addText(x + 5, y - 5, arretes[i].get_poids(), "black");
    }
}
//affiche une centralite
void Graphe::afficher_centralite(float* vecteur) const
{
    //pour tous les sommets du graphe
    for(size_t i = 0; i < m_ordre; ++i)
    {
        //on affiche le nom
        std::cout << sommets[i]->get_nom() << " : " << vecteur[i] << std::endl;;
    }
    std::cout << std::endl;
}
//afficher tous les indices de centralite
void Graphe::afficher_tous_indices() const
{
    std::cout << std::endl << "La centralite de proximite des sommets : " << std::endl;
    afficher_centralite(centralite_proximite);
    std::cout << std::endl << "Le degre de centralite des sommets : " << std::endl;
    afficher_centralite(centralite_degre);
    std::cout << std::endl << "La centralite de vecteur propre des sommets : " << std::endl;
    afficher_centralite(centralite_vecteurp);
    std::cout << std::endl << "La centralite d'intermediarite des sommets : " << std::endl;
    afficher_centralite(centralite_intermediarite);
}


/// ----------GETTERS----------

///retourne l'arrete correspondante � ces deux sommets
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

///---------------SETTERS--------------------
void Graphe::set_m_taille(size_t taille)
{
    m_taille = taille;
}

/// -------------CALCUL DES INDICES DE CENTRALITE -------------

///CENTRALITE DE DEGRE

///calcul de la centralit� de degr� pour 1 sommet dont l'indice est pass� en parametre
float Graphe::calculer_Cd(int indice) const
{
    //1) r�cuperer le nombre d'arretes entrantes et sortantes du sommet = le degr�
    float degre = 0;
    //pour toutes les arretes du graphe
    for(size_t i = 0; i < m_taille; ++i)
    {
        //si l'une des extremit�es de cette arrete correspond � notre sommet alors le degr� augmente
        if(indice == arretes[i].get_indice_s1() || indice == arretes[i].get_indice_s2())
            degre++;
    }

    //2) Calcul de la centralit� normalis� de degr� du sommet
    float Cd = degre/NORMALISE;
    return Cd;
}

///Calcul de la  centralit� de tous les sommets (plac�es dans un tableau)
void Graphe::calculer_tous_Cd()
{
    //allocation du tab de centralite de degre
    centralite_degre = new float[m_ordre];
    //on calcule la centralit� de chacun des sommets du graphe
    for(size_t i = 0; i < m_ordre; ++i)
    {
        centralite_degre[i] = calculer_Cd(i);
    }
}


/// CENTRALITE DE PROXIMITE

///calcul de la centralit� de proximit� pour 1 sommet dont l'indice est pass� en parametre
float Graphe::calculer_Cp(int indice) const
{
    float Cp;
    int somme_distances = 0;
    int num_CC;
    quelle_CC(indice, num_CC); //recuperation de la composante connexe a laquelle appartient ce sommet
    //r�cuperer la somme des longueurs des plus courts chemins de s aux autres sommets du graphe
    for(size_t i = 0; i < CC[num_CC].size(); ++i) //seulement pour cette composante connexe
    {
        //si ce n'est pas s
        if(sommets[CC[num_CC][i]] != sommets[indice])
            somme_distances += Dijkstra(indice,CC[num_CC][i]); // on ajoute leur distance � la somme en faisant dijkstra sur la CC
    }
    if(somme_distances != 0)
        Cp = float(NORMALISE)/somme_distances;
    else
        Cp = 0;
    return Cp;
}

///calcul de la centralit� de proximite pour tous les sommets
void Graphe::calculer_tous_Cp()
{
    centralite_proximite = new float[m_ordre]; //Allocation
    for (size_t i = 0 ; i < m_ordre; ++i)
    {
        centralite_proximite[i] = calculer_Cp(i);
    }
}

///algorithme de Dijkstra
///DIJKSTRA SANS MODIF
int Graphe::Dijkstra(int debut, int fin) const
{
    //1) INITIALISATION
    std::vector<int> marquage((int)sommets.size(), NON_MARQUE); //aucun sommet n'est marqu�
    std::vector<float> distance_S0((float)sommets.size(), 999); //le tableau des distances � S0 (=debut)
    std::vector<int> preds((int)sommets.size(), INCONNU); //vecteur de predecesseur de chaque sommet
    Sommet* s = sommets[debut]; //varaible tampon
    int distance, d_min, id_d_min; //variables

    //distance de S0 � S0 = 0
    distance_S0[debut] = 0;
    marquage[debut] = MARQUE;

    //2) RECHERCHE DU CHEMIN.
    //tant qu'on a pas trouv� le plus court chemin jusqu'� la fin
    do
    {
        d_min = 999;
        //CHEMIN LE PLUS PROCHE DE S0
        //pour tous les sommets
        for(auto it:sommets)
        {
            //si le sommet est adjacent � s
            if((s->EstSuccesseurDe(it->get_indice()))&&(marquage[it->get_indice()] != MARQUE))
            {
                //std::cout << "on est bloque sur l'arrete : " << s->get_nom() << "-" << it->get_nom() << std::endl;
                //on r�cup�re la distance entre ces deux sommets (arrete[s,it] -> poids)
                distance = get_arrete(s->get_indice(), it->get_indice()).get_poids();
                //std::cout << "la distance de " << s->get_nom() << " a " << it->get_nom() << " est " << distance << std::endl;
                //Si c'est plus court d'aller de S0 � it en passant par s
                if(distance_S0[it->get_indice()] > distance_S0[s->get_indice()] + distance)
                {
                    //on met � jour la distance S0 -> it avec celle qui passe par s
                    distance_S0[it->get_indice()] = distance_S0[s->get_indice()] + distance;
                    //predecesseur de it devient s
                    preds[it->get_indice()] = s->get_indice();
                }
            }
            //std::cout << "bloques sur le sommet : " << it->get_nom() << std::endl;
        }

        //le plus proche sommet de S0 qui n'est pas marqu�
        for(size_t i=0; i < sommets.size(); ++i)
        {
            //si ce sommet n'est pas marqu�
            if(marquage[i] != MARQUE)
            {
                //et si c'est le plus proche de S0
                if(distance_S0[i]<d_min)
                {
                    //on change la distance minimale � S0
                    d_min = distance_S0[i];
                    //on garde en m�moire son identifiant
                    id_d_min=i;
                }
            }
        }
        //le sommet le plus proche qui n'a pas encore �t� �tudi� est le prochain que nous allons parcourir
        s = sommets[id_d_min];
        //on marque le sommet s
        marquage[s->get_indice()] = MARQUE;
    }
    while(marquage[fin] != MARQUE);

    //on retourn la distance de debut � fin
    return distance_S0[fin];
}


/// CENTRALITE DE VECTEUR PROPRE

/// Calcul de Cvp
void Graphe::calculer_Cvp()
{
    // initialisation : on passe l'indice des sommets � 1
    centralite_vecteurp = new float[m_ordre];
    for(size_t i=0; i<m_ordre; i++)
    {
        centralite_vecteurp[i]=1;
    }

    // tableau centralit� "intermediaire" pour calcul
    float centralite[m_ordre] = {0};

    float lambda_p = 0;
    float lambda =100;
    float lambda_diff = 100;


    float somme_ci =0;

    do
    {
        for(size_t i=0; i<m_ordre; i++) // va permettre d'affecter un indice de centralite vp � tous les sommets
        {

            for(size_t j =0; j < sommets[i]->sommet_adjacent.size(); j++)  // va faire la somme de l'indice de centralite vp des sommets adjacents au sommet i
            {

                centralite[i] = centralite[i] + centralite_vecteurp[sommets[i]->sommet_adjacent[j]->get_indice()];
            }
        }


        lambda_p = lambda;

        for(size_t i =0; i < m_ordre; i++)    // permet d'avoir la somme des Ci^2
        {
            somme_ci= somme_ci + centralite[i]*centralite[i];
        }

        lambda = sqrt(somme_ci);

        for(size_t i=0; i<m_ordre; i++) // enfin, on recalcule les Cvp
        {
            centralite_vecteurp[i]= centralite[i]/lambda;
        }
        /* std::cout << "lambda vaut : " << lambda << std::endl;
         std::cout << "lambda prec : " << lambda_p << std::endl;*/

        lambda_diff = abs(lambda_p-lambda);


    }
    while(lambda_diff > VAR_LAMBDA);
}


/// CENTRALITE D'INTERMEDIARITE
//= la fréquence avec laquelle un sommet se trouve sur les plus courts chemins reliant deux autre sommets quelconques du graphe
//calcule la centralite d'intermediarite pour un sommet
float Graphe::calcul_Ci(int s) const
{
    float somme_Ci = 0;
    int num_CC;
    quelle_CC(s, num_CC);//récupere à quelle composante connexe appartient le sommet
    //ne lance dijkstra que pour les sommets appartenant à cette CC
    for(size_t i = 0; i < CC[num_CC].size(); ++i)
    {
        for(size_t j = 0; j < CC[num_CC].size(); ++j)
            if(CC[num_CC][j] < CC[num_CC][i])
                somme_Ci += Dijkstra_ameliore(CC[num_CC][j], CC[num_CC][i], s);
    }
    return somme_Ci;

}

void Graphe::calcul_tous_Ci()
{
    centralite_intermediarite = new float[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
    {
        centralite_intermediarite[i] = calcul_Ci(i);
    }
}

//algorithme de Dijkstra adapté
float Graphe::Dijkstra_ameliore(int s0, int sf,int straverse) const
{
    std::vector<int>branche(0);
    std::vector<int>branche0(0);
    std::vector<bool>marque(m_ordre,false);
    int n_marque=0;///les sommets marqués sont ceux qui ont fait parti d'un chemin
    float nb_chemin=0;
    float Ci=0;
    bool stop=false;
    while(stop==false) ///condition d'arret{
    {

        std::vector<int>pred(m_ordre,-1);///liste des predecesseurs
        std::vector<bool>decouvert(m_ordre,false);
        std::vector<int>distance(m_ordre,32767);///distance absolue du sommet en cours par rapport a un sommet numero i

        int dtot=0;///distance parcourue
        int sa;
        int ss=s0;
        int sommet_decouverts=0;

        do
        {
            decouvert[ss]=true;

            sommet_decouverts++;

            for(size_t i=0; i<sommets[ss]->sommet_adjacent.size(); i++) ///on parcourt les sommets adjacents des sommets en cours
            {
                sa=sommets[ss]->sommet_adjacent[i]->get_indice();///on note le numero de sommet

                if(decouvert[sa]==false) ///si le sommet n'est pas découvert
                {
                    if((get_arrete(ss,sa).get_poids()+dtot)<distance[sa])
                    {
                        distance[sa]=get_arrete(ss,sa).get_poids()+dtot;
                        pred[sa]=ss;
                    }
                }
            }
            int minm=32767;
            int minn=32767;
            int sm=0,snm=0;
            for(size_t i=0; i<distance.size(); i++)
            {
                if(distance[i]<minm&&decouvert[i]==false&&marque[i]==true)///ici on determine la distance minimale de tous les sommets marqués
                {
                    minm=distance[i];
                    sm=i;
                }
                if(distance[i]<minn&&decouvert[i]==false&&marque[i]==false)///ici on determine la distance minimale de tous les sommets non marqués
                {
                    minn=distance[i];
                    snm=i;
                }
            }

            if(minn<=minm)///si on en est au 2eme chemin le plus cours ou plus alors on se deplace dans un sommet pas encore marque si sa distance ne depasse pas celui marque
            {
                ss=snm;
            }
            else
            {
                ss=sm;
            }
            dtot=distance[ss];///on actualise la distance totale

        }
        while(sommet_decouverts != int(m_ordre));  ///tant que il reste des sommetes decouverts

        branche=retourner_chemin(sf,pred);///stocke le chemin dans la branche
        if(nb_chemin==0)
        {
            branche0=branche;
        }
        if(nb_chemin>0&&branche0==branche)
        {
            stop=true;   ///on s'arrete quand la branche est la meem que celle du debut
        }
        for(size_t i=0; i<branche.size(); i++)
        {
            if(stop==false)
                if(sommets[branche[i]]->get_indice()==straverse&&stop==false) ///si le sommet est dans un chemin
                {

                    Ci++;
                }
            marque[branche[i]]=true;
        }

        n_marque=0;

        for(size_t i=0; i<m_ordre; i++) ///on met a jour le nb de sommet marque
        {
            if(marque[i]==true)
                n_marque++;
        }
        if(stop==false)///a chaque fin de cette boucle un nouveau chemin est trouve
            nb_chemin++;
    }
    return Ci/nb_chemin;
}

std::vector<int> Graphe::retourner_chemin(int sf,std::vector<int> pred) const///affiche l'arborescence a partir de la liste des predecesseurs
{
    int n;
    std::vector<int>branche(0);

    n=pred[sf];
    if(n!=-1)
    {
        //std::cout<<sommets[sf]->get_nom();
        branche.push_back(sf);
        while(n!=-1)///on remonte tous les predessesseurs jusqu'a trouver le sommer initial
        {
            branche.push_back(n);
            n=pred[n];
        }
    }
    return branche;
}


/// CALCULER TOUS INDICES
void Graphe::calculer_tous_indices()
{
    calculer_tous_Cd();
    calculer_tous_Cp();
    calculer_Cvp();
    calcul_tous_Ci();
}



//VULNERABILITE

void Graphe::vulnerabilite()
{
    //1) SUPPRIMER UNE ARRETE
    supprimer_arrete();
    //2) REGARDER LA CONNEXITE
    //scinder recherche et affichage
    //recherche_afficher_CC();
    rechercher_CC();
    afficher_CC();
    //3) RECALCULER LES NOUVEAUX INDICES DE CENTRALITE
    afficher();
    afficher_graphe_internet();
    calculer_tous_indices();
    //4) COMPARER CES CALCULS AVEC LES ANCIENS (dans la sauvegarde)
    //on recupere dans la sauvegarde les anciens indices de centralite
    float* prec_Cd = new float [m_ordre];
    float* prec_Cvp = new float [m_ordre];
    float* prec_Cp = new float [m_ordre];
    float* prec_Ci = new float[m_ordre];
    chargement_centralites(prec_Cd, prec_Cvp, prec_Cp, prec_Ci);
    //5) INTERPRETER LES RESULTATS
}


void Graphe::supprimer_arrete()
{
    int indice;
    Arrete tampon;
    afficher_arretes();
    std::cout << std::endl <<"Indiquez le numero de l'arrete que vous souhaitez vous supprimer  " << std::endl;
    entree_blindee(0, m_taille, indice);
    //on interverti la case a suppr avec la derniere case du vecteur
    arretes[m_taille - 1].set_indice(indice);
    tampon = arretes[indice];
    arretes[indice] = arretes[m_taille - 1];
    arretes[m_taille - 1] = tampon;
    //supprimer le voisin au bout de cette arrete
    sommets[arretes[m_taille-1].get_indice_s1()]->supprimer_succ(arretes[m_taille-1].get_indice_s2());
    sommets[arretes[m_taille-1].get_indice_s2()]->supprimer_succ(arretes[m_taille-1].get_indice_s1());
    //on supprime la derniere case du vecteur
    arretes.pop_back();
    m_taille--;

    std::cout << std::endl << "Les nouvelles arretes : " << std::endl;
    afficher_arretes();
}

/// CONNEXITE

std::vector<int> Graphe::BFS(int num_s0)const           // source : Mme PALASI
{
    /// déclaration de la file(queue)
    std::queue<const Sommet*>file;
    /// pour le marquage
    /// couleurs [i] indique si le sommet numéro i est non marqué (valeur 0)
    /// ou marqué (valeur 1)
    std::vector<int> couleurs((int)sommets.size(),0);
    ///pour noter les prédécesseurs : on note les numéros des prédécesseurs
    ///(on pourrait stocker des pointeurs sur ...)
    ///preds[i] donnera le numéro du prédécesseur du sommet i
    ///dans les chemins obtenus
    ///Au départ les sommets n’ont pas de prédécesseur (valeur -1)
    ///Le sommet initial n’aura pas de prédécesseur. Les sommets non découverts
    ///(non accessibles à partir du sommet initial) non plus.
    std::vector<int> preds((int)sommets.size(),-1);
    ///étape initiale : on enfile et on marque le sommet initial
    file.push(sommets[num_s0]);
    couleurs[num_s0]=1;
    const Sommet*s;

    ///tant que la file n'est pas vide
    while(!file.empty())
    {
        ///on défile le prochain élément de la file
        s=file.front();//on récupère le premier élement de la file
        file.pop(); // on l’enlève de la file

        /// on va parcourir les successeurs du sommet défilé :
        ///pour chaque successeur du sommet défilé
        for(auto succ:s->sommet_adjacent)
        {
            if(couleurs[succ->get_indice()]==0) ///s'il n'est pas marqué
            {
                couleurs[succ->get_indice()]=1; ///on le marque
                ///on note son prédecesseur (= le sommet défilé)
                preds[succ->get_indice()]= s->get_indice();
                file.push(succ);///on le met dans la file
            }
        }
    }
    return preds;
}

/// COMPOSANTES CONNEXES
//renvoie un vecteur avec les differentes composantes connexes du graphe
void Graphe::rechercher_CC()
{
    size_t num=0;
    bool test;
    int ncc=0;
    std::vector<int> une_cc; //une seule composante connexe
    ///pour noter les numéros de CC
    std::vector<int> cc(sommets.size(),-1);
    CC.clear(); //on clear le vecteur de CC avant tout calcul
    do
    {
        cc[num]=num;
        une_cc.clear();
        une_cc.push_back(num);
        ncc++;

        ///lancement d'un BFS sur le sommet num
        std::vector<int> arbre_BFS=BFS(num);
        ///affichage des sommets decouverts lors du parcours (ceux qui ont un predecesseur
        for(size_t i=0; i<arbre_BFS.size(); ++i)
        {
            if ((i!=num)&&(arbre_BFS[i]!=-1))
            {
                cc[i]=num;
                une_cc.push_back(i);
            }
        }
        ///recherche d'un sommet non explorÈ
        ///pour relancer un BFS au prochain tour
        test=false;
        for(size_t i=0; i<sommets.size(); ++i)
        {
            if (cc[i]==-1)
            {
                num=i;
                test=true;
                break;
            }
        }
        CC.push_back(une_cc);
    }
    while(test==true);
}

//affiche les differentes composantes connexes reçues en parametre
void Graphe::afficher_CC() const
{
    for(size_t i = 0; i < CC.size(); ++i)
    {
        std::cout << "Composante connexe " << i << ": ";
        for(size_t j = 0; j < CC[i].size(); ++j)
            std::cout << sommets[CC[i][j]]->get_nom() << " ";
        std::cout << std::endl;
    }
}

//renvoie le numero de la composante connexe a laquelle appartient le sommet passé en parametre
void Graphe::quelle_CC(int s, int &num_CC) const
{
    for(size_t i = 0; i < CC.size(); ++i) //pour chacune des composantes connexes du graphe
    {
        for(size_t j = 0; j < CC[i].size(); ++j) //pour chacun des indices de sommets de cette CC
            if(s == CC[i][j])//si note sommet appartient a cette CC
                num_CC = i; //alors num_CC prend la valeur de la CC correspondante
    }
}

///SAUVEGARDE CENTRALITE

void Graphe::sauvegarde_centralites()
{
    std::ofstream sauv{"centralites.txt"}; //creation d'un fichier texte en ecriture
    if(!sauv)
        erreur("Impossible d'ouvrir le fichier centralites.txt");
    else
    {
        //CENTRALITE DE DEGRE
        sauv << "centralite_degre" << std::endl;
        ecrire_centralite(centralite_degre, sauv);
        //CENTRALITE DE VECTEUR PROPRE
        sauv << "centralite_vecteurp" << std::endl;
        ecrire_centralite(centralite_vecteurp, sauv);
        //CENTRALITE DE PROXIMITE
        sauv << "centralite_proximite" << std::endl;
        ecrire_centralite(centralite_proximite, sauv);
        //CENTRALITE D'INTERMEDIARITE
        sauv << "centralite_intermediarite" << std::endl;
        ecrire_centralite(centralite_intermediarite, sauv);
        sauv.close();
    }
}

void Graphe::ecrire_centralite(float* vecteur, std::ofstream &fichier)
{
    for(size_t i = 0; i < m_ordre; ++i)
        fichier << vecteur[i] << std::endl;
}





///CHARGEMENT CENTRALITE
void Graphe::chargement_centralites(float* &prec_Cd, float* &prec_Cvp, float* &prec_Cp, float* &prec_Ci)
{
    std::string centralite;
    std::ifstream charg{"centralites.txt"};
    if(!charg)
        erreur("Impossible d'ouvrir le fichier de sauvegarde des centralites");
    else
    {
        charg >> centralite;
        if(centralite == "centralite_degre") //DEGRE
            recuperer_centralite(prec_Cd, charg);
        else if(centralite == "centralite_vecteurp") //VECTEUR PROPRE
            recuperer_centralite(prec_Cvp, charg);
        else if(centralite == "centralite_proximite") //PROXIMITE
            recuperer_centralite(prec_Cp, charg);
        else if(centralite == "centralite_intermediarite") //INTERMEDIARITE
            recuperer_centralite(prec_Ci, charg);
    }
}

void Graphe::recuperer_centralite(float* &vecteur, std::ifstream &fichier)
{
    for(size_t i = 0; i < m_ordre; ++i)
        fichier >> vecteur[i];
}






