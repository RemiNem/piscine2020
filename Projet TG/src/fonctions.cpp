#include <iostream>
#include <string.h>
#include <vector>
#include <dirent.h>

///affiche les erreurs
void erreur(std::string error)
{
    std::cout << std::endl << error << std::endl;
}

///recupere dans un vecteur de string les fichiers qu'il est possible de charger
std::vector<std::string> recuperer_fichiers(std::string nomdossier)
{
    double i = -2; //pour eviter de recuperer les donnees . et .. au debut
    //conversion string vers char
    std::vector<std::string> nomfichiers;
    char* dossier = new char[nomdossier.length() + 1];
    strcpy(dossier, nomdossier.c_str());
    //recupere tous e=les fichiers dans la string
    DIR * rep = opendir(dossier);
    if (rep != NULL)
    {
        struct dirent * ent;

        while ((ent = readdir(rep)) != NULL)
        {
            ++i;
            if (i >= 1)
                nomfichiers.push_back(ent->d_name);
        }

        closedir(rep);
    }
    std::cout << std::endl;
    return nomfichiers;
}


///gère le blindage des entrée consoles
void entree_blindee(int mini, int maxi, int &valeur)
{
    do
    {
        std::cout << "Votre choix :";
        std::cin >> valeur;
        if(valeur < mini || valeur > maxi)
            erreur("Le numero que vous avez entre n'est pas valide");
    }while(valeur < mini || valeur > maxi);
}


