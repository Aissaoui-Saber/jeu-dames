#include "Piece.h"
#include "Case.h"
#include <string>
#include <iostream>
using namespace std;

Piece::Piece(char c,string nom)
{
	this->nom = nom;
	this->caractere = c;
}

char Piece::getCaractere() {
	return this->caractere;
}

void Piece::setCaractere(char c) {
	this->caractere = c;
}

bool Piece::setCase(Case *c) {
	if (c != 0) {///SI LA CASE EXISTE
		if (c->estVide()) {///SI LA CASE EST VIDE ALORS ASSOCIER CETTE PIECE A CETTE CASE
			if (this->CASE != 0) {
				this->CASE->setPiece(0);///LIBERER L'ANCIENNE CASE
			}
			this->CASE = c;///LA PIECE POINT SUR LA CASE
			c->setPiece(this);///LA CASE POINTE SUR LA PIECE
			this->dehorsPlateau = false;///DONC LA PIECE EST DANS LE PLATEAU
			return true;///LE DEPLACMENT ET FAIT
		}
		else {///SI LA CASE EST ASSOCIEE A UNE AUTRE PIECE (N'EST PAS VIDE)
			return false;///DEPLACEMENT IMPOSSIBLE
		}
	}
	else {///METRE LA PIECE DEHORS LE PLATEAU(ELLE NE POINTE SUR AUCUNE CASE c=0)
		this->CASE->setPiece(0);///LA CASE NE POINTE PLUS SUR CETTE PIECE
		this->CASE = c;///CETTE PIECE NE POINT SUR AUCUNE CASE
		this->dehorsPlateau = true;///DONC LA PIECE EST DEHORS LE PLATEAU
		return true;///LE DEPLACMENT ET FAIT
	}
}

Case *Piece::getCase() {
	return this->CASE;
}

void Piece::setJoueur(Joueur *J) {
	if (this->joueur != J) {
		this->joueur = J;
		J->ajouterPiece(this);
	}
}

Joueur *Piece::getJoueur() {
	return this->joueur;
}

bool Piece::estDehorsPlateau() {
	return this->dehorsPlateau;
}

string Piece::getNom()
{
	return this->nom;
}
