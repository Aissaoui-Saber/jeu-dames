#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED
#include <vector>
#include "Case.h"
using namespace std;
class Plateau {
private:
	int nbrLignes;///LE NOMBRE DE LIGNES DE PLATEAU
	int nbrColonnes;///LE NOMBRE DE COLONNES DE PLATEAU
	int nbrLignesDessin;///LE NOMBRE DE LIGNES DE DESSIN DE PLATEAU
	int nbrColonnesDessin;///LE NOMBRE DE COLONNES DE DESSIN DE PLATEAU
	vector<vector<char>> dessinPlateau;///TABLEAU A 2 DIMMENSION QUI CONTIENT DES CARACTERES POUR FAIRE LE DESSIN DE PLATEU
	vector<vector<Case>> cases;///TABLEAU A 2 DIMMENSION QUI CONTIENT DES OBJETS DE TYPE CASE
public:
	Plateau(int nbrLignes, int nbrColonnes);///CONSTRUCTION DE PLATEAU
	int getNbrLignes();///RECUPERER LE NOMBRE DE LIGNES DE PLATEAU
	int getNbrColonnes();///RECUPERER LE NOMBRE DE COLONNES DE PLATEAU
	void afficher();///AFFICHER LE PLATEAU SUR LA CONSOLE
	Case *getCase(int Ligne, int Colonne);///RETOURNER UN POINTEUR SUR L'OBJET CASE QUI SE SITUE A 'Ligne' ET 'Colonne' DONNEE
};

#endif
