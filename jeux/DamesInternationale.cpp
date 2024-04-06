#include "DamesInternationale.h"
#include "Plateau.h"
#include "Piece.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
DamesInternationale::DamesInternationale(bool humain) {
	this->joueurVainqueur = -1;
	this->joueurs.push_back(*new Joueur(humain));///JOUEUR EN HAUT
	this->joueurs.push_back(*new Joueur(true));///JOUEUR EN BAS

	this->joueurs[0].ajouterPiece(new Piece('M',"Dame"));
	this->joueurs[0].getPieces()[0]->setCase(this->damier.getCase(3,0));

	this->joueurs[1].ajouterPiece(new Piece('s', "Pion"));
	this->joueurs[1].getPieces()[0]->setCase(this->damier.getCase(2, 1));

	this->joueurs[1].ajouterPiece(new Piece('s', "Pion"));
	this->joueurs[1].getPieces()[1]->setCase(this->damier.getCase(2, 3));

	this->joueurs[1].ajouterPiece(new Piece('s', "Pion"));
	this->joueurs[1].getPieces()[2]->setCase(this->damier.getCase(2, 5));

	this->joueurs[1].ajouterPiece(new Piece('s', "Pion"));
	this->joueurs[1].getPieces()[3]->setCase(this->damier.getCase(3, 8));

	/*int k(0);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (this->damier.getCase(i, j)->getCouleur() == "Noire") {
				this->joueurs[0].ajouterPiece(new Piece('m',"Pion"));
				this->joueurs[0].getPieces()[k]->setCase(this->damier.getCase(i, j));
				k++;
			}
		}
	}
	k = 0;
	for (int i = 6; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (this->damier.getCase(i, j)->getCouleur() == "Noire") {
				this->joueurs[1].ajouterPiece(new Piece('s',"Pion"));
				this->joueurs[1].getPieces()[k]->setCase(this->damier.getCase(i, j));
				k++;
			}
		}
	}*/
	this->joueurAyantTour = 1;
}

DamesInternationale::~DamesInternationale()
{
	if (this->joueurs.size() > 0) {
		if (this->joueurs[0].getPieces().size() > 0) {
			///SUPPRIMER LES PIECE DE JOUEUR 1
			for (int i = 0; i < this->joueurs[0].getPieces().size(); i++) {
				delete(this->joueurs[0].getPieces()[i]);
			}
			this->joueurs[0].getPieces().clear();
		}
		if (this->joueurs[1].getPieces().size() > 0) {
			///SUPPRIMER LES PIECE DE JOUEUR 2
			for (int i = 0; i < this->joueurs[1].getPieces().size(); i++) {
				delete(this->joueurs[1].getPieces()[i]);
			}
			this->joueurs[1].getPieces().clear();
		}
	}
}

