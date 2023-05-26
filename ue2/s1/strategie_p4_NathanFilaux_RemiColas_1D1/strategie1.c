#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '
#define coordonner 2

// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];
typedef int tab[NB_COLONNES];
typedef int couple[1];
typedef couple mechant[7];

// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int * ligne, int * colonne);
void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne);
void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne);
int choisirColonne(Grille laGrille, char pion);
int choisirColonneStrategie0(Grille laGrille);
int contrer(int i, int j,Grille laGrille);
bool premier_tour(Grille laGrille);
int cherche_aligne(Grille laGrille, char pion, int nb_pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);



// Programme principal. C'est le pion A qui commence Ã  jouer
int main()
{
    Grille laGrille;
    char vainqueur=INCONNU;
    int ligne, colonne;
    initGrille(laGrille);
    afficher(laGrille, PION_A);
    while (vainqueur==INCONNU && !grillePleine(laGrille)){
        faireJouerB(laGrille,PION_B, &ligne, &colonne );
        
        afficher(laGrille, PION_B);
        if (estVainqueur(laGrille, ligne, colonne) ){
            vainqueur = PION_A;
        } else if (!grillePleine(laGrille)){
            faireJouerA(laGrille,PION_A,&ligne,&colonne);
            afficher(laGrille, PION_A);
            if (estVainqueur(laGrille, ligne, colonne) ){
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
    system(EXIT_SUCCESS);
}


void initGrille(Grille laGrille){
    int l, c;
    for (l=0 ; l<NB_LIGNES ; l++){
        for (c=0 ; c<NB_COLONNES ; c++){
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion){
    int l, c;
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
        printf("----");
    }
    printf("-\n");
    for (l=0 ; l<NB_LIGNES ; l++){
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c=0; c<NB_COLONNES ; c++){
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c=0; c<NB_COLONNES ; c++){
            printf("  %d ",c);
    }
    printf("\n\n");

}

bool grillePleine(Grille laGrille){
    bool pleine = true;
    int c = 0;
    while (pleine && c<NB_COLONNES){
        if (laGrille[0][c] == VIDE){
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void jouer(Grille laGrille, char pion, int * ligne, int * colonne ){
   *ligne = -1;
    do {
        *colonne = choisirColonne(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

void faireJouerA(Grille laGrille, char pion, int * ligne, int * colonne ){
   *ligne = -1;
    do {
        *colonne = choisirColonneStrategie0(laGrille);
        
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

void faireJouerB(Grille laGrille, char pion, int * ligne, int * colonne ){
   *ligne = -1;
    do {
        *colonne = choisirColonne(laGrille,pion);
        *ligne = chercherLigne(laGrille, *colonne);
    }while (*ligne==-1);
    laGrille[*ligne][*colonne] = pion;
}

int choisirColonne(Grille laGrille, char pion){
    int col;

    do{
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col<0 ||col>6);
    return col;
}
bool premier_tour(Grille laGrille){
    //  regarde si il y a deja eu plus de 2 jeton poser pour voir si oui où non c'est le premier tour
    bool tour1;
    int compteur;
    tour1=true;
    int i;
    compteur=0;
    i=0;
    while(i<NB_COLONNES && tour1==true){
        if(laGrille[5][i]!=VIDE || laGrille[4][i] !=VIDE){
            compteur++;                                     // on regarde la 2eme et 3 eme ligne de chaque colonne
            if(compteur>=2){    
            tour1=false;
            }
        }
        i++;
        
    }
    return tour1;
}


int choisirColonneStrategie0(Grille laGrille){
    int colonne;
    int i;
    int j;
    tab tablo;
    FILE* fic;
    
    bool debut;
    debut = premier_tour( laGrille);  // on regarde si c'est le premier tour

   if (debut==true){
            fic = fopen("fichier.dat","wb");
            for(i=0;i<NB_COLONNES;i++){
                tablo[i]=5;
            }                                   // si c'est le premier tour on initialise le tableau et le fichier à 5 comme profondeur de colonne
            fwrite(tablo,sizeof(tab),1,fic);
            fclose(fic);
            colonne = 3;                        // si c'est le premier on joue au centre
   }
   else{
       fic = fopen("fichier.dat","rb");
       fread(tablo,sizeof(tab),1,fic);
            i=0;
            while(i<NB_COLONNES && tablo[i]==(j=chercherLigne(laGrille,i))){        //on cherche ou il y un une profondeur différentes pour trouver le pion ennemie
                i++;    
            }
            fclose(fic);
            tablo[i]=tablo[i]-1 ;               // on décrémente la colonne ou l'adversaire a jouer
            colonne = contrer(j+1,i,laGrille);
   }

    
    tablo[colonne]=tablo[colonne]-1 ;
    fic = fopen("fichier.dat","wb");   // on décrémente la colonne où on a jouer
    fwrite(tablo,sizeof(tab),1,fic);
    fclose(fic);
    
    
    return colonne;
}
int contrer(int j,int i,Grille laGrille){
    int res;
    
    //phase offensive
    //diag haut

    if(laGrille[j+1]  [i-1] == PION_B && laGrille[j]  [i+1] != VIDE && laGrille[j+1]  [i+1] == VIDE){
        res =i+1;
    }
    else if(laGrille[j+1]  [i+1] == PION_B && laGrille[j]  [i-1] != VIDE &&  laGrille[j+1]  [i-1] == VIDE){
        res =i-1;
    }
    
    else if(laGrille[j+1]  [i+1] == PION_B && laGrille[j+3]  [i+2] != VIDE && laGrille[j+2]  [i+2] == VIDE){
        res =i+2;
    }
    else if(laGrille[j+1]  [i-1] == PION_B && laGrille[j+3]  [i-2] != VIDE && laGrille[j+2]  [i-2] == VIDE){
        res =i-2;
    }
    
    // diagonal bas
    
    else if(laGrille[j-1]  [i-1] == PION_B && laGrille[j-1]  [i-2] != VIDE && laGrille[j-2]  [i-2] == VIDE){
          res =i-2;
    }
    else if(laGrille[j-1]  [i+1] == PION_B && laGrille[j-1]  [i+2] != VIDE && laGrille[j-2]  [i+2] == VIDE){
         res =i+2;
    }
    else if(laGrille[j-1]  [i-1] == PION_B && laGrille[j]  [i+1] != VIDE && laGrille[j+1]  [i+1] == VIDE){
          res =i+1;
    }
    else if(laGrille[j-1]  [i+1] == PION_B && laGrille[j]  [i-1] != VIDE && laGrille[j+1]  [i-1] == VIDE){
         res =i-1;
    }
    
    
    //cote
    
    else if  (laGrille[j]  [i-1] == PION_B && laGrille[j+1]  [i+1] != VIDE && laGrille[j]  [i+1] == VIDE){
        res =i+1;
    }
    else if (laGrille[j]  [i+1] == PION_B && laGrille[j+1]  [i-1] != VIDE && laGrille[j]  [i-1] == VIDE){
        res =i-1;
    }
    else if (laGrille[j]  [i+1] == PION_B && laGrille[j+1]  [i+2] != VIDE && laGrille[j]  [i+2] == VIDE){
        res =i+2;
    }
    else if (laGrille[j]  [i-1] == PION_B && laGrille[j+1]  [i-2] != VIDE && laGrille[j]  [i-2] == VIDE){
        res =i-2;
    }
    
    
    
    //haut
    else if (laGrille[j+1][i]==PION_B && laGrille[j+2][i] == PION_B && laGrille[j-1][i] == VIDE){ 
        res=i;
    }
    // phase offensive
    
    else{
        res=cherche_aligne(laGrille,PION_A,2);
    }
    return res;
}


    

int chercherLigne(Grille laGrille, int col){
    int ligne = -1;

    while (ligne<NB_LIGNES-1 && laGrille[ligne+1][col]==VIDE){
        ligne++;
    }
    return ligne;
}

int cherche_aligne(Grille laGrille, char pion, int nb_pion)
{
    /*
     * cette fonction cherche une colonne a renvoyer pour creer un alignement de "nb_pion"
     * renvoie -1 si aucune possibilite
     *
     * regarde dans l'odre suivant les possibilites :    1) indice de ligne la plus basse
     *                                                   2) indice de colonne plus au millieu (puis vers l'exterieur)
     *                                                   3) colonne
     *                                                   4) diagonale NO --> SE
     *                                                   5) diagonale SO --> NE
     *                                                   6) ligne
     *
     * la fonction appelle la fonction "coup_davance" lorsque qu'une colonne correspond au attente pour verifier si ça n'offre pas une puissance 4 a l'adversaire
     *   /!\ exeption si possibilite de gagner directement (4 jetons alignes pour nous)
     */

    int compteur;
    int colonne;
    /*
     * sert a savoir si le pion imaginaire avec lequel on test les alignement est bien compris dans cet alignement de pions
     * pour les cas ou il y par exemple 3 jetons sur une ligne (independants du pion imaginaire) et que l'on cherche à aligner 3 pions
     */
    int est_compris;
    char pion_adversaire;

    // on trouve les jetons de l'adversaire
    if (pion == PION_A)
    {
        pion_adversaire = PION_B;
    }
    else
    {
        pion_adversaire = PION_A;
    }

    // à l'envers pour jouer vers le bas de la grille en priorité
    for (int ligne = NB_LIGNES - 1; ligne >= 0; ligne--)
    {
        for (int boucle_colonne = 0; boucle_colonne < NB_COLONNES; boucle_colonne++)
        {
            // ce qui suit permet de commencer vers les colonnes du milieu --> ordre des colonnes : 3-2-4-1-5-0-6
            if (boucle_colonne % 2 == 0)
            {
                colonne = 3 + (boucle_colonne / 2);
            }
            else
            {
                colonne = 3 - (boucle_colonne + 1) / 2;
            }

            // on regarde si le pion "imaginaire" peut être placé sans tomber plus bas et qu'il n'y a pas de pions deja présent
            if (laGrille[ligne][colonne] == VIDE && (laGrille[ligne + 1][colonne] != VIDE || ligne == NB_LIGNES - 1))
            {
                // test d'une colonne
                compteur = 0;
                est_compris = 0;
                for (int test_i_lig = 0; test_i_lig < NB_LIGNES; test_i_lig++)
                {
                    if ((laGrille[test_i_lig][colonne] == pion) || (test_i_lig == ligne))
                    {
                        compteur++;
                        // si le pion "imaginaire" fait partie d'un alignement
                        if (test_i_lig == ligne)
                        {
                            est_compris = 1;
                        }
                    }
                    else
                    {
                        compteur = 0;
                        est_compris = 0;
                    }
                    // condition avec appel de la fonction "coup_davance"
                    if (compteur == nb_pion && est_compris)
                    {
                        return colonne;
                    }
                }
                // reset compteurs
                compteur = 0;
                est_compris = 0;

                // test d'une diagonale NO --> SE
                int test_i_col = colonne;
                int test_i_lig = ligne;

                // on cherche le debut de la diagonale (le plus en haut a gauche)
                while (test_i_col > 0 && test_i_lig > 0)
                {
                    test_i_col--;
                    test_i_lig--;
                }

                while (test_i_col < NB_COLONNES && test_i_lig < NB_LIGNES)
                {
                    if (laGrille[test_i_lig][test_i_col] == pion || (test_i_col == colonne && test_i_lig == ligne))
                    {
                        compteur++;
                        // si le pion "imaginaire" fait partie d'un alignement
                        if (test_i_col == colonne && test_i_lig == ligne)
                        {
                            est_compris = 1;
                        }
                    }
                    else
                    {
                        compteur = 0;
                        est_compris = 0;
                    }
                    // condition avec appel de la fonction "coup_davance"
                    if (compteur == nb_pion && est_compris)
                    {
                        return colonne;
                    }
                    // incrementation des indices
                    test_i_lig++;
                    test_i_col++;
                }
                // reset compteurs
                compteur = 0;
                est_compris = 0;

                // test diagonale SO --> NE
                test_i_col = colonne;
                test_i_lig = ligne;

                // on cherche le debut de la diagonale (le plus en bas a gauche)
                while (test_i_col > 0 && test_i_lig < 5)
                {
                    test_i_col--;
                    test_i_lig++;
                }

                while (test_i_col < NB_COLONNES && test_i_lig >= 0)
                {
                    if (laGrille[test_i_lig][test_i_col] == pion || (test_i_col == colonne && test_i_lig == ligne))
                    {
                        compteur++;
                        // si le pion "imaginaire" fait partie d'un alignement
                        if (test_i_col == colonne && test_i_lig == ligne)
                        {
                            est_compris = 1;
                        }
                    }
                    else
                    {
                        compteur = 0;
                        est_compris = 0;
                    }
                    // condition avec appel de la fonction "coup_davance"
                    if (compteur == nb_pion && est_compris)
                    {
                        return colonne;
                    }
                    // incrementation des indices
                    test_i_lig--;
                    test_i_col++;
                }
                // reset des compteurs
                compteur = 0;
                est_compris = 0;

                // test de la ligne
                for (int test_i_col = 0; test_i_col < NB_COLONNES; test_i_col++)
                {
                    if (laGrille[ligne][test_i_col] == pion || test_i_col == colonne)
                    {
                        compteur++;
                        // si le pion "imaginaire" fait partie d'un alignement
                        if (test_i_col == colonne)
                        {
                            est_compris = 1;
                        }
                    }
                    else
                    {
                        compteur = 0;
                        est_compris = 0;
                    }
                    // condition avec appel de la fonction "coup_davance"
                    if (compteur == nb_pion && est_compris)
                    {
                        return colonne;
                    }
                }
            }
        }
    }
    // aucun cas trouver --> renvoie -1
    return -1;
}

bool estVainqueur(Grille laGrille, int lig, int col){
    // consiste Ã  regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt,i,j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i<NB_LIGNES && laGrille[i][col]==lePion){
        cpt++;
        i++;
    }
    if (cpt>=4){
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j>=0 && laGrille[lig][j]==lePion){
        cpt++;
        j--;
    }
    j = col+1;
    // on regarde Ã  l'ouest
    while (j<NB_COLONNES && laGrille[lig][j]==lePion){
        cpt++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j>=0 && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j--;
    }
    i = lig+1;
    j = col+1;
    // on regarde au Sud Est
    while (i<NB_LIGNES && j<NB_COLONNES && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j++;
    }
    if (cpt>=4 ){
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j<NB_COLONNES && i>=0 && laGrille[i][j]==lePion){
        cpt++;
        i--;
        j++;
    }
    i = lig+1;
    j = col-1;
    // on regarde au Sud Ouest
    while (i<NB_LIGNES && j>=0 && laGrille[i][j]==lePion){
        cpt++;
        i++;
        j--;
    }
    if (cpt>=4 ){
        return true;
    }
    return false;
}

void finDePartie(char vainqueur){
    if (vainqueur != INCONNU){
        printf("Joueur %c vainqueur\n", vainqueur);
    } else {
        printf("MATCH NUL");
    }
}



