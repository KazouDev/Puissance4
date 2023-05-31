/*!
 * \mainpage Puissance4
 * \brief Jeu du Puissance 4.
 *
 * \author LEVACHER Ethan
 * \version 0.1
 * \date 28 octobre 2022
 *
 * Jeu où s'affronte 2 joueurs, à tour de rôle, en faisant tomber leurs pions dans
 * une des colonnes de la grille, de dimension 6x7. Le vainqueur est le premier à aligner
 * 4 pions.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * \def NB_LIGNE
 * \brief constante, entière, du nombre de ligne d'une grille.
 *
 * Nombre de ligne de la grille de jeux.
 */
#define NB_LIGNE 6

/**
 * \def NB_COL
 * \brief constante, entière, du nombre de colle d'une grille.
 *
 * Nombre de colonne de la grille de jeux.
 */
#define NB_COL 7

/**
 * \def PION_A
 * \brief constante du caractère du pion A.
 */
#define PION_A 'X'

/**
 * \def PION_B
 * \brief constante du caractère du pion B.
 */
#define PION_B 'O'

/**
 * \def VIDE
 * \brief constante du caractère représentant une case vide.
 */
#define VIDE ' '

/**
 * \def INCONNU
 * \brief constante du caractère inconnu.
 */
#define INCONNU ' '

/**
 * \def COLONNE_DEBUT
 * \brief constante, entière, de la colonne avant les déplacements du joueurs.
 *
 * Utile notamment lors de de la séléction de la colonne par le choix afin de placer le pions au centre des colonnes.
 */
#define COLONNE_DEBUT NB_LIGNE/2

/**
 * \def VICTOIRE
 * \brief constante, entière, du nombre de pions devant être aligné pour une victoire
 *
 * Utile lors de la fonction estVainqueur, afin de verifier si un pion est gagnant ou non.
 */
#define VICTOIRE 4

/**
 * \def GAUCHE
 * \brief constante du caractère à saisir pour se déplacer à gauche.
 */
#define GAUCHE 'q'

/**
 * \def DROITE
 * \brief constante du caractère à saisir pour se déplacer à droite.
 */
#define DROITE 'd'

/**
 * \def DEBUTPARTIE
 * \brief constante du caractère à saisir pour démarrer la partie.
 */
#define DEBUTPARTIE 'O'

/**
 * \typedef t_grille
 * \brief type grille de NB_LIGNE x NB_COL
 *
 * Type servant à la grille principale de jeux.
 */
typedef char t_grille[NB_LIGNE][NB_COL];

/**
 * \fn debut_partie()
 * \brief Affiche les régles et attend la saisie du caractère DEBUTPARTIE, avant de continuer.
 *
 * En cas de mauvaise saisie, la procédure ré-affiche les régles et redemande la saisie du caractère DEBUTPARTIE.
 */
void debut_partie();

/**
 * \fn rest_scanf()
 * \brief Remet à zero la file d'attente du scanf
 *
 * Le raisonnement utiliser pour cette fonction à était trouvé sur internet.
 * Cette fonction permet de remettre à zéro la file d'attente du scanf afin d'éviter les erreurs en cas de saisie de plusieurs caractère à la suite.
 */
void rest_scanf();

/**
 * \fn void initGrille(t_grille g)
 * \brief Procédure initialisant la grille passé en paramètre.
 * \param g : la grille de type t_grille, servant de grille de jeux.
 *
 * Consiste à remplir la grille de caractère vide au début du programme.
 */
void initGrille(t_grille g);

/**
 * \fn void afficher(t_grille g, char pion, int colonne)
 * \brief Procédure affichant la grille ainsi que les pions contenu dans celle-ci.
 * \param g la grille de type y_grille, servant de grille de jeux.
 * \param pion charactère représentant le prochain pion à jouer.
 * \param colonne int du numéro de colonne ou le prochaine pion jouera.
 *
 * Affichage de la grille, ainsi que des pions contenu dans la grille, et également le prochaine pion qui jouera ainsi que les numéros des colonnes.
 */
