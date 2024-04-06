#ifndef MOUVEMENT_H_INCLUDED
#define MOUVEMENT_H_INCLUDED
#include "Case.h"
#include "Piece.h"
#include "Joueur.h"

class Mouvement {
private:
	int joueur;///L'INDICE DU JOUEUR DANS LA LISTE DES JOUEURS DE LA PARTIE
	Piece *piece;///LA PIECE
	Case *source;///LA POSITON SOURCE
	Case *destination;///LA POSITION DESTINATION
	Piece *piecePrise = 0;///LA PIECE PRISE
	Case *casePiecePrise = 0;///LA CASE DE LA PIECE PRISE
public:
	Mouvement(int j, Piece *p, Case *src, Case *dest,Piece *piecePrise);///CONSTRUCTEUR
	int getJoueur();///RETOURNER L'INDICE DU JOUEUR DANS LA LISTE DES JOUEURS DE LA PARTIE
	Piece *getPiece();///RETOURNER LA PIECE
	Case *getCaseSource();///RETOURNER LA POSITION SOURCE
	Case *getCaseDestination();///RETOURNER LA POSITION DESTINATION
	bool avecPrise();///SI LE DEPLACEMENT EST AVEC PRISE, RETOURNER VRAI
	Piece *getPiecePrise();///RETOURNER LA PIECE PRISE
	Case *getCasePiecePriese();///RETOURNER LA CASE DE LA PIECE PRISE
};

#endif // MOUVEMENT_H_INCLUDED
