#include "Piece.h"
#include "Joueur.h"
#include "Case.h"
#include <vector>
using namespace std;

Joueur::Joueur(bool humain) {
	this->humain = humain;
}

vector<Piece*> Joueur::getPieces() {
	return this->pieces;
}

void Joueur::ajouterPiece(Piece *p) {
	if (this->possedePiece(p) == false) {
		this->pieces.push_back(p);
		p->setJoueur(this);
	}
}

bool Joueur::deplasserPiece(Piece* p, Case* c) {
	if (c != 0) {
		if (c->estVide()) {
			if (p->setCase(c)) {
				return true;
			}
			return false;
		}
		return false;
	}
	else {
		p->setCase(0);
	}
	
}

bool Joueur::estHumain()
{
	return this->humain;
}

bool Joueur::possedePiece(Piece *p) {
	for (int i = 0; i<(int)this->pieces.size(); i++) {
		if (p == this->pieces[i]) {
			return true;
		}
	}
	return false;
}
