
#include"tp4.h"
//#define date 2014
int main()
{
    int choix=0;
    TRANCHE *racine=NULL;
    while (choix!=13)
    {
        printf("MENU\n");
        printf("-------------------------------\n");
        printf("1. Initialiser un arbre\n");
        printf("2. Ajouter une tranche\n");
        printf("3. Ajouter un benevole\n");
        printf("4. Afficher les tranches\n");
        printf("5. Afficher les benevoles d'une tranche\n");
        printf("6. Supprimer un benevole\n");
        printf("7. Supprimer une tranche\n");
        printf("8. Afficher les benevoles d'honneur\n");
        printf("9. Afficher le nb total de benevoles\n");
        printf("10. Actualiser l'ABR\n");
        printf("11. Afficher le pourcentage d'une tranche d'age\n");
        printf("12. Detruire l'arbre\n");
        printf("13. Quitter\n");
        printf("-------------------------------\n");
        scanf("%d", &choix);

        if (choix==1)
        {
            int bsup;
            printf("Entrez la borne superieure de votre racine:\n");
            scanf("%d", &bsup);
            racine=nouvelleTranche(bsup);
            printf("voici votre racine:\n");
            printf("%d\n", racine->borneSup);
            printf("-------------------------------\n");
        }
        else if (choix == 2)
        {
            if(racine!=NULL){
            int bsup;
            printf("Entrez la borne superieure de votre tranche:\n");
            scanf("%d", &bsup);
            TRANCHE *nouvelle=ajoutTranche(racine, bsup);
            printf("\n");
            afficherArbre(racine);
            printf("-------------------------------\n");
            }
            else
            {
                printf("Erreur, il faut initialiser l'arbre avant.\n");
            }
        }
        else if (choix == 3)
        {
            if (racine!=NULL){
            char nom[20], prenom[20];
            char sexe;
            int CIN, annee;
            printf("Entrez le nom du benevole:\n");
            scanf("%s", nom);
            printf("Entrez le prenom du benevole:\n");
            scanf("%s", prenom);
            printf("\nEntrez le sexe du benevole:\n");
            scanf(" %c", &sexe);
            printf("Entrez le CIN du benevole:\n");
            scanf("%d", &CIN);
            printf("Entrez l annee de naissance du benevole:\n");
            scanf("%d", &annee);
            BENEVOLE *nouveau=nouveauBen(nom, prenom, CIN, sexe, annee);
            BENEVOLE *ptr=insererBen(racine, nouveau);
            if(ptr!=NULL)
            {
                printf("Ajout reussi\n");
            }
            else
            {
                printf("Echec de l'ajout\n");
            }
        }
            printf("-------------------------------\n");
        }
        else if (choix == 4)
        {
            if (racine!=NULL) {
              printf("\n Voici les tranches d'age de votre ABR\n");
              afficherArbre(racine);
            }else{
              printf("L'arbre est vide\n");
            }
            printf("-------------------------------\n");
        }
        else if (choix == 5)
        {
            int bsup;
            printf("Quelle tranche voulez vous afficher?\n");
            scanf("%d", &bsup);
            afficherTranche(racine, bsup);
            printf("-------------------------------\n");
        }
        else if (choix == 6)
        {
            int CIN, annee, resultat;
            printf("Quelle est l'annee de naissance du benevole?\n");
            scanf("%d", &annee);
            printf("Son CIN?\n");
            scanf("%d", &CIN);
            resultat=supprimerBen(racine, CIN, annee);
            if (resultat==0)
            {
                printf("Suppression reussie\n");
            }
            else
            {
                printf("Echec de la suppression\n");
            }
            printf("-------------------------------\n");
        }
        else if (choix == 7)
        {
            int bsup, result;
            printf("\nQuelle tranche souhaitez-vous supprimer?\n");
            scanf("%d",&bsup);
            //TRANCHE **ptrRacine=racine;
            result=supprimerTranche(racine, bsup);
            if (result==2) {
              printf("La racine a ete supprimee et l'arbre est vide.\n");
              racine=NULL;
            }
            if (result==1)
            {
                printf("Erreur, la tranche n'a pas ete supprimee\n");
            }
            if (result == 0)
            {
                if(racine == NULL){
                        printf("Il n'y a plus de racine\n");
                }
                else{
                printf("La racine est:%d\n", racine->borneSup);
                printf("La tranche a ete correctement supprimee\n");
                }
            }

            printf("-------------------------------\n");
        }
        else if (choix == 8)
        {
            LISTBENEVOLES *listeBenHonneur=BenDhonneur(racine);
            if (listeBenHonneur->benevole!=NULL){
            afficherListe(listeBenHonneur);
            }
            else
            {
                printf("Erreur il n'y a pas de benevole dans cet arbre\n");
            }
            printf("-------------------------------\n");
        }
        else if (choix == 9)
        {
            int nbTotalBen;
            nbTotalBen=totalBen(racine);
            printf("Le nombre total de benevole de l'arbre est: %d\n", nbTotalBen);
            printf("-------------------------------\n");
        }
        else if (choix == 10)
        {
            int nbBenDepl=actualiser(racine);
            printf("Le nb de benevole deplace est: %d\n", nbBenDepl);
            printf("-------------------------------\n");
        }
        else if (choix == 11)
        {
            int bsup;
            float pourcent;
            printf("De quelle borne voulez vous connaitre le pourcentage ?\n");
            scanf("%d", &bsup);
            pourcent=pourcentageTranche(racine, bsup);
            printf("Le pourcentage de benevole dans cette tranche est: %f\n", pourcent);
            printf("-------------------------------\n");
        }
        else if (choix == 12)
        {
            if (racine!=NULL){
              int resultat=detruireABR(racine);
              if (resultat==0)
              {
                  printf("La destruction de l'ABR a reussie\n");
                  racine=NULL;
              }
              else
              {
                  printf("Erreur lors de la destruction de l'ABR\n");
              }
            }
            printf("-------------------------------\n");
        }
    }
    return 0;
}
