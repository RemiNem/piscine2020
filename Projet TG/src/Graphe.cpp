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
#define DX                  26
#define DY                  8
#define ECHELLE             70

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
    //initialiser le vecteur de couleurs
    charger_couleurs();
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
void Graphe::afficher_graphe_internet()
{
    Svgfile svgout;
    attribuer_couleur(); //on attribue la couleur du sommet a chaque sommet
    //SOMMETS
    for(size_t i = 0; i < m_ordre; ++i)
    {
        svgout.addDisk(sommets[i]->get_x()*ECHELLE, sommets[i]->get_y()*ECHELLE, 5, coloration[sommets[i]->get_couleur()]); //placer le sommet
        svgout.addText(sommets[i]->get_x()*ECHELLE, sommets[i]->get_y()*ECHELLE - 5, sommets[i]->get_nom(), "black"); //Afficher son nom
    }
    //ARRETES + POIDS
    for(size_t i = 0; i < m_taille; ++i)
    {
        //Arrete
        svgout.addLine(sommets[arretes[i].get_indice_s1()]->get_x()*ECHELLE, sommets[arretes[i].get_indice_s1()]->get_y()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE, "black");

        //Ajouter une fleche si le graphe est orient� (sommet 2 = pointe de la fl�che)
        if(m_orientation == true)
        {

            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE - 10, sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE - 10, "black");
            svgout.addLine(sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE, sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE - 10, sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE + 10, "black");

        }
        //Ajouter le poids
        //on r�cupere les coordonn�es du point � mi chemin entre les deux sommets
        int x1 = sommets[arretes[i].get_indice_s1()]->get_x()*ECHELLE;
        int y1 = sommets[arretes[i].get_indice_s1()]->get_y()*ECHELLE;
        int x2 = sommets[arretes[i].get_indice_s2()]->get_x()*ECHELLE;
        int y2 = sommets[arretes[i].get_indice_s2()]->get_y()*ECHELLE;

        int x = (max(x1, x2) - min(x1,x2))/2 + min(x1,x2);
        int y = (max(y1,y2) - min(y1,y2))/2 + min(y1,y2);

        svgout.addText(x + 5, y - 5, arretes[i].get_poids(), "black");
    }
}

void Graphe::afficher_centralite(float* vecteur, int dx, int dy) const
{
    int descendre = 1;
    //pour tous les sommets du graphe
    for(size_t i = 0; i < m_ordre; ++i)
    {
        //on affiche le nom
        gotoligcol(dy + descendre, 10);
        std::cout << "Sommet " << sommets[i]->get_nom() << ": ";
        gotoligcol(dy + descendre, dx);
        std::cout << vecteur[i];
        ++descendre;
    }
}



//afficher tous les indices de centralite
void Graphe::afficher_tous_indices(int dy, int dx) const
{
    gotoligcol(5, 30);
    std::cout << "INDICES DE CENTRALITE NON NORMALISES";
    gotoligcol(dy, dx + 4);
    printf("Cp");
    afficher_centralite(centralite_proximite, dx, dy);
    gotoligcol(dy, dx + 17);
    printf("Cd");
    afficher_centralite(centralite_degre, 15 + dx, dy);
    gotoligcol(dy, dx + 34);
    printf("Cvp");
    afficher_centralite(centralite_vecteurp, 30 + dx, dy);
    gotoligcol(dy, dx + 47);
    printf("Ci");
    afficher_centralite(centralite_intermediarite, 45 + dx, dy);
    std::cout << std::endl;
}

void Graphe::afficher_tous_indices_normalises(int dy, int dx) const
{
    gotoligcol(5, 30);
    std::cout << "INDICES DE CENTRALITE NORMALISES";
    gotoligcol(dy, dx + 4);
    printf("Cp");
    afficher_centralite(Cp_norm, dx, dy);
    gotoligcol(dy, dx + 17);
    printf("Cd");
    afficher_centralite(Cd_norm, 15 + dx, dy);
    gotoligcol(dy, dx + 34);
    printf("Cvp");
    afficher_centralite(Cvp_norm, 30 + dx, dy);
    gotoligcol(dy, dx + 47);
    printf("Ci");
    afficher_centralite(Ci_norm, 45 + dx, dy);
    std::cout << std::endl;
}



