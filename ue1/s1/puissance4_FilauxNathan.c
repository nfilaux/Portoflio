#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //pour clear la console
#include <time.h>   //pour aléatoire


#define NBLIG 6     //nombre de ligne de la grille de jeu
#define NBCOL 7     //nombre de colonne de la grille de jeu


const char PION_A = 'x';
const char GRAND_PION_A = '#';
const char PION_B = 'o';
const char GRAND_PION_B = '@';
const char VIDE = ' ';
const char PROCHAIN_JETON = '*';    //pion qui répresente un futur coup


typedef char Grille[NBLIG][NBCOL];


void clearScreen();     //permet de nettoyer la console
void demande_nom(char, char []);
int aleatoire();        //renvoie un nombre aléatoire (0 ou 1)
void initGrille(Grille);    //remplit la grille de jeu par des espaces
void afficher(Grille);
int grillePleine(Grille);
void jouer(Grille, char, int*, int*, char [], char []);     //place jeton grâce à choisirColonne et touverLigne
int choisirColonne(Grille, char, char [], char []);     //demande une colonne et la renvoie
int trouverLigne(Grille, int);
int estVainqueur(Grille, int, int, char);
void transforme_jeton(int [4][2], Grille, char);    //transforme les 4 jetons alignés pour mieux voir la serie (est appelé depuis la fonction estVainqueur)
int finDePartie(char, char [], char [], Grille);
int confirmeColonne(Grille, int);       //renvoie 0 si le pion ne doit pas être placé ou 1 sinon après confirmation du joueur