void DamesInternationale::lancer() {
	string s("");
	while (this->joueurVainqueur == -1)
	{
		system("CLS");
		cout << "- Tapez 's' pour selectionner une piece" << endl;
		cout << "- Tapez 'q' pour quiter la partie" << endl;
		cout << "- Tapez 'r' pour annuler le deplacement" << endl << "----------------------------------------------------------------------------------------" << endl << endl;
		cout << "                             JOUEUR 1 [" << this->nombrePieceDansPlateau(0) << " Pieces restantes]" <<endl;
		this->damier.afficher();
		cout << "                             JOUEUR 2 [" << this->nombrePieceDansPlateau(1) << " Pieces restantes]" << endl << endl;
		cout << "----------------------------------------------------------------------------------------" << endl;
		this->deplacementsPossibles.clear();
		if (this->estTermine()) {
			break;
		}
		this->deplacementsPossibles.clear();
		if (this->joueurs[this->joueurAyantTour].estHumain()) {
			///SELECTIONNER UNE PIECE-------------------------------
			cout << "[Joueur " << this->joueurAyantTour + 1 << "] selectionner une piece:";
			cin >> s;
			if (s.length() == 2 || s.length() == 3) {
				Case *caseSelectionee = this->selectionnerCase(s);
				///DEPLACER UNE PIECE-----------------------------------
				if (caseSelectionee != 0) {
					this->deplacerPiece(caseSelectionee);
				}
			}
			else {
				this->executeCmd(s);
			}
		}
		else {
			/// TROUVER TOUT LES DEPLACEMENTS POSSIBLE
			for (int i = 0; i < (int)this->joueurs[this->joueurAyantTour].getPieces().size(); i++) {
				if (this->joueurs[this->joueurAyantTour].getPieces()[i]->estDehorsPlateau() == false) {
					this->trouverDeplacements(this->joueurs[this->joueurAyantTour].getPieces()[i]);
				}
			}
			for (int i = 0; i < (int)this->deplacementsPossibles.size(); i++) {
				if (this->deplacementsPossibles[i].avecPrise()) {///CHOISIR UN DEPLACEMENT AVEC PRISE S'IL ESXISTE 
					Piece *p = this->deplacementsPossibles[i].getPiece();///PIECE SELECTIONNEE
					this->deplacementsPossibles.clear();
					this->trouverDeplacements(p);///TROUVER LES DEPLACEMENTS POSSIBLE DE LA PIECE SELECTIONNEE
					this->deplacerPiece(p->getCase());
					break;
				}
				else if (i == this->deplacementsPossibles.size() - 1) {///CHOISIR UN DEPLACEMENTS SANS PRISE
					int k = this->nbrAleatoire(0, this->deplacementsPossibles.size() - 1);
					Piece *p = this->deplacementsPossibles[k].getPiece();///CHOISIR UNE CASE ALEATOIRE
					this->deplacementsPossibles.clear();
					this->trouverDeplacements(p);///TROUVER LES DEPLACEMENTS POSSIBLE DE LA PIECE SELECTIONNEE
					this->deplacerPiece(this->deplacementsPossibles[0].getCaseSource());
				}
			}
		}
	}
	if (this->joueurVainqueur > -1) {
		cout << "PARTIE TERMINE" << endl << "JOUEUR " << this->joueurVainqueur + 1 << " EST LE VAINQUEUR" << endl;
		return;
	}
}

