#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// les constantes
#define NB_LIGNES 6
#define NB_COLONNES 7
#define PION_A 'X'
#define PION_B 'O'
#define VIDE ' '
#define INCONNU ' '


// les types
typedef int Grille[NB_LIGNES][NB_COLONNES];


// prototypes des fonctions
void initGrille(Grille laGrille);
void afficher(Grille laGrille, char pion);
bool grillePleine(Grille laGrille);
void jouer(Grille laGrille, char pion, int *ligne, int *colonne);
int choisirColonne(Grille laGrille, char pion);
int chercherLigne(Grille laGrille, int col);
bool estVainqueur(Grille laGrille, int lig, int col);
void finDePartie(char vainqueur);

void jouerStrategie2(Grille laGrille, char pion, int *ligne, int *colonne);
int strategie_offensive(Grille g, char pion);
int premier_tour(Grille g);
int cherche_aligne(Grille laGrille, char pion, int nb_pion);
bool coup_davance(Grille laGrille, char pion, int colonne, int ligne);
int on_sait_jamais(Grille g);


// Programme principal. C'est le pion A qui commence a jouer
int main()
{
    Grille laGrille;
    char vainqueur = INCONNU;
    int ligne, colonne;
    initGrille(laGrille);
    afficher(laGrille, PION_B);
    while (vainqueur == INCONNU && !grillePleine(laGrille))
    {
        jouerStrategie2(laGrille, PION_B, &ligne, &colonne);
        afficher(laGrille, PION_A);
        if (estVainqueur(laGrille, ligne, colonne))
        {
            vainqueur = PION_B;
        }
        else if (!grillePleine(laGrille))
        {
            jouer(laGrille, PION_A, &ligne, &colonne);
            if (estVainqueur(laGrille, ligne, colonne))
            {
                vainqueur = PION_A;
            }
        }
    }
    finDePartie(vainqueur);
    system(EXIT_SUCCESS);
}

/*
 *           * * * * * * * * * * * * * * * * * *
 *           *                                 *
 *           *       FONCTIONS STRATÉGIES      *
 *           *                                 *
 *           * * * * * * * * * * * * * * * * * *
 */

