#include <iostream>
#include <string>
#include <vector>
#include "Case.h"
#include "Plateau.h"
#include "Piece.h"
#include "Partie.h"
#include "DamesInternationale.h"
using namespace std;

char menuChoixAdversaire(int numJeu) {
	char c(' ');
	while (true) {
		system("CLS");
		switch (numJeu) {
		case 1:
			cout << "Dames (Internationale)" << endl;
			break;
		case 2:
			cout << "Dames (Anglaise)" << endl;
			break;
		case 3:
			cout << "#########" << endl;
			break;
		}
		cout << "1- Joueur VS Joueur" << endl << "2- Joueur VS Ordinateur" << endl << "0- Retour" << endl;
		cout << "Tapez un numero: ";
		cin >> c;
		if (c == '1' || c == '2' || c == '0') {
			system("CLS");
			return c;
		}
	}
	return '0';
}
char menuPartie(int numJeu) {
	char c(' ');
	while (true) {
		system("CLS");
		switch (numJeu) {
		case 1:
			cout << "Dames (Internationale)" << endl;
			break;
		case 2:
			cout << "Dames (Anglaise)" << endl;
			break;
		case 3:
			cout << "########" << endl;
			break;
		}
		cout << "1- Nouvelle Partie" << endl << "2- Reprendre" << endl << "0- Retour" << endl;
		cout << "Tapez un numero: ";
		cin >> c;
		if (c == '1' || c == '2' || c == '0') {
			system("CLS");
			return c;
		}
	}
	return '0';
}
char menuPrincipale() {
	char c(' ');
	while (true) {
		system("CLS");
		cout << "Bienvenu ! voici la liste des jeux:" << endl;
		cout << "1- Dames (Internationale)" << endl << "2- ##########" << endl << "3- #########" << endl << endl << "0- Quitter" << endl;
		cout << "Tapez le numero du jeu: ";
		cin >> c;
		if (c == '1' || c == '2' || c == '3' || c == '0') {
			system("CLS");
			return c;
		}
	}
	return '0';
}

int main()
{
	int jeuChoisi(0), partieChoisi(0);
	int adversaire(0);
	while (true)
	{
		jeuChoisi = ((int)menuPrincipale()) - 48;///CHOISIR LE JEU
		if (jeuChoisi > 0) {
			partieChoisi = ((int)menuPartie(jeuChoisi)) - 48;///CHOISIR (NOUVELLE PARTIE/REPRENDRE PARITE)
			switch (jeuChoisi)
			{
			case 1:///JEU DAMES INTERNATIONALE
				if (partieChoisi == 1) {///NOUVELLE PARTIE
					adversaire = (int)menuChoixAdversaire(jeuChoisi) - 49;///CHOISIR L'ADVERSAIRE
					if (adversaire == 1) {///VS PC
						DamesInternationale partieDamesInternationale(false);
						partieDamesInternationale.lancer();
						//partieDamesInternationale.sauvgarder();
						partieDamesInternationale.~DamesInternationale();
					}
					else if (adversaire == 0) {///VS JOUEUR
						DamesInternationale partieDamesInternationale(true);
						partieDamesInternationale.lancer();
						//partieDamesInternationale.sauvgarder();
						partieDamesInternationale.~DamesInternationale();
					}
					else {///RETOUR
						break;
					}
				}
				else if (partieChoisi == 2) {///REPRENDRE PARTIE

				}
				else {///RETOUR
					break;
				break;
			case 2:///#############
				break;
			case 3:///#############
				break;
				}
			}
		} else {
			return 0;
		}
	}
	main();
}