void DamesInternationale::trouverDeplacements(Piece *p)
{
	int ligne = p->getCase()->getLigne();
	int colonne = p->getCase()->getColonne();
	vector<Mouvement> deplacements;
	if (this->joueurAyantTour == 0) {///REGLES POUR JOUEUR EN HAUT
		///REGLES POUR LES PIONS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (p->getNom() == "Pion") {
			if (colonne + 1 < this->damier.getNbrColonnes()) {///CASE GAUCHE EXISTE
				if (this->damier.getCase(ligne + 1, colonne + 1)->estVide()) {///SI LA CASE GAUCHE EST VIDE
					deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 1, colonne + 1), 0));
				}
				else {///LE CAS D'UNE PRISE A GAUCHE
					if (colonne + 2 < this->damier.getNbrColonnes()) {
						if (ligne + 2 < this->damier.getNbrLignes()) {
							if (this->damier.getCase(ligne + 2, colonne + 2)->estVide()) {///SI LA CASE DESTINATION EST VIDE
								if (this->damier.getCase(ligne + 1, colonne + 1)->getPiece()->getJoueur() == &this->joueurs[1]) {///SI LA PIECE QU'ON VEUT LA PRENDRE APARTIENT AU JOUEUR ADVERSIARE
									deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 2, colonne + 2), this->damier.getCase(ligne + 1, colonne + 1)->getPiece()));
								}
							}
						}
					}
				}
			}
			if (colonne - 1 >= 0) {///CASE DROITE EXISTE
				if (this->damier.getCase(ligne + 1, colonne - 1)->estVide()) {///SI LA CASE DROITE EST VIDE
					deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 1, colonne - 1), 0));
				}
				else {///LE CAS D'UNE PRISE A DROITE
					if (colonne - 2 >= 0) {
						if (ligne + 2 < this->damier.getNbrLignes()) {
							if (this->damier.getCase(ligne + 2, colonne - 2)->estVide()) {
								if (this->damier.getCase(ligne + 1, colonne - 1)->getPiece()->getJoueur() == &this->joueurs[1]) {
									deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 2, colonne - 2), this->damier.getCase(ligne + 1, colonne - 1)->getPiece()));
								}
							}
						}
					}
				}
			}
			if (ligne - 2 >= 0) {///LE CAS D'UNE PRISE EN ARRIERE
				if (colonne - 2 >= 0) {///CASE DROITE EXISTE
					if (this->damier.getCase(ligne - 2, colonne - 2)->estVide()) {
						if (this->damier.getCase(ligne - 1, colonne - 1)->estVide() == false) {
							if (this->damier.getCase(ligne - 1, colonne - 1)->getPiece()->getJoueur() == &this->joueurs[1]) {
								deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 2, colonne - 2), this->damier.getCase(ligne - 1, colonne - 1)->getPiece()));
							}
						}
					}
				}
				if (colonne + 2 < this->damier.getNbrColonnes()) {///CASE GAUCHE EXISTE
					if (this->damier.getCase(ligne - 2, colonne + 2)->estVide()) {
						if (this->damier.getCase(ligne - 1, colonne + 1)->estVide() == false) {
							if (this->damier.getCase(ligne - 1, colonne + 1)->getPiece()->getJoueur() == &this->joueurs[1]) {
								deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 2, colonne + 2), this->damier.getCase(ligne - 1, colonne + 1)->getPiece()));
							}
						}
					}
				}
			}
		}
		///REGLES POUR LES DAMES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (p->getNom() == "Dame") {
			///NORD EST-------------------------------------------------------------------
			int i = ligne, j = colonne,lignePiecePrise(0),colonnePiecePrise(0);
			i--; j++;
			bool prise = false;
			while (i >= 0 && j < this->damier.getNbrColonnes())
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i--; j++;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i >= 0 && j < this->damier.getNbrColonnes()) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i--; j++;
			}
			///SUD EST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i++; j++;
			prise = false;
			while (i < this->damier.getNbrLignes() && j < this->damier.getNbrColonnes())
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i++; j++;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i < this->damier.getNbrLignes() && j < this->damier.getNbrColonnes()) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i++; j++;
			}
			///SUD OUEST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i++; j--;
			prise = false;
			while (i < this->damier.getNbrLignes() && j >= 0)
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i++; j--;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i < this->damier.getNbrLignes() && j >= 0) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i++; j--;
			}
			///NORD OUEST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i--; j--;
			prise = false;
			while (i >= 0 && j >= 0)
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i--; j--;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i >= 0 && j >= 0) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i--; j--;
			}
		}

		if (this->joueurs[this->joueurAyantTour].estHumain()) {
			for (int i = 0; i < (int)deplacements.size(); i++) {
				if (deplacements[i].avecPrise()) {
					this->deplacementsPossibles.push_back(deplacements[i]);
				}
			}
			if (this->deplacementsPossibles.size() == 0) {
				for (int j = 0; j < (int)deplacements.size(); j++) {
					this->deplacementsPossibles.push_back(deplacements[j]);
				}
			}
		}
		else {
			for (int i = 0; i < (int)deplacements.size(); i++) {
				if (deplacements[i].avecPrise()) {
					this->deplacementsPossibles.push_back(deplacements[i]);
					break;
				}
				else if (i == deplacements.size() - 1) {
					for (int j = 0; j < (int)deplacements.size(); j++) {
						if (deplacements[j].avecPrise() == false) 
						{
							this->deplacementsPossibles.push_back(deplacements[j]);
						}
					}
				}
			}
		}
	}
	else {///REGLES POUR JOUEUR EN BAS
		///REGLES POUR LES PIONS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (p->getNom() == "Pion") {
			if (colonne + 1 < this->damier.getNbrColonnes()) {///CASE GAUCHE EXISTE
				if (this->damier.getCase(ligne - 1, colonne + 1)->estVide()) {///SI LA CASE GAUCHE EST VIDE
					deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 1, colonne + 1), 0));
				}
				else {///LE CAS D'UNE PRISE A DROITE
					if (colonne + 2 < this->damier.getNbrColonnes()) {
						if (ligne - 2 >= 0) {
							if (this->damier.getCase(ligne - 2, colonne + 2)->estVide()) {
								if (this->damier.getCase(ligne - 1, colonne + 1)->getPiece()->getJoueur() == &this->joueurs[0]) {
									deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 2, colonne + 2), this->damier.getCase(ligne - 1, colonne + 1)->getPiece()));
								}
							}
						}
					}
				}
			}
			if (colonne - 1 >= 0) {///CASE DROITE EXISTE
				if (this->damier.getCase(ligne - 1, colonne - 1)->estVide()) {///SI LA CASE DROITE EST VIDE
					deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 1, colonne - 1), 0));
				}
				else {///LE CAS D'UNE PRISE A GAUCHEE
					if (colonne - 2 >= 0) {
						if (ligne - 2 >= 0) {
							if (this->damier.getCase(ligne - 2, colonne - 2)->estVide()) {
								if (this->damier.getCase(ligne - 1, colonne - 1)->getPiece()->getJoueur() == &this->joueurs[0]) {
									deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne - 2, colonne - 2), this->damier.getCase(ligne - 1, colonne - 1)->getPiece()));
								}
							}
						}
					}
				}
			}
			if (ligne + 2 < this->damier.getNbrLignes()) {///LE CAS D'UNE PRISE EN ARRIERE
				if (colonne - 2 >= 0) {///CASE GAUCHE EXISTE
					if (this->damier.getCase(ligne + 2, colonne - 2)->estVide()) {
						if (this->damier.getCase(ligne + 1, colonne - 1)->estVide() == false) {
							if (this->damier.getCase(ligne + 1, colonne - 1)->getPiece()->getJoueur() == &this->joueurs[0]) {
								deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 2, colonne - 2), this->damier.getCase(ligne + 1, colonne - 1)->getPiece()));
							}
						}
					}
				}
				if (colonne + 2 < this->damier.getNbrColonnes()) {///CASE DROITE EXISTE
					if (this->damier.getCase(ligne + 2, colonne + 2)->estVide()) {
						if (this->damier.getCase(ligne + 1, colonne + 1)->estVide() == false) {
							if (this->damier.getCase(ligne + 1, colonne + 1)->getPiece()->getJoueur() == &this->joueurs[0]) {
								deplacements.push_back(*new Mouvement(joueurAyantTour, p, p->getCase(), this->damier.getCase(ligne + 2, colonne + 2), this->damier.getCase(ligne + 1, colonne + 1)->getPiece()));
							}
						}
					}
				}
			}
		}
		///REGLES POUR LES DAMES++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (p->getNom() == "Dame") {
			///NORD EST-------------------------------------------------------------------
			int i = ligne, j = colonne, lignePiecePrise(0), colonnePiecePrise(0);
			i--; j++;
			bool prise = false;
			while (i >= 0 && j < this->damier.getNbrColonnes())
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i--; j++;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i >= 0 && j < this->damier.getNbrColonnes()) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i--; j++;
			}
			///SUD EST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i++; j++;
			prise = false;
			while (i < this->damier.getNbrLignes() && j < this->damier.getNbrColonnes())
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i++; j++;
					}
					else
					{
						break;
					}
				}
				if (prise) {
					if (i < this->damier.getNbrLignes() && j < this->damier.getNbrColonnes()) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i++; j++;
			}
			///SUD OUEST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i++; j--;
			prise = false;
			while (i < this->damier.getNbrLignes() && j >= 0)
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i++; j--;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i < this->damier.getNbrLignes() && j >= 0) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i++; j--;
			}
			///NORD OUEST-------------------------------------------------------------------
			i = ligne, j = colonne;
			i--; j--;
			prise = false;
			while (i >= 0 && j >= 0)
			{
				if (this->damier.getCase(i, j)->estVide() && prise == false) {
					deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), 0));
				}
				else if (prise == false) {
					if (this->damier.getCase(i, j)->getPiece()->getJoueur() != &this->joueurs[this->joueurAyantTour]) {
						prise = true;
						lignePiecePrise = i;
						colonnePiecePrise = j;
						i--; j--;
					}
					else {
						break;
					}
				}
				if (prise) {
					if (i >= 0 && j >= 0) {
						if (this->damier.getCase(i, j)->estVide()) {
							deplacements.push_back(*new Mouvement(this->joueurAyantTour, p, p->getCase(), this->damier.getCase(i, j), this->damier.getCase(lignePiecePrise, colonnePiecePrise)->getPiece()));
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}
				i--; j--;
			}
		}

		for (int i = 0; i < (int)deplacements.size(); i++) {
			if (deplacements[i].avecPrise()) {
				this->deplacementsPossibles.push_back(deplacements[i]);
			}
		}
		if (this->deplacementsPossibles.size() == 0) {
			for (int j = 0; j < (int)deplacements.size(); j++) {
				this->deplacementsPossibles.push_back(deplacements[j]);
			}
		}
	}

}