void jouerStrategie2(Grille laGrille, char pion, int *ligne, int *colonne)
{
    *ligne = -1;
    do
    {
        *colonne = strategie_offensive(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    } while (*ligne == -1);
    laGrille[*ligne][*colonne] = pion;
}

int strategie_offensive(Grille g, char pion)
{
    /*
     * cette strategie ne defend que si l'adversaire a la possibilite de faire un puissance 4
     * sinon il essaye d'aligner le plus de pion possible (priorite au coup vers le millieu de la grille)
     * la fonction "cherche_aligne" verifie que le pion qu'il souhaite poser ne va pas aider l'adversaire a directement faire un puissance 4 (grace a l'appel d'une fonction "coup_davance")
     * le cas du premier tour est considere comme un cas particulier;
     *
     *  renvoie la colonne ou jouer le jeton
     */

    char pion_adversaire;
    // colonne a renvoyer
    int col;
    int tour1;

    // on trouve les jetons de l'adversaire
    if (pion == PION_A)
    {
        pion_adversaire = PION_B;
    }
    else
    {
        pion_adversaire = PION_A;
    }

    // cas particulier : tour 1
    tour1 = premier_tour(g);
    // teste si c'est le premier tour
    if (tour1 > -1)
    {
        return tour1;
    }
    else
    {
        // cherche si il y a une possibilité de gagner (en un coup)
        col = cherche_aligne(g, pion, 4);
        if (col > -1)
        {
            return col;
        }

        // recherche si il faut empecher l'adversaire de gagner (en un coup)
        col = cherche_aligne(g, pion_adversaire, 4);
        if (col > -1)
        {
            return col;
        }

        // l'adversaire a peu de chances de gagner --> on essaye d'aligner 3 de nos jetons
        col = cherche_aligne(g, pion, 3);
        if (col > -1)
        {
            return col;
        }

        // on essaye d'aligner deux jetons
        col = cherche_aligne(g, pion, 2);
        if (col > -1)
        {
            return col;
        }

        // si on ne peut faire aucunes des précédentes actions --> on met le jetons dans la colonne la plus au centre possible
        else
        {
            return on_sait_jamais(g);
        }
    }
}

int premier_tour(Grille grille)
{
    /*
    * cette fonction permet de savoir si il s'agit du premier tour (premier a jouer ou un seul pion pose par l'adversaire)

    * si c'est le cas, elle renvoie la colonne adaptee :
    *       colonne du milieu si premier a jouer
    *       sinon colonne colle au pion adverse cote millieu de la grille (si pion adverse au millieu alors colonne d'avant)
    *
    * sinon elle renvoie -1
    */

    // compteur de jetons dans les deux premieres lignes de la grille
    int compteur = 0;
    // colonne du jeton adverse (utile seulement si il s'agit du premier tour)
    int col_jeton;

    for (int i = NB_LIGNES - 1; i > 4; i--)
    {
        // on regarde pour chaque colonne
        for (int j = 0; j < NB_COLONNES; j++)
        {
            // s'il y a un pion on ajoute 1 au compteur
            if (grille[i][j] != VIDE)
            {
                compteur++;
                // on stocke la colonne du jeton adverse
                col_jeton = j;
            }
        }
    }
    // cas on l'on joue en premier
    if (compteur == 0)
    {
        // si vide --> retourne le milieu de la grille
        return 3;
    }
    // cas ou l'on joue en deuxieme
    else if (compteur == 1)
    {
        // test pour mettre notre pion le plus au milieu possible en restant collé à celui de l'adversaire
        if (col_jeton <= 3)
        {
            return col_jeton + 1;
        }
        else
        {
            return col_jeton - 1;
        }
    }

    // si ce n'est pas le premier tour on renvoie -1
    return -1;
}

bool coup_davance(Grille laGrille, char pion, int colonne, int ligne)
{
    /*
     * cette fonction est appelle par "cherche_ligne" et permet de prevoir si le jeton au dessus du jeton que l'on souhaite poser, va offrir un puissance 4 à l'adversaire
     *
     * la ligne et colonne en entree sont celui du pion (potentiellement) dangereux
     *
     * renvoie true si il y a un risque de puissance 4
     * sinon renvoie false
     *
     * pas necessaire de regarder la colonne car le pion en dessous est le notre
     */

    // compteur de pions alignes
    int nb_identique = 0;
    // compteur pour indice(s) de la grille
    int compteur = 1;

    // test horizontal
    // coté gauche
    while (compteur < 4 && laGrille[ligne][colonne - compteur] == pion && colonne - compteur >= 0)
    {
        nb_identique++;
        compteur++;
    }
    compteur = 1;
    // coté droit
    while (compteur < 4 && laGrille[ligne][colonne + compteur] == pion && colonne + compteur < NB_COLONNES)
    {
        nb_identique++;
        compteur++;
    }
    // si il y a 3 pion proche alors renvoie true
    if (nb_identique == 3)
    {
        return true;
    }

    // reset compteurs
    compteur = 1;
    nb_identique = 0;

    // test diagonale NO --> SE
    // coté haut
    while (compteur < 4 && laGrille[ligne - compteur][colonne - compteur] == pion && colonne - compteur >= 0 && ligne - compteur >= 0)
    {
        nb_identique++;
        compteur++;
    }
    compteur = 1;
    // coté bas
    while (compteur < 4 && laGrille[ligne + compteur][colonne + compteur] == pion && colonne + compteur < NB_COLONNES && ligne + compteur < NB_LIGNES)
    {
        nb_identique++;
        compteur++;
    }
    // si il y a 3 pion proche alors renvoie true
    if (nb_identique == 3)
    {
        return true;
    }

    // reset compteurs
    compteur = 1;
    nb_identique = 0;

    // test diagonale NE --> SO
    // coté haut
    while (compteur < 4 && laGrille[ligne - compteur][colonne + compteur] == pion && colonne + compteur < NB_COLONNES && ligne - compteur >= 0)
    {
        nb_identique++;
        compteur++;
    }
    compteur = 1;
    // coté bas
    while (compteur < 4 && laGrille[ligne + compteur][colonne - compteur] == pion && colonne - compteur >= 0 && ligne + compteur < NB_LIGNES)
    {
        nb_identique++;
        compteur++;
    }
    // si il y a 3 pion proche alors renvoie true
    if (nb_identique == 3)
    {
        return true;
    }
    // pas de futur puissance 4 trouve --> renvoie false
    return false;
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
                    if (compteur == nb_pion && est_compris && (nb_pion == 4 || !coup_davance(laGrille, pion_adversaire, colonne, ligne - 1)))
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
                    if (compteur == nb_pion && est_compris && (nb_pion == 4 || !coup_davance(laGrille, pion_adversaire, colonne, ligne - 1)))
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
                    if (compteur == nb_pion && est_compris && (nb_pion == 4 || !coup_davance(laGrille, pion_adversaire, colonne, ligne - 1)))
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
                    if (compteur == nb_pion && est_compris && (nb_pion == 4 || !coup_davance(laGrille, pion_adversaire, colonne, ligne - 1)))
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

int on_sait_jamais(Grille g)
{
    /*
     * fonction qui renvoie la colonne la plus au centre possible de la grille
     * il s'agit du dernier cas possible (si on ne peut meme pas aligner 2 pions)
     */

    // colonne a renvoyer
    int colonne;

    // boucle pour parcourir chaque colonne
    for (int boucle_colonne = 0; boucle_colonne < NB_COLONNES; boucle_colonne++)
    {
        // ce qui suit permet de commencer vers les colonnes du milieu --> priorite des colonnes : 3-2-4-1-5-0-6
        if (boucle_colonne % 2 == 0)
        {
            colonne = 3 + (boucle_colonne / 2);
        }
        else
        {
            colonne = 3 - (boucle_colonne + 1) / 2;
        }

        // si la colonne n'est pas pleine --> renvoie celle-ci
        if (chercherLigne(g, colonne) > -1)
        {
            return colonne;
        }
    }
    // cas d'erreur (ce n'est pas cense etre execute jusqu'ici si la grille n'est pas pleine)
    return -1;
}


/*
 *           * * * * * * * * * * * * * *
 *           *                         *
 *           *       FONCTIONS JEU     *
 *           *                         *
 *           * * * * * * * * * * * * * *
 */

void initGrille(Grille laGrille)
{
    int l, c;
    for (l = 0; l < NB_LIGNES; l++)
    {
        for (c = 0; c < NB_COLONNES; c++)
        {
            laGrille[l][c] = VIDE;
        }
    }
}

void afficher(Grille laGrille, char pion)
{
    int l, c;
    // system("cls");
    printf("\t");
    printf("  %c\n", pion);
    printf("\t");
    for (c = 0; c < NB_COLONNES; c++)
    {
        printf("----");
    }
    printf("-\n");
    for (l = 0; l < NB_LIGNES; l++)
    {
        printf("\t");
        for (c = 0; c < NB_COLONNES; c++)
        {
            printf("| %c ", laGrille[l][c]);
        }
        printf("|\n");
        printf("\t");
        for (c = 0; c < NB_COLONNES; c++)
        {
            printf("----");
        }
        printf("-\n");
    }
    printf("\t");
    for (c = 0; c < NB_COLONNES; c++)
    {
        printf("  %d ", c);
    }
    printf("\n\n");
}

bool grillePleine(Grille laGrille)
{
    bool pleine = true;
    int c = 0;
    while (pleine && c < NB_COLONNES)
    {
        if (laGrille[0][c] == VIDE)
        {
            pleine = false;
        }
        c++;
    }
    return pleine;
}

void jouer(Grille laGrille, char pion, int *ligne, int *colonne)
{
    *ligne = -1;
    do
    {
        *colonne = choisirColonne(laGrille, pion);
        *ligne = chercherLigne(laGrille, *colonne);
    } while (*ligne == -1);
    laGrille[*ligne][*colonne] = pion;
}

int choisirColonne(Grille laGrille, char pion)
{
    int col;

    do
    {
        printf("Numero de colonne ? ");
        scanf("%d", &col);
    } while (col < 0 || col > 6);
    return col;
}

int chercherLigne(Grille laGrille, int col)
{
    int ligne = -1;

    while (ligne < NB_LIGNES - 1 && laGrille[ligne + 1][col] == VIDE)
    {
        ligne++;
    }
    return ligne;
}

bool estVainqueur(Grille laGrille, int lig, int col)
{
    // consiste Ã regarder si une ligne de 4 pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    char lePion = laGrille[lig][col];
    int cpt, i, j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i < NB_LIGNES && laGrille[i][col] == lePion)
    {
        cpt++;
        i++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder l'horizontale, en comptant le nombre de pions Ã  l'Est et Ã  l'Ouest
    j = col;
    cpt = 0;
    // on regarde Ã  l'est
    while (j >= 0 && laGrille[lig][j] == lePion)
    {
        cpt++;
        j--;
    }
    j = col + 1;
    // on regarde Ã  l'ouest
    while (j < NB_COLONNES && laGrille[lig][j] == lePion)
    {
        cpt++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Ouest
    while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j--;
    }
    i = lig + 1;
    j = col + 1;
    // on regarde au Sud Est
    while (i < NB_LIGNES && j < NB_COLONNES && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j++;
    }
    if (cpt >= 4)
    {
        return true;
    }
    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;
    // on regarde au Nord Est
    while (j < NB_COLONNES && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j++;
    }
    i = lig + 1;
    j = col - 1;
    // on regarde au Sud Ouest
    while (i < NB_LIGNES && j >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j--;
    }
    if (cpt >= 4)
    {
        return true;
    }
    return false;
}

void finDePartie(char vainqueur)
{
    if (vainqueur != INCONNU)
    {
        printf("Joueur %c vainqueur\n", vainqueur);
    }
    else
    {
        printf("MATCH NUL");
    }
}
