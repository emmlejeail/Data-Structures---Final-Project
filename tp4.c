#include"tp4.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

BENEVOLE *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee)
{
    BENEVOLE *nouveau=malloc(sizeof(BENEVOLE));
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    nouveau->CIN=CIN;
    nouveau->sexe=sexe;
    nouveau->annee=annee;
    nouveau->suivant=NULL;
    return nouveau;
}

TRANCHE *nouvelleTranche(int borneSup)
{
    TRANCHE *nouvelle=malloc(sizeof(TRANCHE));
    nouvelle->liste=nouvelleListe();
    nouvelle->borneSup=borneSup;
    nouvelle->pere=NULL;
    nouvelle->filsG=NULL;
    nouvelle->filsD=NULL;
    return nouvelle;
}

LISTBENEVOLES *nouvelleListe()
{
    LISTBENEVOLES *nouvelle=malloc(sizeof(LISTBENEVOLES));
    nouvelle->benevole=NULL;
    nouvelle->nbrElements=0;
    return nouvelle;
}

TRANCHE *ajoutTranche(TRANCHE *racine, int borneSup)
{
    TRANCHE *nouv = nouvelleTranche(borneSup);
    TRANCHE *courant=racine;
    TRANCHE *pere=racine;
    if (racine==NULL)
    {
        return NULL;
    }
    else
    {
        while(courant!=NULL)
        {
            if (borneSup<courant->borneSup)///on va dans le sous arbre gauche
            {
                pere=courant;
                courant=courant->filsG;
            }
            else if (borneSup>courant->borneSup)///on va dans le sous-arbre droit
            {
                pere=courant;
                courant=courant->filsD;
            }
            else if (borneSup==courant->borneSup)
            {
                printf("Cette tranche existe deja.\n");
                return courant;
            }
        }
        if (pere->borneSup<borneSup)
        {
            pere->filsD=nouv;
            nouv->pere=pere;
            return nouv;
        }
        else if (pere->borneSup>borneSup)
        {
            pere->filsG=nouv;
            nouv->pere=pere;
            return nouv;
        }
    }
}
TRANCHE *minABR(TRANCHE *a)
{
    if (a->filsG==NULL)
    {
        return a;
    }
    else
    {
        return minABR(a->filsG);
    }
}

TRANCHE *maxABR(TRANCHE *a)
{
    if(a->filsD==NULL)
    {
        return a;
    }
    else
    {
        return maxABR(a->filsD);
    }
}

TRANCHE *succABR(TRANCHE *x)
{
    if (x->filsD!=NULL)
    {
        return minABR(x->filsD);
    }
    else
    {
        TRANCHE *y=x->pere;
        while((y!=NULL) && (x==y->filsD))
        {
            x=y;
            y=y->pere;
        }
        return y;
    }
}

TRANCHE *predABR(TRANCHE *x)
{
    if(x->filsG!=NULL)
    {
        return maxABR(x->filsG);
    }
    else
    {
        TRANCHE *y=x->pere;
        while((y!=NULL)&&(x==y->filsG))
        {
            x=y;
            y=y->pere;
        }
        return y;
    }
}

void afficherArbre(TRANCHE *racine)
{
    if (racine!=NULL)
    {
        afficherArbre(racine->filsG);
        printf(" %d |", racine->borneSup);
        afficherArbre(racine->filsD);
        printf("\n");
    }
}

TRANCHE *trouverTranche(TRANCHE *racine, int borneSup)
{
    if(racine == NULL)
    {
        return NULL;
    }

    TRANCHE *courant=racine;
    while((courant!=NULL)&&(courant->borneSup!=borneSup))
    {
        if(courant->borneSup<borneSup)
        {
            courant=courant->filsD;
        }
        if(courant->borneSup>borneSup)
        {
            courant=courant->filsG;
        }
    }
    return courant;
}