Case *DamesInternationale::lireCommande(string s) {
	int x(-1);
	int y(-1);
	if (s.length() == 2) {
		if (((int)s[0] > 48) && ((int)s[0] <= 57)) {
			x = ((int)s[0]) - 49;
			if (((int)s[1] >= 97) && ((int)s[1] <= 122)) {
				y = ((int)s[1]) - 97;
			}
		}
		else if (((int)s[1] > 48) && ((int)s[1] <= 57)) {
			x = ((int)s[1]) - 49;
			if (((int)s[0] >= 97) && ((int)s[0] <= 122)) {
				y = ((int)s[0]) - 97;
			}
		}

		if (x != -1 && y != -1) {
			return this->damier.getCase(x, y);
		}
		else {
			return 0;
		}
	}
	else {
		if (((int)s[0] > 48) && ((int)s[0] <= 57) && ((int)s[1] > 47) && ((int)s[1] <= 57)) {
			x = (((int)s[0]) - 48) * 10;
			x += ((int)s[1]) - 48;
			if (((int)s[2] >= 97) && ((int)s[2] <= 122)) {
				y = ((int)s[2]) - 97;
			}
		}
		else if (((int)s[1] > 48) && ((int)s[1] <= 57) && ((int)s[2] > 47) && ((int)s[2] <= 57)) {
			x = (((int)s[1]) - 48) * 10;
			x += ((int)s[2]) - 48;
			if (((int)s[0] >= 97) && ((int)s[0] <= 122)) {
				y = ((int)s[0]) - 97;
			}
		}

		if (x != -1 && y != -1) {
			return this->damier.getCase(x - 1, y);
		}
		else {
			return 0;
		}
	}
}