/*
*                   * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                   *                 PROGRAMME PRINCIPAL                 *
*                   * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/


int main(){
    char vainqueur, joueur_actuel;
    char nomA[30], nomB[30];
    int ligne, colonne, tour_joueur;
    int continue_jouer = 1;
    Grille g;

    srand(time(NULL));

    while(continue_jouer){
        initGrille(g);
        tour_joueur = aleatoire();      // peut être égal à 0 ou 1
        vainqueur = VIDE;


        clearScreen();
        printf("        * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
        printf("        *                 JEU DU PUISSANCE 4                *\n");
        printf("        * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");

        demande_nom(PION_A, nomA);
        printf("\n");
        demande_nom(PION_B, nomB);
        while (vainqueur==VIDE && !grillePleine(g)){
            if(tour_joueur%2 == 0){     //permet de faire jouer le premier joueur choisis aléatoirement puis ensuite chacun leur tour
                joueur_actuel = PION_A;
            }
            else{
                joueur_actuel = PION_B;
            }

            jouer(g, joueur_actuel, &ligne, &colonne, nomA, nomB);

            if (estVainqueur(g, ligne, colonne, joueur_actuel)){
                vainqueur = joueur_actuel;
            }
            tour_joueur++;
        }
        continue_jouer = finDePartie(vainqueur, nomA, nomB, g);     //possiblité de relancer une partie
    }
}


/*
*                   * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                   *                 PROCEDURE/FONCTIONS                 *
*                   * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/


void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}


void demande_nom(char pion, char nom[]){
    if (pion == PION_A){
        printf("Quel est le nom du joueur 1 : ");
        scanf("%s", nom);
        printf("Vos jetons sont des \"%c\"\n", PION_A);
    }
    else if(pion == PION_B){
        printf("Quel est le nom du joueur 2 : ");
        scanf("%s", nom);
        printf("Vos jetons sont des \"%c\"\n", PION_B);
        sleep(2);
    }
}


int aleatoire(){
    return rand()%2;    //valeur peut être égal à 0 ou 1
}


void initGrille(Grille g){
    int i,j;
    for (i=0; i<NBLIG; i++){
        for (j=0; j<NBCOL; j++){
            g[i][j] = VIDE;
        }
    }
}


void afficher(Grille g){
    int i, j;

    printf("  1   2   3   4   5   6   7\n");
    printf("+―――+―――+―――+―――+―――+―――+―――+\n");
    //printf("+---+---+---+---+---+---+---+\n");         //pour affichage sur windows

    for (i=0; i<NBLIG; i++){
        for (j=0; j<NBCOL; j++){
            printf("| %c ", g[i][j]);
        }
        printf("|\n+―――+―――+―――+―――+―――+―――+―――+\n");
        //printf("|\n+---+---+---+---+---+---+---+\n");     //pour affichage sur windows
    }
    printf("\n");
}


int grillePleine(Grille g){
    int res = 1;
    int i;
    for (i=0; i<NBCOL; i++){
        if (g[0][i] == VIDE){
            res = 0;
        }
    }
    return res;
}


void jouer(Grille g, char pion, int *ligne, int *colonne, char nomA[], char nomB[]){
    *colonne = choisirColonne(g, pion, nomA, nomB);     //donne colonne choisie
    *ligne = trouverLigne(g, *colonne);                 //donne la ligne ou placer le jeton
    g[*ligne][*colonne] = pion;                         //place le jeton
}


int choisirColonne(Grille g, char pion, char nomA[], char nomB[]){
    int colonne;
    int confirme;
    do{
        clearScreen();
        if(pion == PION_A){
                printf("       ---  C'est au tour de %s (joueur 1) de jouer  ---\n\n", nomA);
            }
            else{
                printf("       ---  C'est au tour de %s (joueur 2) de jouer  ---\n\n", nomB);
            }
        printf("Voici la grille de jeu :\n\n");
        afficher(g);

        do{
            printf("Choisissez une colonne ou placer le jeton (entre 1 et 7) : ");
            scanf("%d", &colonne);
        }while (colonne > NBCOL || colonne < 1);
        colonne--;      //pour pouvoir l'utiliser comme un indice du tableau

        //preparation de l'affichage avant l'appel de confirmeColonne
        clearScreen();      
        if(pion == PION_A){
                printf("       ---  C'est au tour de %s (joueur 1) de jouer  ---\n\n", nomA);
            }
            else{
                printf("       ---  C'est au tour de %s (joueur 2) de jouer  ---\n\n", nomB);
            }

        confirme = confirmeColonne(g, colonne);
    }while(!confirme);
    return colonne;
}


int confirmeColonne(Grille g, int colonne){
    int ligne;
    char confirme, retour_chariot;
    int reponse = 0;

    ligne = trouverLigne(g, colonne);
    if (ligne == -1){
        printf("Colonne pleine !\n");
    }
    else{
        g[ligne][colonne] = PROCHAIN_JETON;
        printf("Voici la grille de jeu :\n\n");
        afficher(g);
        scanf("%c", &retour_chariot);
        printf("Voulez-vous jouer a cette endroit (O/N) : ");
        scanf("%c", &confirme);
        scanf("%c", &retour_chariot);
        g[ligne][colonne] = VIDE;
    }
    if (confirme == 'O' || confirme == 'o'){
        reponse = 1;
    }
    return reponse;
}


int trouverLigne(Grille g, int colonne){
    int boucle = NBLIG-1;
    int res = -1;
    while (boucle >= 0 && res == -1){
        if (g[boucle][colonne] == VIDE){
            res = boucle;
        }
        boucle--;
    }
    return res;
}


int estVainqueur(Grille g, int ligne_jeton, int colonne_jeton, char pion){
    int ligne, colonne, trouve;
    int direction = 1;  /*1 si on avance, -1 si on recule, 0 si on s'arrete*/
    int res = 0;
    int t_jetonAlignes[4][2];
    
    trouve = 0;
    ligne = ligne_jeton;
    colonne = colonne_jeton+1;

    t_jetonAlignes[trouve][0] = ligne_jeton;        //permet de stocker les coordonnées (ligne) du jeton trouvé pour ensuite changer son caractère en cas victoire
    t_jetonAlignes[trouve][1] = colonne_jeton;      //pareil mais pour la colonne

    while(direction==1 && trouve<3){    //test d'une ligne (commence vers la droite)
        if((colonne < NBCOL) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
            trouve++;

            t_jetonAlignes[trouve][0] = ligne;
            t_jetonAlignes[trouve][1] = colonne;

            colonne++;
        }
        else{
            direction = -1;
        }
    }

    colonne = colonne_jeton-1;

    while (direction && trouve<3){      //suite du test d'une ligne (vers la gauche)
        if((colonne >= 0) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
            trouve++;

            t_jetonAlignes[trouve][0] = ligne;
            t_jetonAlignes[trouve][1] = colonne;

            colonne--;
        }
        else{
            direction = 0;
        }
    }


    if(trouve >= 3){    //test pour verifier si il y a un gagnant
            res = 1;
            transforme_jeton(t_jetonAlignes, g, pion);
    }

    direction = 1;
    ligne = ligne_jeton+1;
    colonne = colonne_jeton;
    trouve = 0;
    

    if (!res){   //test d'une colonne
        while((direction == 1) && (trouve < 3)){    //vers le bas
            if((ligne < NBLIG) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne++;
            }
            else{
                direction = -1;
            }
        }

        ligne = ligne_jeton-1;

        while (direction && trouve<3){      //vers le haut
            if((ligne >= 0) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne--;
            }
            else{
                direction = 0;
            }
        }
    }

    
    if(trouve >= 3){    //test pour verifier si il y a un gagnant
            res = 1;
            transforme_jeton(t_jetonAlignes, g, pion);
    }

    direction = 1;
    ligne = ligne_jeton+1;
    colonne = colonne_jeton+1;
    trouve = 0;


    if(!res){    /*test d'une diagonale haut gauche vers bas droite*/
        while(direction==1 && trouve<3){    //vers sud est
            if((ligne < NBLIG) && (colonne < NBCOL) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne++;
                colonne++;
            }
            else{
                direction = -1;
            }
        }

        ligne = ligne_jeton-1;
        colonne = colonne_jeton-1;

        while (direction && trouve<3){      //vers nord ouest
            if((ligne >= 0) && (colonne >= 0) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne--;
                colonne--;
            }
            else{
                direction = 0;
            }
        }
    }

    if(trouve >= 3){    //test pour verifier si il y a un gagnant
            res = 1;
            transforme_jeton(t_jetonAlignes, g, pion);
    }

    direction = 1;
    trouve = 0;
    ligne = ligne_jeton+1;
    colonne = colonne_jeton-1;

    if(!res){     /*test d'une diagonale haut droite vers bas gauche*/
        while(direction==1 && trouve<3){    //vers sud ouest
            if((ligne < NBLIG) && (colonne >= 0) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne++;
                colonne--;
            }
            else{
                direction = -1;
            }
        }

        ligne = ligne_jeton-1;
        colonne = colonne_jeton+1;

        while (direction && trouve<3){      //vers nord est
            if((ligne >= 0) && (colonne < NBCOL) && (g[ligne][colonne] == g[ligne_jeton][colonne_jeton])){
                trouve++;

                t_jetonAlignes[trouve][0] = ligne;
                t_jetonAlignes[trouve][1] = colonne;

                ligne--;
                colonne++;
            }
            else{
                direction = 0;
            }
        }
    }

    if(trouve >= 3){    //test pour verifier si il y a un gagnant
        res = 1;
        transforme_jeton(t_jetonAlignes, g, pion);
    }
    return res;
}


