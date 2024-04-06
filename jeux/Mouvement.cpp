#include "Case.h"
#include "Piece.h"
#include "Joueur.h"
#include "Mouvement.h"

Mouvement::Mouvement(int j, Piece *p, Case *src, Case *dest,Piece *piecePrise) {
	this->joueur = j;
	this->piece = p;
	this->source = src;
	this->destination = dest;
	this->piecePrise = piecePrise;
	if (piecePrise != 0) {
		this->casePiecePrise = piecePrise->getCase();
	}
	else {
		this->casePiecePrise = 0;
	}
}

int Mouvement::getJoueur() {
	return this->joueur;
}

Piece *Mouvement::getPiece() {
	return this->piece;
}

Case *Mouvement::getCaseSource() {
	return this->source;
}

Case *Mouvement::getCaseDestination() {
	return this->destination;
}

bool Mouvement::avecPrise()
{
	if (this->piecePrise == 0) {
		return false;
	}
	else
	{
		return true;
	}
	
}

Piece * Mouvement::getPiecePrise()
{
	return this->piecePrise;
}

Case * Mouvement::getCasePiecePriese()
{
	return this->casePiecePrise;
}