int DamesInternationale::getDeplacementIndex(Case *c) {
	for (int i = 0; i < (int)this->deplacementsPossibles.size(); i++) {
		if (this->deplacementsPossibles[i].getCaseDestination() == c) {
			return i;
		}
	}
	return -1;
}

Case * DamesInternationale::selectionnerCase(string s)
{
	Case *caseSelectionee = this->lireCommande(s);
	if (caseSelectionee != 0) {///SI LA CASE SELECTIONNEE EXISTE
		if (caseSelectionee->estVide() == false) {///SI LA CASE SELECTIONNEE N'EST PAS VIDE
			if (caseSelectionee->getPiece()->getJoueur() == &this->joueurs.at(this->joueurAyantTour)) {///SI LE JOUEUR AYANT LE TOUR POSSEDE CETTE PIECE
				this->trouverDeplacements(caseSelectionee->getPiece());
				if (this->deplacementsPossibles.size() != 0) {
					return caseSelectionee;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
	return 0;
}

void DamesInternationale::deplacerPiece(Case *caseSelectionee) {
	///DEPLACEMENT POUR JOUEUR HUMAIN++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if (this->joueurs[this->joueurAyantTour].estHumain()) {
		string s = "";
		string caseChoisi = "";
		if (caseSelectionee->getLigne() < 8) {
			caseChoisi += (char)(caseSelectionee->getLigne() + 49);
			caseChoisi += (char)(caseSelectionee->getColonne() + 97);
		}
		else {
			caseChoisi += to_string(caseSelectionee->getLigne() + 1);
			caseChoisi += (char)(caseSelectionee->getColonne() + 97);
		}
		cout << "Suggestions:";
		this->afficherSuggestions();///AFFICHER LES CASE SUGGEREE POUR DEPLACER LA PIECE
		while (true)
		{
			cout << "[Joueur " << this->joueurAyantTour + 1 << "] Deplacer {" << caseChoisi << "} vers: ";
			cin.ignore();
			cin >> s;///LIRE LA CASE SAISIE PAR LE JOUEUR
			if (s.length() == 2 || s.length() == 3) {
				Case *c = this->lireCommande(s);
				int i = this->getDeplacementIndex(c);
				if (i >= 0) {///SI LA CASE CHOISIE EST VALIDE
					this->historique.push_back(this->deplacementsPossibles[i]);///AJOUTER LE DEPLACEMENT DANS L'HISTORIQUE DES DEPLACEMENT
					this->joueurs[this->joueurAyantTour].deplasserPiece(caseSelectionee->getPiece(), c);///FAIRE DEPLACER LA PIECE A LA CASE CHOISI
					
					if (this->deplacementsPossibles[i].avecPrise() == false) {///QUAND IL N'Y A PAS DE PRISE
						///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER AVEC UNE DAME)---------------------------------------------
						if ((this->joueurAyantTour == 0) && (c->getPiece()->getNom() == "Pion")) {
							if (c->getLigne() == this->damier.getNbrLignes() - 1) {
								this->joueurs[0].deplasserPiece(c->getPiece(), 0);
								ajouterDame(0, c);
							}
						}
						else if ((this->joueurAyantTour == 1) && (c->getPiece()->getNom() == "Pion")) {
							if (c->getLigne() == 0) {
								this->joueurs[1].deplasserPiece(c->getPiece(), 0);
								ajouterDame(1, c);
							}
						}
						this->deplacementsPossibles.clear();
						///---------------------------------------------------------------------------------------------------------------
						this->changerTour();
						break;
					}
					else {///QUAND IL Y A UNE PRISE
						this->joueurs[joueurAyantTour].deplasserPiece(this->deplacementsPossibles[i].getPiecePrise(), 0);///FAIRE SORTIR LA PIECE PRISE DEHORS LE PLATEAU
						if (this->deplacementsPossibles[i].getPiecePrise()->getNom() == "Dame" && c->getPiece()->getNom() == "Pion") {
							this->changerTour();
							break;
						}
						///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER AVEC UNE DAME)---------------------------------------------
						if ((this->joueurAyantTour == 0) && (c->getPiece()->getNom() == "Pion")) {
							if (c->getLigne() == this->damier.getNbrLignes() - 1) {
								this->joueurs[0].deplasserPiece(c->getPiece(), 0);
								ajouterDame(0, c);
							}
						}
						else if ((this->joueurAyantTour == 1) && (c->getPiece()->getNom() == "Pion")) {
							if (c->getLigne() == 0) {
								this->joueurs[1].deplasserPiece(c->getPiece(), 0);
								ajouterDame(1, c);
							}
						}
						this->deplacementsPossibles.clear();
						///---------------------------------------------------------------------------------------------------------------
						
						this->trouverDeplacements(c->getPiece());///RECHERCHER DES NOUVEAUX DEPLACEMENTS POSSIBLE
						int indicePrise = this->getPriseIndice();
						if (indicePrise == -1) {///QUAND IL N'Y A PAS DE PRISE
							this->changerTour();
							break;
						}
						else
						{
							system("CLS");
							cout << "- Tapez 's' pour selectionner une piece" << endl;
							cout << "- Tapez 'q' pour quiter la partie" << endl;
							cout << "- Tapez 'r' pour annuler le deplacement" << endl << "----------------------------------------------------------------------------------------" << endl << endl;
							cout << "                             JOUEUR 1 [" << this->nombrePieceDansPlateau(0) << " Pieces restantes]" << endl;
							this->damier.afficher();
							cout << "                             JOUEUR 2 [" << this->nombrePieceDansPlateau(1) << " Pieces restantes]" << endl << endl;
							cout << "----------------------------------------------------------------------------------------" << endl;

							this->deplacerPiece(c);
							break;
						}
						this->changerTour();
					}
				}
				else {
					cout << "Deplacement Invalide !" << endl;
				}
			}
			else {
				this->executeCmd(s);
			}
		}
	}
	///DEPLACEMENT POUR JOUEUR PC++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	else {
		int indiceDePrise = this->getPriseIndice();
		///DEPLACEMENT SANS PRISE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if (indiceDePrise == -1) {
			this->historique.push_back(this->deplacementsPossibles[0]);///AJOUTER LE DEPLACEMENT DANS L'HISTORIQUE DES DEPLACEMENT
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			this->joueurs[this->joueurAyantTour].deplasserPiece(caseSelectionee->getPiece(), this->deplacementsPossibles[0].getCaseDestination());///FAIRE DEPLACER LA PIECE A LA CASE CHOISI
			///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER AVEC UNE DAME)-----------------------------------------------																																  ///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER VERS UNE DAME)---------------------------------------------
			if (this->deplacementsPossibles[0].getPiece()->getNom() == "Pion") {
				if (this->deplacementsPossibles[0].getPiece()->getCase()->getLigne() == this->damier.getNbrLignes() - 1) {
					this->joueurs[this->joueurAyantTour].deplasserPiece(this->deplacementsPossibles[0].getCaseDestination()->getPiece(), 0);
					ajouterDame(this->joueurAyantTour, this->deplacementsPossibles[0].getCaseDestination());
				}
			}
			this->changerTour();
			///---------------------------------------------------------------------------------------------------------------
		}
		///DEPLACEMENT AVEC PRISE++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else {
			this->historique.push_back(this->deplacementsPossibles[indiceDePrise]);///AJOUTER LE DEPLACEMENT DANS L'HISTORIQUE DES DEPLACEMENT
			this_thread::sleep_for(std::chrono::milliseconds(1500));
			this->joueurs[this->joueurAyantTour].deplasserPiece(caseSelectionee->getPiece(), this->deplacementsPossibles[indiceDePrise].getCaseDestination());///FAIRE DEPLACER LA PIECE A LA CASE CHOISI
			this->joueurs[joueurAyantTour].deplasserPiece(this->deplacementsPossibles[indiceDePrise].getPiecePrise(), 0);///FAIRE SORTIR LA PIECE PRISE DEHORS LE PLATEAU

			///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER AVEC UNE DAME)-----------------------------------------------																																  ///QUAND LE PION ARRIVE A LA FIN DU PLATEAU (CHANGER VERS UNE DAME)---------------------------------------------
			if (this->deplacementsPossibles[indiceDePrise].getPiece()->getNom() == "Pion") {
				if (this->deplacementsPossibles[indiceDePrise].getPiece()->getCase()->getLigne() == this->damier.getNbrLignes() - 1) {
					this->joueurs[this->joueurAyantTour].deplasserPiece(this->deplacementsPossibles[indiceDePrise].getCaseDestination()->getPiece(), 0);
					ajouterDame(this->joueurAyantTour, this->deplacementsPossibles[indiceDePrise].getCaseDestination());
				}
			}
			///---------------------------------------------------------------------------------------------------------------

			Piece *p = this->deplacementsPossibles[indiceDePrise].getCaseDestination()->getPiece();
			this->deplacementsPossibles.clear();
			this->trouverDeplacements(p);
			if (this->deplacementsPossibles.size() > 0) {///S'IL EXISTE DES NOUVEAUX DEPLACEMENTS POSSIBLE
				indiceDePrise = this->getPriseIndice();
				if (indiceDePrise > -1) {///S'IL EXISTE UN DEPLACEMENT AVEC PRISE
					system("CLS");
					cout << "- Tapez 's' pour selectionner une piece" << endl;
					cout << "- Tapez 'q' pour quiter la partie" << endl;
					cout << "- Tapez 'r' pour annuler le deplacement" << endl << "----------------------------------------------------------------------------------------" << endl << endl;
					cout << "                             JOUEUR 1 [" << this->nombrePieceDansPlateau(0) << " Pieces restantes]" << endl;
					this->damier.afficher();
					cout << "                             JOUEUR 2 [" << this->nombrePieceDansPlateau(1) << " Pieces restantes]" << endl << endl;
					cout << "----------------------------------------------------------------------------------------" << endl;
					this->deplacerPiece(this->deplacementsPossibles[indiceDePrise].getCaseSource());
					//this_thread::sleep_for(std::chrono::milliseconds(1500));
				}
				else {
					this->changerTour();
					//this->lancer();
				}
			}
			else
			{
				this->changerTour();
				//this->lancer();
			}
		}
	}
}

