#ifndef DAMESINTERNATIONALE_H_INCLUDED
#define DAMESINTERNATIONALE_H_INCLUDED
#include "Plateau.h"
#include "Partie.h"
#include <vector>
#include <string>

class DamesInternationale : public Partie {
private:
	Plateau damier = *new Plateau(10, 10);///LE DAMIER
	int getDeplacementIndex(Case * c);
	Case * selectionnerCase(string s);
	void deplacerPiece(Case * caseSelectionee);
	void executeCmd(string s);
	void annulerMouvement();
	void ajouterDame(int Joueur, Case * c);
	void trouverDeplacements(Piece *p);
	Case *lireCommande(string s);
public:
	DamesInternationale();
	DamesInternationale(bool humain);
	~DamesInternationale();
	void lancer();
	bool estTermine();
};

#endif // DAMESINTERNATIONALE_H_INCLUDED