BENEVOLE *chercherBen(TRANCHE *racine, int CIN, int *annee){
  //renvoie 0 quand le b�n�vole n'est pas dans la liste
  //on commence par chercher la tranche
  int age=anneeActuelle()-*annee;
  int tranche=(age%5==0) ? age : ((age/5)+1)*5;
  TRANCHE *courant=racine;
  while((courant!=NULL) && (courant->borneSup!=tranche)){
    if (tranche<courant->borneSup)
        courant=courant->filsG;
    else if (tranche>courant->borneSup)
        courant=courant->filsD;
  }
  if ((courant==NULL) || (courant->liste==NULL)) {//la tranche dans laquelle le b�n�vole devrait �tre n'existe pas, ou elle est vide
    return NULL;
  }

  BENEVOLE *benevole=courant->liste->benevole;
  while((benevole!=NULL) && (benevole->CIN!=CIN))
  {
    benevole=benevole->suivant;
  }
  return benevole;
}

int viderListe (LISTBENEVOLES *liste)
{
    if(liste->benevole!=NULL)
    {
        BENEVOLE *beneCourant=liste->benevole;
        while(beneCourant!=NULL)
        {
            liste->benevole=beneCourant->suivant;
            free(beneCourant);
            beneCourant=liste->benevole;
        }
    }
    return 0;
}

BENEVOLE* insererListeBen(LISTBENEVOLES* liste, BENEVOLE* benevole)
{
  //fonction qui ins�re un b�n�vole dans une liste de b�n�voles

  if (liste->benevole==NULL)
    { //la liste des benevoles est vide
      liste->benevole=benevole;
      liste->nbrElements+=1;
    }
  else
    {//la liste des benevoles est non vide
    BENEVOLE* benevoleListe=liste->benevole;
    BENEVOLE* benevoleListePred=liste->benevole;

    while((benevoleListe!=NULL) && (benevoleListe->annee>=benevole->annee) && (benevoleListe->CIN!=benevole->CIN))
    {
      benevoleListePred=benevoleListe;
      benevoleListe=benevoleListe->suivant;
    }
    if (benevoleListe==NULL) {//insertion en fin de liste
      benevoleListePred->suivant=benevole;
      liste->nbrElements+=1;
      return benevole;
    }
    if (benevoleListe->CIN!=benevole->CIN)
    {//teste si le b�n�vole n'est pas d�j� dans la liste
      if (benevoleListe==liste->benevole)
      {// il faut ins�rer en d�but de liste->benevole
        benevole->suivant=liste->benevole;
        liste->benevole=benevole;
      }else
      {
        benevole->suivant=benevoleListe;
        benevoleListePred->suivant=benevole;
      }
      liste->nbrElements+=1;
    }else
    {
      printf("Le benevole est deja dans la liste\n");
      return NULL;
    }
  }
  return benevole;
}

BENEVOLE *insererBen(TRANCHE *racine, BENEVOLE *benevole)
{
  /* le prototype de la fonction donn� dans l'�nonc� ne permet pas de
  modifier la racine (pas de double pointeur et on doit renvoyer un BENEVOLE*),
  il donc faut absolument que l'ABR soit non vide avant d'appeler cette fonction!!!
  donc il faut faire "1) initialiser un arbre"
  mais quel est l'int�ret de renvoyer benevole?*/
  TRANCHE* noeud=racine;
  int age=anneeActuelle()-benevole->annee;
  int trancheBen=(age%5==0) ? age : ((age/5)+1)*5;

  noeud=ajoutTranche(racine,trancheBen);
  BENEVOLE* temp=insererListeBen(noeud->liste,benevole);
  return temp;
}