void DamesInternationale::executeCmd(string s)
{
	if (s == "s" || s == "S") {
		//this->lancer();
	}
	if (s == "q" || s == "Q") {
		this->joueurVainqueur = -2;
		//arreter la partie
	}
	if (s == "r" || s == "R") {
		if (this->joueurs[0].estHumain()) {///LE CAS OU LA PARTIE EST ENTRE DEUX HUMAIN
			if (this->historique.size() > 0) {
				if (this->historique[this->historique.size() - 1].getJoueur() != this->joueurAyantTour) {
					this->annulerMouvement();
					this->changerTour();
				}
				else {
					this->annulerMouvement();
				}
			}
		}
		else///LE CAS OU LA PARTIE EST ENTRE PC ET HUMAIN
		{
			if (this->historique.size() > 0) {
				while (this->historique.size() > 0)
				{
					if (this->historique[this->historique.size() - 1].getJoueur() == 0 && this->historique.size() != 1) {
						this->annulerMouvement();
					}
					else {
						break;
					}
				}
				if (this->historique.size() > 0 && this->historique[this->historique.size() - 1].getJoueur() == 1) {
					this->annulerMouvement();
				}
			}
		}
		this->deplacementsPossibles.clear();
	}
}

void DamesInternationale::annulerMouvement()
{
	if (this->historique.size() > 0) {
		int j = this->historique[this->historique.size() - 1].getJoueur();
		Piece *p = this->historique[this->historique.size() - 1].getPiece();
		Case *c = this->historique[this->historique.size() - 1].getCaseSource();
		this->joueurs[j].deplasserPiece(p, c);
		if (this->historique[this->historique.size() - 1].avecPrise()) {///S'IL Y A UNE PRISE ALORS REMETRE LA PIECE PRIE DANS LE PLATEAU
			p = this->historique[this->historique.size() - 1].getPiecePrise();
			c = this->historique[this->historique.size() - 1].getCasePiecePriese();
			this->joueurs[j].deplasserPiece(p, c);
		}
		this->historique.pop_back();
	}
}

