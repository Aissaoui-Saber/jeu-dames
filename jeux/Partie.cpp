#include <vector>
#include "Plateau.h"
#include "Case.h"
#include "Piece.h"
#include "Joueur.h"
#include "Partie.h"
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

Partie::Partie() {

}

Partie::~Partie()
{
	this->historique.clear();
	this->joueurs.clear();
}

void Partie::lancer() {
	
}

void Partie::sauvgarder()
{
}

int Partie::nbrAleatoire(int MIN, int MAX) { 
	static bool first = true;
	if (first) {
		srand((unsigned int)time(NULL)); 
		first = false;
	}
	return MIN + rand() % ((MAX + 1) - MIN);
}

void Partie::changerTour() {
	if (this->joueurAyantTour == (int)this->joueurs.size() - 1) {
		this->joueurAyantTour = 0;
	}
	else {
		this->joueurAyantTour++;
	}
}

void Partie::annulerMouvement() {
	
}

Case * Partie::lireCommande(string s)
{
	return 0;
}

void Partie::trouverDeplacements(Piece *p)
{
}

void Partie::afficherSuggestions()
{
	for (int i = 0; i < (int)this->deplacementsPossibles.size(); i++) {
		if (this->deplacementsPossibles[i].avecPrise()) {
			cout << "[#" << this->deplacementsPossibles[i].getCaseDestination()->getLigne() + 1 << (char)(this->deplacementsPossibles[i].getCaseDestination()->getColonne() + 97) << "] ";
		}
		else {
			cout << "[" << this->deplacementsPossibles[i].getCaseDestination()->getLigne() + 1 << (char)(this->deplacementsPossibles[i].getCaseDestination()->getColonne() + 97) << "] ";
		}	
	}
	cout << endl;
}

bool Partie::deplacementValide(Case * c)
{
	int i(0);
	while (i < (int)this->deplacementsPossibles.size())
	{
		if (this->deplacementsPossibles[i].getCaseDestination() == c) {
			return true;
		}
		i++;
	}
	return false;
}

void Partie::deplacerPiece(Case *caseSelectionee)
{
}

int Partie::getDeplacementIndex(Case * c)
{
	return -1;
}

Case * Partie::selectionnerCase(string s)
{
	return 0;
}

void Partie::executeCmd(string s)
{
}

int Partie::getPriseIndice()
{
	int i(0);
	while (i < (int)this->deplacementsPossibles.size())
	{
		if (this->deplacementsPossibles[i].avecPrise()) {
			return i;
		}
		i++;
	}
	return -1;
}

int Partie::nombrePieceDansPlateau(int indiceJoueur)
{
	int c(0);
	for (int i = 0; i < (int)this->joueurs[indiceJoueur].getPieces().size(); i++) {
		if (this->joueurs[indiceJoueur].getPieces()[i]->estDehorsPlateau() == false) {
			c++;
		}
	}
	return c;
}

bool Partie::estTermine()
{
	return false;
}
