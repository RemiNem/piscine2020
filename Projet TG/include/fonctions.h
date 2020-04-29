#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

///Affiche les erreurs
void erreur(std::string error);
///chargement fichier
std::vector<std::string> recuperer_fichiers(std::string nomdossier);
///gere le blindage des entrees console
void entree_blindee(int mini, int maxi, int &valeur);
#endif // FONCTIONS_H_INCLUDED