void afficher(t_grille g, char pion, int colonne);

/**
 * \fn bool grillePleine(t_grille)
 * \brief Fonction retournant si la grille est pleine ou non.
 * \param g la grille de type t_grille, servant de grille de jeux.
 * \return un booléen, true si la grille est pleine, false sinon.
 *
 */
bool grillePleine(t_grille g);

/**
 * \fn jouer(t_grille g, char pion, int *ligne, int *colonne)
 * \brief Fonction permettant le déroulement du jeux.
 * \param g la grille de type t_grille, servant de grille de jeux.
 * \param pion paramètre d'entrée qui représentent le caractère du pion qui joue.
 * \param *ligne paramètre de sortie qui représentent l'entier du numéro de ligne où le joueur joue.
 * \param *colonne paramètre de sortie qui représentent l'entier du numéro de colonne où le joueur joue.
 *
 * Verification uniquement de la première ligne, étant donné que les pions tombent au plus bas, afin de gagner en optimisation.
 */
void jouer(t_grille g, char pion, int *ligne, int *colonne);

/**
 * \fn choisirColonne(t_grille g, char pion, int colonne)
 * \brief Fonction permettant au joueur de choisir la colonne dans laquelle il joue.
 * \param g la grille de type t_grille, servant de grille de jeux.
 * \param pion paramètre d'entrée qui représentent le caractère du pion qui joue.
 * \param colonne paramètre d'entrée qui représentent l'entier du numéro de colonne où le prochain pion jouera.
 * \return entier correspondant au numéro de la colonne choisie par le joueur.
 *
 */
int choisirColonne(t_grille g, char pion, int colonne);

/**
 * \fn trouverLigne(t_grille g, int colonne)
 * \brief Fonction permettant de trouver la ligne à laquelle doit être placé le pion en fonction de la colonne.
 * \param g la grille de type t_grille, servant de grille de jeux.
 * \param colonne paramètre d'entrée qui représentent l'entier du numéro de colonne où l'on souhaite rechercher une ligne disponible.
 * \return entier correspondant à la ligne à laquelle se trouve un emplacement possible pour un pion dans la colonne passé en paramètre, retourne -1 si la colonne est pleine.
 *
 */
int trouverLigne(t_grille g, int colonne);

/**
 * \fn estVainqueur(t_grille g, int ligne, int colonne)
 * \brief Fonction permettant de vérifier si un pion est gagnant.
 * \param g la grille de type t_grille, servant de grille de jeux.
 * \param ligne paramètre d'entrée qui représentent l'entier du numéro de ligne où le pion se situe.
 * \param colonne paramètre d'entrée qui représentent l'entier du numéro de colonne où le pion se situe.
 * \return booléen indiquant si le pion passé en paramètre est un pion vainqueur, renvoie true si le pion est vainqueur, false sinon.
 */
bool estVainqueur(t_grille g, int ligne, int colonne);

/**
 * \fn finDePartie(char pion)
 * \brief Procédure affichant un message de fin de partie en fonction du pion passé en paramètre.
 * \param pion caractère correspondant au pion qui à gagné la partie, ou la constante VIDE en cas d'égalité.
 */
void finDePartie(char pion);

