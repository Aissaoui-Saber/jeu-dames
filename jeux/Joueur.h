#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED
#include "Piece.h"
#include "Case.h"
#include <vector>
#include <string>
using namespace std;
class Piece;
class Case;
class Joueur {
private:
	vector<Piece*> pieces;///LISTE DES PIECES QUE CE JOUEUR POSSEDE
	bool possedePiece(Piece *p);///TESTER SI CE JOUEUR POSSEDE LA PIECE p
	bool humain;///TRUE -> JOUEUR HUMAIN | FALSE -> JOUEUR ROBOT
public:
	Joueur(bool humain);///CONSTRUCTEUR DE JOUEUR
	vector<Piece*> getPieces();///RETOURNER LA LISTE DES PIECES QUE CE JOUEUR POSSEDE
	void ajouterPiece(Piece *p);///ASSOCIER CE JOUEUR A UNE PIECE ET L'AJOUTER DANS LA LISTE DES PIECES QU'IL POSSEDE
	bool deplasserPiece(Piece *p, Case *c);///FAIRE DEPLACER UNE PIECE VERS UNE CASE
	bool estHumain();///SI LE JOUEUR EST HUMAIN, RETOURNER TRUE
};

#endif // JOUEUR_H_INCLUDED