int supprimerBen(TRANCHE *racine, int CIN, int annee){
  //renvoie 1 quand le b�n�vole n'est pas dans la liste
  //on commence par chercher la tranche
  int age=anneeActuelle()-annee;
  int tranche=(age%5==0) ? age : ((age/5)+1)*5;
  TRANCHE *courant=racine;
  while((courant!=NULL) && (courant->borneSup!=tranche)){
    if (tranche<courant->borneSup)
        courant=courant->filsG;
    else if (tranche>courant->borneSup)
        courant=courant->filsD;
  }
  if ((courant==NULL) || (courant->liste==NULL)) {//la tranche dans laquelle le b�n�vole devrait �tre n'existe pas
    return 1;
  }

  BENEVOLE *benevole=courant->liste->benevole;
  BENEVOLE *pred=courant->liste->benevole;
  while((benevole!=NULL) && (benevole->CIN!=CIN))
  {
    pred=benevole;
    benevole=benevole->suivant;
  }
  if (benevole==NULL) {//le b�n�vole n'est pas dans la liste
      return 1;
  }
  if (pred==benevole) {
    courant->liste->benevole=courant->liste->benevole->suivant;
  }else{
    pred->suivant=benevole->suivant;
  }
  free(benevole);
  courant->liste->nbrElements--;
  //si la liste est vide, on supprime la tranche
  if (courant->liste->benevole==NULL) {
    if ((courant==racine) && (racine->filsG==NULL) && (racine->filsD==NULL)) {
      printf("L'arbre est vide. Pour supprimer la racine détruisez l'arbre (12)\n");
    }else{
      supprimerTranche(racine,tranche);
    }
  }
  return 0;
}

int supprimerTranche (TRANCHE *racine, int borneSup){
  //retourne 2 si l'arbre est vide, 1 si la tranche n'existe pas, 0 sinon
  TRANCHE* min=NULL;
  TRANCHE *courant=racine;
  while((courant!=NULL) && (courant->borneSup!=borneSup)){
    if (borneSup<courant->borneSup)
        courant=courant->filsG;
    else if (borneSup>courant->borneSup)
        courant=courant->filsD;
  }
  if (courant==NULL) {
    printf("Impossible de supprimer la tranche.\n");
    return 1;
  }
  viderListe(courant->liste);
  if (courant==racine) {
    //on traite la suppression de la racine comme un cas spécifique seulement quand elle a 0 ou 1 fils, 2 fils ne pose pas de problème
    if ((racine->filsG==NULL) && (racine->filsD==NULL)) { // la racine n'a pas de fils
      free(racine);
      return 2;
    }
    if (racine->filsG==NULL) { // la racine a un fils droit
      min=racine->filsD;
      while (min->filsG!=NULL)
        min=min->filsG;
      racine->liste=min->liste;
      min->liste=NULL;
      racine->borneSup=min->borneSup;
      min->borneSup+=1;
      supprimerTranche(racine, min->borneSup);
      return 0;
    }
    if (racine->filsD==NULL) { // la racine a un fils gauche
      TRANCHE* max=racine->filsG;
      while (max->filsD!=NULL)
        max=max->filsD;
      racine->liste=max->liste;
      max->liste=NULL;
      racine->borneSup=max->borneSup;
      max->borneSup--;
      supprimerTranche(racine, max->borneSup);
      return 0;
    }
  }
  TRANCHE* predcourant=courant->pere;
  if ((courant->filsG==NULL) && (courant->filsD==NULL)) { // courant n'a pas de fils
    if (predcourant->filsG==courant) {
      predcourant->filsG=NULL;
    }else{
      predcourant->filsD=NULL;
    }
    free(courant);
    return 0;
  }
  if (courant->filsG==NULL) { // courant a un fils droit
    courant->filsD->pere=predcourant;
    if (predcourant->filsG==courant) {
      predcourant->filsG=courant->filsD;
    }else{
      predcourant->filsD=courant->filsD;
    }
    free(courant);
    return 0;
  }
  if (courant->filsD==NULL) { // courant a un fils gauche
    courant->filsG->pere=predcourant;
    if (predcourant->filsG==courant) {
      predcourant->filsG=courant->filsG;
    }else{
      predcourant->filsD=courant->filsG;
    }
    free(courant);
    return 0;
  }
  //courant a 2 fils
  min=courant->filsD;
  while (min->filsG!=NULL)
    min=min->filsG;
  courant->liste=min->liste;
  min->liste=NULL;
  courant->borneSup=min->borneSup;
  min->borneSup+=1;
  supprimerTranche(courant, min->borneSup);
  return 0;
}
int totalBenTranche(TRANCHE *racine, int borneSup){
  TRANCHE *courant=racine;
  while((courant!=NULL) && (courant->borneSup!=borneSup)){
    if (borneSup<courant->borneSup)
        courant=courant->filsG;
    else if (borneSup>courant->borneSup)
        courant=courant->filsD;
  }
  if (courant==NULL) {
    return 0;
  }
  return courant->liste->nbrElements;
}