void DamesInternationale::ajouterDame(int Joueur,Case *c)
{
	if (Joueur == 0) {
		this->joueurs[0].ajouterPiece(new Piece('M', "Dame"));
	}
	else if (Joueur == 1) {
		this->joueurs[1].ajouterPiece(new Piece('S', "Dame"));
	}
	this->joueurs[Joueur].deplasserPiece(this->joueurs[Joueur].getPieces()[this->joueurs[Joueur].getPieces().size() - 1], c);
}

bool DamesInternationale::estTermine()
{
	int nbrPiecesDansPlateau1 = this->nombrePieceDansPlateau(0);
	int nbrPiecesDansPlateau2 = this->nombrePieceDansPlateau(1);
	if (nbrPiecesDansPlateau1 > 0 && nbrPiecesDansPlateau2 > 0) {
		for (int i = 0; i < (int)this->joueurs[this->joueurAyantTour].getPieces().size(); i++) {
			if (this->joueurs[this->joueurAyantTour].getPieces()[i]->estDehorsPlateau() == false) {
				this->trouverDeplacements(this->joueurs[this->joueurAyantTour].getPieces()[i]);
			}
		}
		int nbrDeplacement = this->deplacementsPossibles.size();

		if (nbrDeplacement > 0) {
			return false;
		}
		else if (nbrDeplacement == 0){
			changerTour();
			this->joueurVainqueur = this->joueurAyantTour;
			return true;
		}
	}
	else if (nbrPiecesDansPlateau1 == 0){
		this->joueurVainqueur = 1;
		return true;
	}
	else if (nbrPiecesDansPlateau2 == 0){
		this->joueurVainqueur = 0;
		return true;
	}
}
