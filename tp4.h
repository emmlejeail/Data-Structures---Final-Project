#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct Benevole
{
    char nom[20];
    char prenom[20];
    char sexe;
    int annee;
    int CIN;
    struct Benevole *suivant;

}BENEVOLE;


typedef struct ListBenevoles
{
    BENEVOLE *benevole;
    int nbrElements;

}LISTBENEVOLES;

typedef struct Tranche
{
    LISTBENEVOLES *liste;
    int borneSup;
    struct Tranche *pere;
    struct Tranche *filsG;
    struct Tranche *filsD;

}TRANCHE;

struct element{
	TRANCHE *tranche;
	struct element *suivant;
};

typedef struct pile{
	struct element *tete;
	int taille;
}PILE;

BENEVOLE *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee);
TRANCHE *nouvelleTranche(int borneSup);
LISTBENEVOLES *nouvelleListe();

TRANCHE *ajoutTranche(TRANCHE *racine, int borneSup);
void afficherArbre(TRANCHE *racine);
BENEVOLE *chercherBen(TRANCHE *racine, int CIN, int *annee);

int supprimerTranche(TRANCHE *racine, int borneSup);

TRANCHE *maxABR(TRANCHE *a);
TRANCHE *minABR(TRANCHE *a);
TRANCHE *succABR(TRANCHE *x);
TRANCHE *predABR(TRANCHE *x);

int totalBenTranche(TRANCHE *racine, int borneSup);
void afficherTranche(TRANCHE *racine, int borneSup);
float pourcentageTranche(TRANCHE *racine, int borneSup);

int supprimerBen(TRANCHE *racine, int CIN, int annee);
BENEVOLE *insererBen(TRANCHE *racine, BENEVOLE *benevole);
BENEVOLE* insererListeBen(LISTBENEVOLES* liste, BENEVOLE* benevole);

int totalBenTranche(TRANCHE *racine, int borneSup);
int totalBen(TRANCHE *racine);
TRANCHE* max(TRANCHE* racine);
LISTBENEVOLES *BenDhonneur(TRANCHE *racine);

void afficherListe(LISTBENEVOLES *liste);

int detruireABR(TRANCHE *racine);

int actualiser(TRANCHE *racine);

int anneeActuelle();

PILE *CreerPile();
int pileVide(PILE *p);
void empiler(TRANCHE *racine, PILE *p);
TRANCHE *depiler(PILE *p);

#endif // TP4_H_INCLUDED
