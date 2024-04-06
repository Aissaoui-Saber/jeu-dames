#include "Plateau.h"
#include <iostream>
#include <vector>
#include <string>
#include "Case.h"
using namespace std;

Plateau::Plateau(int nbrLignes, int nbrColonnes) {
	this->nbrColonnes = nbrColonnes;
	this->nbrLignes = nbrLignes;

	this->nbrLignesDessin = (this->nbrLignes * 4) + 1;
	this->nbrColonnesDessin = (this->nbrColonnes * 4) + 1;
	///INITIALISATION DE TABLEAU DE DESSIN-------------------------
	int ii = -1, jj = -1;
	vector<char> v;
	for (int i(0); i<this->nbrLignesDessin; i++) {
		if (i % 4 == 0) {
			ii++;
		}
		if (i == ii * 4) {
			vector<char> v(this->nbrColonnesDessin, '.');
			this->dessinPlateau.push_back(v);
		}
		else {
			vector<char> v;
			for (int j = 0; j<this->nbrColonnesDessin; j++) {
				if (j % 4 == 0) {
					jj++;
				}
				if (j == jj * 4) {
					v.push_back('.');
				}
				else {
					v.push_back(' ');
				}
			}
			jj = -1;
			this->dessinPlateau.push_back(v);
		}
	}
	///INITIALISATION DE TABLEAU DE CASES--------------------------
	for (int i = 0; i<this->nbrLignes; i++) {
		vector<Case> w;
		for (int j = 0; j<this->nbrColonnes; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					Case C = *new Case(i, j, "Blanche");
					C.setPiece(0);
					w.push_back(C);
				}else{
					Case C = *new Case(i, j, "Noire");
					C.setPiece(0);
					w.push_back(C);
				}
			}
			else {
				if (j % 2 != 0) {
					Case C = *new Case(i, j, "Blanche");
					C.setPiece(0);
					w.push_back(C);
				}
				else {
					Case C = *new Case(i, j, "Noire");
					C.setPiece(0);
					w.push_back(C);
				}
			}
		}
		this->cases.push_back(w);
	}
}


int Plateau::getNbrLignes() {
	return this->nbrLignes;
}

int Plateau::getNbrColonnes() {
	return this->nbrColonnes;
}

void Plateau::afficher() {
	///AFFECTER LE CONTENU DES CASES AU DESSIN
	for (int i = 0; i<nbrLignes; i++) {
		for (int j = 0; j<nbrColonnes; j++) {
			if (this->cases.at(i).at(j).estVide() == false) {
				this->dessinPlateau.at(4 * i + 2).at(4 * j + 2) = this->cases.at(i).at(j).getPiece()->getCaractere();
			}
			else {
				this->dessinPlateau.at(4 * i + 2).at(4 * j + 2) = ' ';
			}
		}
	}
	///AFFICHER L'ALPHABET AU DESUS-------------------------
	cout << "       ";
	for (int i(0); i<this->nbrColonnes; i++) {
		cout << (char)(97 + i) << "       ";
	}
	cout << endl;
	///-------------------------------
	int ii = -1;
	for (int i = 0; i<this->nbrLignesDessin; i++) {
		if (i % 4 == 0) {
			ii++;
		}
		///AFFICHER LES NOMBRES DE LIGNES A GAUCHE---------
		if (i == (4 * ii + 2)) {
			if (ii<9) {
				cout << " " << (ii + 1) << " ";
			}
			else {
				cout << (ii + 1) << " ";
			}
		}
		else {
			cout << "   ";
		}
		///----------------------------------------
		for (int j = 0; j<this->nbrColonnesDessin; j++) {
			cout << this->dessinPlateau[i][j] << " ";
		}
		///AFFICHER LES NOMBRES DE LIGNES A DROITE---------
		if (i == (4 * ii + 2)) {
				cout << (ii + 1);
		}
		cout << endl;
	}
	cout << "       ";
	for (int i(0); i<this->nbrColonnes; i++) {
		cout << (char)(97 + i) << "       ";
	}
	cout << endl;
}
Case *Plateau::getCase(int Ligne, int Colonne) {
	if (Ligne >= 0 && Colonne >= 0) {
		if (Ligne < this->nbrLignes && Colonne < this->nbrColonnes) {
			return &this->cases[Ligne][Colonne];
		}
		else
		{
			return 0;
		}
		
	}
	else {
		return 0;
	}

}

