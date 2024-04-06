#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED
#include <vector>
#include <string>
#include "Plateau.h"
#include "Case.h"
#include "Piece.h"
#include "Joueur.h"
#include "Mouvement.h"

class Partie {
protected:
	int joueurAyantTour;///LE JOUEUR QUI A LE TOUR DE JOUER
	int joueurVainqueur;///LE JOUEUR QUI A GAGNIE
	vector<Joueur> joueurs;///LES JOUEURS
	vector<Mouvement> historique;///L'HISTORIQUE DES MOUVMENETS EFECTUEE PAR LES JOUEURS
	vector<Mouvement> deplacementsPossibles;///LISTE DES CASE QUE CETTE PIECE PEUT ATTENDRE SELEON LES REGLES DE JEU

	int nbrAleatoire(int MIN, int MAX);
	void changerTour();///PASSER LE TOUR POUR UN AUTRE JOUEUR
	virtual void annulerMouvement()=0;///ANNULER UN MOUVEMENT
	void lancer();///DEMARER LA PARTIE
	void sauvgarder();///SAUVGARDER LA PARTIE
	Case *lireCommande(string s);///LIRE LES COMMANDES SAISE PAR L'UTILISATEUR POUR DETERMINER LA CASE VOULU
	virtual void trouverDeplacements(Piece *p)= 0;///TROUVER TOUT LES CASES POSSIBLE POUR QUE CETTE PIECE PEUT ATTEINDRE EN RESPECTANT DES REGLES
	void afficherSuggestions();///AFFICHER LES SUGGESTION DES DEPLACEMENTS POSSIBLES
	bool deplacementValide(Case *c);///TESTER SI LE DEPLASEMENT DEMANDEE PAR L'USTILISATEUR VERS UNE CASE EST VALIDE
	virtual void deplacerPiece(Case *caseSelectionee) = 0;///DEPLACER LA PIECE SELECTIONNEE PAR L'UTILISATEUR VERS LA CASE DESTINATION
	int getDeplacementIndex(Case *c);///RETOURNER L'INDICE DU DEPLACEMENT DANS LE VECTEUR DES DEPLACEMENTS A PARTIR D'UNE CASE DONNEE
	virtual Case *selectionnerCase(string s) = 0;///LIRE LA CHAINE DE CARACTERE SASIE PAR L'UTILISATEUR ET TROUVER LA CASE VOULU PAR CETTE CHAINE
	virtual void executeCmd(string s) = 0;///EXECUTER LES COMMANDES (EXEMEPLE: ANNULER LE DEPLACEMENT D'UNE PIECE, QUITER LA PARTIE ...)
	int getPriseIndice();///RECUPERER L'INDICE DU DEPLACEMENT QUI CONTIENT UNE PRISE (RETOURNER -1 S'IL N'Y A PAS DE PRISE)
	int nombrePieceDansPlateau(int indiceJoueur);///COMPTER LE NOMBRE DE PIECES D'UN JOUEUR QUI SONT DANS LE PLATAEU
	virtual bool estTermine() = 0;///VERIFIER L'ETAT DE LA PARTIE SI ELLE EST TERMINE OU NON
public:
	Partie();///CONSTRUCTEUR
	~Partie();///DESTRUCTEUR
};

#endif // PARTIE_H_INCLUDED