/// ----------GETTERS----------

///retourne l'arrete correspondante � ces deux sommets
void Graphe::get_arrete(int s1, int s2, Arrete &arrete) const //on passe arrete par adresse pour eviter control reaches end of non-void function
{
    //GRAPHE ORIENTE
    if(m_orientation == true)
    {
        for(size_t i = 0; i < m_taille; ++i)
        {
            if(s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())
                arrete = arretes[i];
        }
    }
    //GRAPHE NON ORIENTE
    else
    {
        for (size_t i = 0; i < m_taille; ++i)
        {
            if((s1 == arretes[i].get_indice_s1() && s2 == arretes[i].get_indice_s2())||(s2 == arretes[i].get_indice_s1() && s1 == arretes[i].get_indice_s2()))
                arrete = arretes[i];
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

//calcul de la centralit� de degr� pour 1 sommet dont l'indice est pass� en parametre
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
    float Cd = degre;
    return Cd;
}

//Calcul de la  centralit� de tous les sommets (plac�es dans un tableau)
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
//calcule la Cd normalisé de tous les sommets
void Graphe::Cd_normalise()
{
    Cd_norm = new float [m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        Cd_norm[i] = centralite_degre[i]/int(NORMALISE);
}

/// CENTRALITE DE PROXIMITE

//calcul de la centralit� de proximit� pour 1 sommet dont l'indice est pass� en parametre
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
        Cp = float(1)/somme_distances;
    else
        Cp = 0;
    return Cp;
}

//calcul de la centralit� de proximite pour tous les sommets
void Graphe::calculer_tous_Cp()
{
    centralite_proximite = new float[m_ordre]; //Allocation
    for (size_t i = 0 ; i < m_ordre; ++i)
    {
        centralite_proximite[i] = calculer_Cp(i);
    }
}

//Calcul de la Cp normalisé de tous les sommets
void Graphe::Cp_normalise()
{
    Cp_norm = new float[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        Cp_norm[i] =  centralite_proximite[i]*int(NORMALISE);
}

//algorithme de Dijkstra
//DIJKSTRA SANS MODIF
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
                Arrete a;
                get_arrete(s->get_indice(), it->get_indice(), a);
                //on r�cup�re la distance entre ces deux sommets (arrete[s,it] -> poids)
                distance = a.get_poids();
                //Si c'est plus court d'aller de S0 � it en passant par s
                if(distance_S0[it->get_indice()] > distance_S0[s->get_indice()] + distance)
                {
                    //on met � jour la distance S0 -> it avec celle qui passe par s
                    distance_S0[it->get_indice()] = distance_S0[s->get_indice()] + distance;
                    //predecesseur de it devient s
                    preds[it->get_indice()] = s->get_indice();
                }
            }
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

// Calcul de Cvp
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
        lambda_diff = abs(lambda_p-lambda);
    }
    while(lambda_diff > VAR_LAMBDA);
}
//Calcul de Cvp normalisé pour tous les sommets
void Graphe::Cvp_normalise()
{
    Cvp_norm = new float[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        Cvp_norm[i] = centralite_vecteurp[i];
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
                somme_Ci += Ci_chemins(CC[num_CC][j], CC[num_CC][i], s);
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

//calcule la Ci normalisé de tous les sommets
void Graphe::Ci_normalise()
{
    Ci_norm = new float[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        Ci_norm[i] = (2*centralite_intermediarite[i])/(m_ordre*m_ordre - 3*m_ordre + 2);
}

void Graphe::Dijkstra_ameliore(int s, int s0, int sf,int straverse, std::vector<bool>&parcouru, int chemin[], int noeud_parcourus,int poidstot,int poidsmax,float &Ci,float &nb_chemin)const
{
    parcouru[s] = true;
    chemin[noeud_parcourus]=s;
    noeud_parcourus++;

    if(s==sf) ///si soommet atteint
    {
        int i;
        nb_chemin++;///on aug le nb de chemins le plus cours
        for( i=0; i<noeud_parcourus; i++)
        {
            if(sommets[chemin[i]]->get_indice()==straverse)
                if((straverse != sf)&&(straverse != s0))
                    Ci++;
        }

    }
    else if(poidstot<=poidsmax) ///si le chemin en cours a un poids inferieur a celui de dijstra on continue
    {
        for (size_t i = 0; i <sommets[s]->sommet_adjacent.size(); ++i)
        {
            int sa=sommets[s]->sommet_adjacent[i]->get_indice();
            if (parcouru[sa]==false)
            {
                Arrete a;
                get_arrete(s,sa,a);
                int poids=poidstot+a.get_poids();
                Dijkstra_ameliore(sa, s0, sf,straverse, parcouru, chemin, noeud_parcourus,poids,poidsmax,Ci,nb_chemin);
            }
        }
    }
    noeud_parcourus--;
    parcouru[s]=false;
}
float Graphe::Ci_chemins(int s0, int sf,int straverse) const
{
    std::vector<bool> parcouru (m_ordre,false);
    int *chemin = new int[m_ordre];
    float Ci=0;
    float nb_chemin=0;
    Dijkstra_ameliore(s0,s0,sf,straverse,parcouru,chemin,0,0,Dijkstra(s0,sf),Ci,nb_chemin);

    return Ci/nb_chemin;
}

/// CALCULER TOUS INDICES
void Graphe::calculer_tous_indices()
{
    calculer_tous_Cd();
    calculer_tous_Cp();
    calculer_Cvp();
    calcul_tous_Ci();
}

void Graphe::calculer_tous_indices_normalises()
{
    Cd_normalise();
    Cp_normalise();
    Cvp_normalise();
    Ci_normalise();
}


//VULNERABILITE

void Graphe::vulnerabilite()
{
    //1) SUPPRIMER UNE ARRETE OU PLUSIEURS
    bool stop = false;
    std::string choix;
    do
    {
        supprimer_arrete();
        std::cout << "Souhaitez-vous supprimer une autre arrete ? (oui ou non)" << std::endl;
        std::cin.clear();
        fflush(stdin);
        std::cin >> choix;
        if(choix == "oui" || choix == "OUI")
            stop = false;
        else if (choix == "non" || choix == "NON")
            stop = true;
        else
        {
            std::cout << "vous n avez pas repondu par oui ou par non, on considere cela comme un non" << std::endl;
            stop=true;
        }
    }while(!stop);
    system("pause");
    system("cls");
    //2) REGARDER LA CONNEXITE
    rechercher_CC();
    afficher_CC();
    system("pause");
    system("cls");
    //3) RECALCULER LES NOUVEAUX INDICES DE CENTRALITE
    afficher_graphe_internet();
    calculer_tous_indices();
    //4) COMPARER CES CALCULS AVEC LES ANCIENS (dans la sauvegarde)
    //on recupere dans la sauvegarde les anciens indices de centralite
    comparaison_centralites();
}

void Graphe::comparaison_centralites()
{
    float* prec_Cd = new float [m_ordre];
    float* prec_Cvp = new float [m_ordre];
    float* prec_Cp = new float [m_ordre];
    float* prec_Ci = new float[m_ordre];
    float* prec_Cd_norm = new float [m_ordre];
    float* prec_Cvp_norm = new float [m_ordre];
    float* prec_Cp_norm = new float [m_ordre];
    float* prec_Ci_norm = new float[m_ordre];

    chargement_centralites(prec_Cd, prec_Cvp, prec_Cp, prec_Ci, prec_Cd_norm, prec_Cvp_norm, prec_Cp_norm, prec_Ci_norm); //on recupere les anciennes donnees de centralite

    float* diff_Cd = difference_centralite(prec_Cd, centralite_degre);
    float* diff_Cvp = difference_centralite(prec_Cvp, centralite_vecteurp);
    float* diff_Cp = difference_centralite(prec_Cp, centralite_proximite);
    float* diff_Ci = difference_centralite(prec_Ci, centralite_intermediarite);

    afficher_arretes_suppr_pour_centralite();

    gotoligcol(DY, DX); std::cout << "diff Cp";
    gotoligcol(DY, DX + 17); std::cout << "diff Cd";
    gotoligcol(DY, DX + 31); std::cout << "diff Cvp";
    gotoligcol(DY, DX + 44); std::cout << "diff Ci";
    afficher_centralite(diff_Cp, DX, DY);
    afficher_centralite(diff_Cd, DX + 15, DY);
    afficher_centralite(diff_Cvp, DX + 30, DY);
    afficher_centralite(diff_Ci, DX + 45, DY);

    afficher_tous_indices(DY + m_ordre + 2, DX);

    system("pause");
    system("cls");

    diff_Cd = difference_centralite(prec_Cd_norm, centralite_degre);
    diff_Cvp = difference_centralite(prec_Cvp_norm, centralite_vecteurp);
    diff_Cp = difference_centralite(prec_Cp_norm, centralite_proximite);
    diff_Ci = difference_centralite(prec_Ci_norm, centralite_intermediarite);

    afficher_arretes_suppr_pour_centralite();

    gotoligcol(DY, DX); std::cout << "diff Cp";
    gotoligcol(DY, DX + 17); std::cout << "diff Cd";
    gotoligcol(DY, DX + 31); std::cout << "diff Cvp";
    gotoligcol(DY, DX + 44); std::cout << "diff CI";
    afficher_centralite(diff_Cp, DX, DY);
    afficher_centralite(diff_Cd, DX + 15, DY);
    afficher_centralite(diff_Cvp, DX + 30, DY);
    afficher_centralite(diff_Ci, DX + 45, DY);

    afficher_tous_indices_normalises(DY + m_ordre + 4, DX);

    arretes_supprimees.clear();

}

void Graphe::afficher_arretes_suppr_pour_centralite() const
{
    std::cout << std::endl << "Modification des centralites du graphe suite a la suppression";
    if(arretes_supprimees.size() > 1)
        std::cout << " des arretes : ";
    else
         std::cout << " de l'arrete :";
    for (size_t i = 0; i < arretes_supprimees.size(); ++i)
        std::cout << sommets[arretes_supprimees[i].get_indice_s1()]->get_nom() << "-" << sommets[arretes_supprimees[i].get_indice_s2()]->get_nom() << "  ";

}

float* Graphe::difference_centralite(float* pred, float* nv) const
{
    float* diff = new float[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        diff[i] = nv[i] - pred[i];
    return diff;
}

void Graphe::supprimer_arrete()
{
    int indice;
    Arrete tampon;
    system("cls");
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

    std::cout << std::endl << "l'arrete " << sommets[tampon.get_indice_s1()]->get_nom() << "-"
              << sommets[tampon.get_indice_s2()]->get_nom()
              << " a ete supprime avec succes" << std::endl << std::endl;
    arretes_supprimees.push_back(tampon);
    afficher_graphe_internet();
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
    std::cout << std::endl;
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
        sauv << std::endl << "centralite_degre" << "     non_normalise      normalise" <<std::endl;
        ecrire_centralite(centralite_degre, Cd_norm, sauv);
        //CENTRALITE DE VECTEUR PROPRE
        sauv << std::endl << "centralite_vecteurp" << "    non_normalise      normalise" << std::endl;
        ecrire_centralite(centralite_vecteurp, Cvp_norm, sauv);
        //CENTRALITE DE PROXIMITE
        sauv << std::endl << "centralite_proximite" << "    non_normalise      normalise" <<std::endl;
        ecrire_centralite(centralite_proximite, Cp_norm, sauv);
        //CENTRALITE D'INTERMEDIARITE
        sauv << std::endl << "centralite_intermediarite" << "    non_normalise      normalise" <<std::endl;
        ecrire_centralite(centralite_intermediarite, Ci_norm, sauv);
        sauv.close();
    }
}

void Graphe::ecrire_centralite(float* vecteur, float* vecteur_norm, std::ofstream &fichier)
{
    for(size_t i = 0; i < m_ordre; ++i)
    {
        fichier << "     Sommet" << sommets[i]->get_nom() << "                ";
        fichier << vecteur[i] << "          "<< vecteur_norm[i] << std::endl;
    }

}


///CHARGEMENT CENTRALITE
void Graphe::chargement_centralites(float* &prec_Cd, float* &prec_Cvp, float* &prec_Cp, float* &prec_Ci, float* &prec_Cd_norm, float* &prec_Cvp_norm, float* &prec_Cp_norm, float* &prec_Ci_norm) const
{
    std::string centralite;
    std::ifstream charg{"centralites.txt"};
    if(!charg)
        erreur("Impossible d'ouvrir le fichier de sauvegarde des centralites");
    else
    {
        do
        {
            charg >> centralite;
            if(centralite == "centralite_degre") //DEGRE
                recuperer_centralite(prec_Cd, prec_Cd_norm, charg);
            else if(centralite == "centralite_vecteurp") //VECTEUR PROPRE
                recuperer_centralite(prec_Cvp, prec_Cvp_norm, charg);
            else if(centralite == "centralite_proximite") //PROXIMITE
                recuperer_centralite(prec_Cp, prec_Cp_norm, charg);
            else if(centralite == "centralite_intermediarite") //INTERMEDIARITE
                recuperer_centralite(prec_Ci, prec_Ci_norm, charg);
        }
        while(charg);
        charg.close();
    }
}

void Graphe::recuperer_centralite(float* &vecteur, float* &vecteur_norm, std::ifstream &fichier) const
{
    std::string sommet;
    std::string norm;
    fichier >> norm >> norm;
    for(size_t i = 0; i < m_ordre; ++i)
    {
        fichier >> sommet;
        fichier >> vecteur[i];
        fichier >> vecteur_norm[i];
    }

}


///COLORATION

void Graphe::charger_couleurs()
{
    coloration.push_back("blue");
    coloration.push_back("green");
    coloration.push_back("red");
    coloration.push_back("purple");
    coloration.push_back("black");
    coloration.push_back("pink");
}

void Graphe::attribuer_couleur()
{
    bool changement = true;
    float** Cd = new float*[m_ordre];
    for(size_t i = 0; i < m_ordre; ++i)
        Cd[i] = new float[2];
    float tampon_c;
    //copier le vecteur de centralite de degre + le sommet attribué
    for(size_t i = 0; i < m_ordre; ++i)
    {
        Cd[i][0] = centralite_degre[i];
        Cd[i][1] = i;
    }
    //tri du plus petit Cd au plus grand
    while(changement)
    {
        changement = false;
        for(size_t i = 0; i < m_ordre - 1; ++i)
        {
            if(Cd[i][0] > Cd[i+1][0])
            {
                tampon_c = Cd[i][0];
                Cd[i][0] = Cd[i+1][0];
                Cd[i+1][0] = tampon_c;

                tampon_c = Cd[i][1];
                Cd[i][1] = Cd[i+1][1];
                Cd[i+1][1] = tampon_c;

                changement = true;
            }
        }
    }
    int couleur = 0;
    int prec_Cd = int(Cd[0][0]);
    //Affectation des couleurs aux sommets
    for(size_t i = 0; i < m_ordre; ++i)
    {
        if(Cd[i][0] == prec_Cd) //si on a la meme couleur qu'avant
            couleur = couleur; //on conserve la meme couleur
        else
            ++couleur; //elle change
        sommets[Cd[i][1]]->set_couleur(couleur); // on affecte la couleur au sommet
        prec_Cd = int(Cd[i][0]); //on conserve l'ancienne centralité du sommet pour comparer
    }

}