void transforme_jeton(int tableau_pions_trouves[4][2], Grille g, char pion){
    char pion_switch;
    int boucle_switch;

    if(pion == PION_A){     //on regarde quel jeton a gagné
            pion_switch = GRAND_PION_A;
        }
        else{
            pion_switch = GRAND_PION_B;
        }

        for(boucle_switch=0; boucle_switch<4; boucle_switch++){
            g[tableau_pions_trouves[boucle_switch][0]][tableau_pions_trouves[boucle_switch][1]] = pion_switch;      //change les jetons alignés (trouvé dans la fonction estVainqueur)
        }
}


int finDePartie(char pion, char nom1[], char nom2[], Grille g){
    int continuer = 0;
    char reponse;
    clearScreen();
    printf("    ---     LA PARTIE EST FINIE     ---\n\n");
    printf("Voici la grille de fin :\n\n");
    afficher(g);
    if (pion == PION_A){
        printf("Le gagnant est %s, le joueur 1 !\n", nom1);
    }
    else if(pion == PION_B){
        printf("Le gagnant est %s, le joueur 2 !\n", nom2);
    }
    else{
        printf("Match nul !\n");
    }
    printf("\nVoulez-vous refaire une partie (O/N) : ");    //possiblité de rejouer une partie
    scanf("%c", &reponse);
    if(reponse == 'O' || reponse =='o'){
        continuer = 1;
    }
    return continuer;
}