/**
 * \fn main()
 * \brief Programme principale du Puissance4.
 * \return entier, EXIT_SUCCES
 * 
 * Cette fonction appelle toutes les fonctions défini précédemment afin de permettre le déroulement du jeu.
*/
int main()
{
    /**
     * \var vainqueur
     * \brief Variable de type caractère, représentant le vainqueur.
     *
     * Cette variable est initialisé avec la constante INCONNU, et lorsqu'un joueur est vainqueur, elle prend le caractère du pion du joueur.
     */
    char vainqueur;

    /**
     * \var ligne
     * \brief Variable de type entière, représentant la ligne où à était placé le dernier pion.
     *
     * Cette variable est modifié par la fonction jouer, lorsqu'un pion est placé.
     */
    int ligne;

    /**
     * \var colonne
     * \brief Variable de type entière, représentant la colonne où à était placé le dernier pion.
     *
     * Cette variable est modifié par la fonction jouer, lorsqu'un pion est placé.
     */
    int colonne;

    /**
     * \var grille
     * \brief Variable de type t_grille, permettant de stocker la grille de jeu.
     *
     *  C'est cette variable qui va être principalement modifié lors du jeu.
     */
    t_grille grille;

    debut_partie();

    initGrille(grille);
    vainqueur = INCONNU;
    afficher(grille, PION_A, COLONNE_DEBUT);

    while (vainqueur == INCONNU && !(grillePleine(grille)))
    {
        jouer(grille, PION_A, &ligne, &colonne);
        afficher(grille, PION_B, COLONNE_DEBUT);
        if (estVainqueur(grille, ligne, colonne))
        {
            vainqueur = PION_A;
        }
        else if (!grillePleine(grille))
        {
            jouer(grille, PION_B, &ligne, &colonne);
            afficher(grille, PION_A, COLONNE_DEBUT);
            if (estVainqueur(grille, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
}

void debut_partie()
{
    char debut;
    do
    {
        system("clear");
        printf("Bonjour, bienvenue dans le jeux du puissance 4.\nLes régles sont les suivantes:\nChacun votre tour, vous placez un pion dans une colonne. Le gagnant est le 1er joueur à aligner 4 pions, horizontalement, soit verticalement, soit en diagonale.\nSi la grille est pleine, sans gagnant, il y égalité !\nBon jeu et bonne chance !\n");
        printf("Entrée sur O pour commencer la partie !\n");
        scanf("%c", &debut);
        rest_scanf();
    } while (debut != DEBUTPARTIE);
}

void rest_scanf()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void initGrille(t_grille g)
{
    for (int i = 0; i < NB_LIGNE; i++)
    {
        for (int j = 0; j < NB_COL; j++)
        {
            g[i][j] = VIDE;
        }
    }
}

void afficher(t_grille g, char pion, int colonne)
{
    system("clear");
    /**
     * Affichage du prochaine pion à jouer.
     */
    for (int i = 0; i < colonne; i++)
    {
        printf("    ");
    }
    printf("%3c\n+", pion);

    /**
     * Affichage de la première ligne.
     */
    for (int i = 0; i < NB_COL; i++)
    {
        printf("---+");
    }
    printf("\n");

    /**
     * Affichage des autres lignes.
     */
    for (int i = 0; i < NB_LIGNE; i++)
    {
        printf("|");
        for (int j = 0; j < NB_COL; j++)
        {
            if (g[i][j] != VIDE && g[i][j] != PION_A && g[i][j] != PION_B)
            {
                printf("Erreur dans la partie ! Caractère Inconnu ! FIN DU JEUX.");
                return;
            }
            else
            {
                printf(" %c |", g[i][j]);
            }
        }
        printf("\n+");
        for (int i = 0; i < NB_COL; i++)
        {
            printf("---+");
        }
        printf("\n");
    }

    /**
     * Affichage des numéros de colonne.
     */
    for (int i = 0; i < NB_COL; i++)
    {
        printf("  %d ", i);
    }
    printf("\n");
}

bool grillePleine(t_grille g)
{
    bool pleine = true;
    int colonne;
    colonne = 0;

    while (pleine && colonne < NB_COL)
    {
        if (g[0][colonne] == VIDE)
        {
            pleine = false;
        }
        colonne = colonne + 1;
    }
    return pleine;
}

void jouer(t_grille g, char pion, int *ligne, int *colonne)
{
    *colonne = choisirColonne(g, pion, COLONNE_DEBUT);
    *ligne = trouverLigne(g, *colonne);

    g[*ligne][*colonne] = pion;
}

int choisirColonne(t_grille g, char pion, int colonne)
{
    char action;
    int choix = colonne;
    char message[145];
    scanf("%c", &action);
    rest_scanf();
    while (action != ' ' || trouverLigne(g, choix) == -1)
    {
        strcpy(message, "");
        switch (action)
        {
        case GAUCHE:
            if (choix > 0)
            {
                choix = choix - 1;
            }
            else
            {
                choix = NB_COL - 1;
            }
            break;
        case DROITE:
            if (choix < NB_COL - 1)
            {
                choix = choix + 1;
            }
            else
            {
                choix = 0;
            }
            break;
        case ' ':
            if (trouverLigne(g, choix) == -1)
            {
                strcpy(message, "Impossible de jouer dans cette colonne car elle est pleine !\n");
            }
            break;
        default:
            strcpy(message, "Action inconnu !\nListe des entrées:\nq: vous déplace à gauche.\nd: vous déplace à droite\nespace: place le pion dans la colonne selectionnez.\n");
            break;
        }
        afficher(g, pion, choix);
        // Affiche un message d'erreur si y en a un sinon affiche "" donc rien.
        printf("%s", message);
        scanf("%c", &action);
        rest_scanf();
    }
    return choix;
}

int trouverLigne(t_grille g, int colonne)
{
    int ligne = -1;

    while (ligne < NB_LIGNE && g[ligne + 1][colonne] == VIDE)
    {
        ligne = ligne + 1;
    }
    return ligne;
}

bool estVainqueur(t_grille g, int ligne, int colonne)
{
    int i = 0;

    int align = 0;
    int alignMax = 0;

    /**
     * Verif victoire Verticale
     */
    while (ligne + i < NB_LIGNE && align < VICTOIRE && g[ligne + i][colonne] == g[ligne][colonne])
    {
        i++;
        align++;
    }
    alignMax = alignMax < align ? align : alignMax;

    /**
     * Verif victoire Horizontale
     */
    align = 1;
    i = 1;
    while (colonne + i < NB_COL && align < VICTOIRE && alignMax < VICTOIRE && g[ligne][colonne + i] == g[ligne][colonne])
    {
        i++;
        align++;
    }

    i = 1;
    while (colonne - i >= 0 && align < VICTOIRE && alignMax < VICTOIRE && g[ligne][colonne - i] == g[ligne][colonne])
    {
        i++;
        align++;
    }
    alignMax = alignMax < align ? align : alignMax;

    /**
     * Verif diagonale GAUCHE A DROITE
     */
    align = 1;
    i = 1;
    while (colonne + i < NB_COL && ligne - i >= 0 && align < VICTOIRE && alignMax < VICTOIRE && g[ligne - i][colonne + i] == g[ligne][colonne])
    {
        i++;
        align++;
    }

    i = 1;
    while (colonne - i >= 0 && ligne + i < NB_LIGNE && align < VICTOIRE && alignMax < VICTOIRE && g[ligne + i][colonne - i] == g[ligne][colonne])
    {
        i++;
        align++;
    }
    alignMax = alignMax < align ? align : alignMax;

    /**
     * Verif diagonale DROITE A GAUCHE
     */
    align = 1;
    i = 1;
    while (colonne - i >= 0 && ligne - i >= 0 && align < VICTOIRE && alignMax < VICTOIRE && g[ligne - i][colonne - i] == g[ligne][colonne])
    {
        i++;
        align++;
    }

    i = 1;
    while (colonne + i < NB_COL && ligne + i < NB_LIGNE && align < VICTOIRE && alignMax < VICTOIRE && g[ligne + i][colonne + i] == g[ligne][colonne])
    {
        i++;
        align++;
    }
    alignMax = alignMax < align ? align : alignMax;
    return alignMax >= VICTOIRE;
}

void finDePartie(char pion)
{
    char pionPerdant;
    if (pion == INCONNU)
    {
        printf("Egalité ! Aucun gagnant !\n");
    }
    else
    {
        pionPerdant = pion == PION_B ? PION_A : PION_B;
        printf("Victoire des pions %c face au pions %c ! Félicitations !\n", pion, pionPerdant);
    }
}