int totalBen(TRANCHE *racine)
{
    if (racine!=NULL) {
      int nbFilsG=totalBen(racine->filsG);
      int nbFilsD=totalBen(racine->filsD);
      //printf("Tranche: %d\n Nb de b�n�voles dans cette tranche:%d\n Nb de b�n�voles d�j� compt�s:%d\n",racine->borneSup,racine->liste->nbrElements,nbFilsG+nbFilsD+racine->liste->nbrElements);
      //afficherTranche(racine, racine->borneSup);
      //printf("\n\n");
      return nbFilsG+nbFilsD+racine->liste->nbrElements;
    }else{
      return 0;
    }
}

float pourcentageTranche(TRANCHE *racine, int borneSup)
{
  int totalben=totalBen(racine);
  if (totalben!=0)
{
    int totalbenTranche=totalBenTranche(racine,borneSup);
    if (totalbenTranche!=0)
    {
    return (float)totalbenTranche/totalben;
    }
    else
    {
        return 0;
    }

}
  else
  {
      return 0;
  }
}

void afficherTranche(TRANCHE *racine, int borneSup)
{
  TRANCHE *courant=racine;
  while((courant!=NULL) && (courant->borneSup!=borneSup)){
    if (borneSup<courant->borneSup)
        courant=courant->filsG;
    else if (borneSup>courant->borneSup)
        courant=courant->filsD;
  }
  if (courant==NULL) {
    printf("La tranche %d-%d n'est pas dans l'arbre.\n",borneSup-5,borneSup);
  }else
  {
    BENEVOLE* benevole=courant->liste->benevole;
    if (benevole==NULL)
    {
      printf("La tranche %d-%d est vide.\n",borneSup-5,borneSup);
    }
    else
    {
      printf("Tranche %d-%d ans:\n\n",borneSup-5,borneSup);
      printf("Nombre de personnes:%d\n",courant->liste->nbrElements);
      while(benevole!=NULL)
      {
        printf("Nom:%s\nPrenom:%s\nSexe:%c\nAnnee de naissance:%d\nCIN:%d\n\n",benevole->nom,benevole->prenom,benevole->sexe,benevole->annee,benevole->CIN);
        benevole=benevole->suivant;
      }
    }
  }
}

TRANCHE* max(TRANCHE* racine){
  //on parcourt les tranches en partant de la plus �lev�e jusqu'� en atteindre une tranche non vide
  //utilis�e dans BenDhonneur, fonction diff�rente de maxABR
  TRANCHE* pred=NULL;
  if (racine!=NULL) {
    pred=max(racine->filsD);
    if ((pred==NULL) && (racine->liste->benevole!=NULL)) {
      return racine;
    }else if(pred!=NULL){
      return pred;
    }
    pred=max(racine->filsG);
  }
  return pred;
}

LISTBENEVOLES *BenDhonneur(TRANCHE *racine){
  TRANCHE* trancheMax=max(racine);
  LISTBENEVOLES* listeHonneur=nouvelleListe();
  if (trancheMax!=NULL) {//si l'arbre contient au moins un benevole
    BENEVOLE* ben=trancheMax->liste->benevole;
    while (ben->suivant!=NULL) {//comme trancheMax!=NULL, la liste est forc�ment non vide
      ben=ben->suivant;
    }
    int annee=ben->annee;

    ben=trancheMax->liste->benevole;
    while (ben->annee!=annee) {//comme trancheMax!=NULL, la liste est forc�ment non vide
      ben=ben->suivant;
    }
    listeHonneur->benevole=ben;
    listeHonneur->nbrElements=1;
    while (ben->suivant!=NULL) {
      listeHonneur->nbrElements+=1;
      ben=ben->suivant;
    }
  }
  return listeHonneur;
}

