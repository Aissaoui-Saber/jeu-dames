#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED
#include "Case.h"
#include "Joueur.h"
#include <vector>
class Case;
class Joueur;
class Piece {
protected:
	char caractere;///LE CARACTERE QUI VA ETRE AFFICHE SUR LA CASE (CONSOLE)
	string nom;///LE NOM DE LA PIECE (EXEMPLE: PION,DAME,ROI,CHEVALE ....)
	Case *CASE = 0;///LA CASE ASSOCIEE A CETTE PIECE
	Joueur *joueur = 0;///LE JOUEUR QUI POSSEDE CETTE PIECE
	bool dehorsPlateau;///SI VRAI -> LA PIECE N'EST ASSOCIEE AVEC AUCUNE CASE DU PLATEAU
public:
	Piece(char c,string nom);///CONSTRUCTEUR DE LA PIECE
	char getCaractere();///RETOURNER LE CARACTERE DE CETTE PIECE
	void setCaractere(char c);///MODIFIER LE CARACTERE DE CETTE PIECE
	bool setCase(Case *c);///DEPLACER CETTE PIECE VERS UNE AUTRE CASE
	void setJoueur(Joueur *J);///MODIFIER LE JOUEUR QUI POSSEDE LA PIECE
	Case *getCase();///RETOURNER LA CASE ASSOCIEE AVEC CETTE PIECE
	Joueur *getJoueur();///RETOURNER LE JOUEUR QUI POSSEDE CETTE PIECE
	bool estDehorsPlateau();///RETOURNER VRAI SI LA PIECE N'EST ASSOCIEE AVEC AUCUNE CASE DU PLATEAU
	string getNom();///RETOURNER LE NOM DE CETTE PIECE
};

#endif // PIECE_H_INCLUDED
