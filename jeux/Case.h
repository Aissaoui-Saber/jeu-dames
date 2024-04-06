#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED
#include "Piece.h"
#include <string>
using namespace std;
class Piece;
class Case {
private:
	int ligne = 0;///LA LIGNE DE LA CASE
	int colonne = 0;///LA COLONNE DE LA CASE
	bool vide = true;///LA CASE EST VIDE OU ELLE CONTITNET UNE PIECE
	Piece *piece = 0;///LA PIECE ASSOCIEE A CETTE CASE
	string couleur;///LE NOM DE LA COULEUR DE CETTE CASE
public:
	Case(int Ligne, int Colonne,string color);///CONSTRUCTION DE L'OBJET CASE
	bool estVide();///SI LA CASE CONTIENT UNE PIECE RETOURNER 'False' SINON RETOURNER 'True'
	int getLigne();///RECUPERER LA LIGNE DE LA CASE
	int getColonne();///RECUPERER LA COLONNE DE LA CASE
	string getCouleur();///RETOURNER LE NOM DE LA COULEUR DE CETTE CASE
	void setPiece(Piece *p);///ASSOCIER UNE PIECE A CETTE CASE
	Piece *getPiece();///RETOURNER LA PIECE ASSOCIEE A CETTE CASE
	std::string toString();///RETOURNER UNE CHAINE DE CARACTERE EXEMPLE:"[2,3]"
};

#endif // CASE_H_INCLUDED