void afficherListe(LISTBENEVOLES *liste)
{
    BENEVOLE *courant=liste->benevole;
    printf("Nombre de personnes: %d\n", liste->nbrElements);
    while(courant!=NULL)
    {
        printf("Nom:%s\nPrenom:%s\nSexe:%c\nAnnee de naissance:%d\nCIN:%d\n\n",courant->nom,courant->prenom,courant->sexe,courant->annee,courant->CIN);
        courant=courant->suivant;
    }
}

int detruireABR(TRANCHE *racine)///fonction r�cursivee
{
    if ((racine->filsD==NULL)&&(racine->filsG==NULL))///condition d'arr�t, il n'y a plus que la racine
    {
        supprimerTranche(racine, racine->borneSup);
        return 0;
    }
    if (racine->filsG!=NULL)///tant qu'il y a un fils gauche on supprime le minimum de l'ABR
    {
        TRANCHE *minimum=minABR(racine);
        int resultat;
        resultat=supprimerTranche(racine, minimum->borneSup);
        if (resultat==0)
        {
            detruireABR(racine);
        }
        else
        {
            return 1;
        }
    }
    if (racine->filsD!=NULL)///tant qu'il y a un fils droit on supprime le maximum de l'ABR
    {
        TRANCHE *maximum=maxABR(racine);
        int resultat;
        resultat=supprimerTranche(racine, maximum->borneSup);
        if (resultat==0)
        {
            detruireABR(racine);
        }
        else
        {
            return 1;
        }
    }
}

int anneeActuelle()
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    return instant.tm_year + 1900;
}
PILE *creerPile(){
	PILE *p = malloc(sizeof(PILE));
	p->tete = NULL;
	p->taille = 0;
	return p;
}

int pile_vide (PILE *p){
	if (p->taille == 0 || p->tete == NULL)
		return 1;
	else
		return 0;
}

void empiler(TRANCHE *x, PILE *p){
	struct element *new = malloc(sizeof(struct element));
	new->tranche = x;
	new->suivant = p->tete;
	p->tete = new;
	p->taille++;
}

TRANCHE *depiler(PILE *p){
	if (!pile_vide(p)){
		TRANCHE *x = p->tete->tranche;
		struct element *ptr = p->tete;
		p->tete = p->tete->suivant;
		free(ptr);
		p->taille--;
		return x;
	}
	else
		return NULL;
}

int actualiser(TRANCHE *racine)
{
    int nombre=0;
    if (racine!=NULL)
    {
        PILE *p = creerPile();
        empiler(racine, p);
        while(!pile_vide(p))
        {
            TRANCHE *t = depiler(p);
            BENEVOLE *parcours = t->liste->benevole, *pPrecedent = NULL, *pSauv = NULL;

            while(parcours!=NULL)
            {
                if (anneeActuelle()- parcours->annee > t->borneSup)
                { //on choisit de ne pas d�placer tous ceux dont l'age est sup�rieur car sinon compliquer pour trier dans la nouvelle liste
                    if (pPrecedent==NULL)
                    {
                        t->liste->benevole = parcours->suivant;
                        pSauv = parcours->suivant;
                        parcours->suivant = NULL;
                        printf("on stocke pour deplacer\n");
                    }
                    else
                    {
                        pPrecedent->suivant = parcours->suivant ;
                        pSauv = parcours->suivant;
                        parcours->suivant = NULL;
                        printf("on actualise la suite du precedent\n");
                    }
                    t->liste->nbrElements--;       //car on incr�mente le nombre de b�n�vole dans insererBen
                    if (t->liste->nbrElements==0)
                        supprimerTranche(racine, t->borneSup);
                    insererBen(racine, parcours);
                    printf("On reinsere\n");
                    //insererBen(racine, ptr);
                    parcours = pSauv;
                    nombre++;
                }
                else
                {
                    pPrecedent = parcours;
                    parcours = parcours->suivant;
                }
            }
            if (t->filsG != NULL)
                empiler(t->filsG, p);
            if (t->filsD != NULL)
                empiler(t->filsD, p);
        }
        free(p);
        return nombre;
    }
    return nombre;
}
