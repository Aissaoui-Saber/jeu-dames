#include "Case.h"
#include <string>
using namespace std;
Case::Case(int Ligne, int Colonne,string color) {
	if (Ligne < 0) {
		this->ligne = 0;
	}
	else {
		this->ligne = Ligne;
	}
	if (Colonne < 0) {
		this->colonne = 0;
	}
	else {
		this->colonne = Colonne;
	}
	this->couleur = color;
}

bool Case::estVide() {
	return this->vide;
}

int Case::getLigne() {
	return this->ligne;
}

int Case::getColonne() {
	return this->colonne;
}

string Case::getCouleur()
{
	return this->couleur;
}

void Case::setPiece(Piece *p) {
	this->piece = p;
	if (p != 0) { this->vide = false; }
	else { this->vide = true; }
}

Piece *Case::getPiece() {
	return this->piece;
}

std::string Case::toString() {
	return "[" + to_string(Case::ligne) + "," + to_string(Case::colonne) + "]";
}