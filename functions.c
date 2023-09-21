#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

Element **allocate_matrice(int length, int width)
{
    Element **matrice;

    // Allocation de mémoire pour les lignes (tableau de pointeurs)
    matrice = (Element **)malloc(length * sizeof(Element *));
    if (matrice == NULL)
    {
        printf("Echec de l'allocation de memoire.\n");
        return NULL;
    }

    // Allocation de mémoire pour chaque ligne (tableau de Elements)
    int i;
    for (i = 0; i < length; i++)
    {
        matrice[i] = (Element *)malloc(width * sizeof(Element));
        if (matrice[i] == NULL)
        {
            printf("Echec de l'allocation de memoire pour la ligne %d.\n", i);

            // Libération de la mémoire déjà allouée
            for (int j = 0; j < i; j++)
            {
                free(matrice[j]);
            }
            free(matrice);

            return NULL;
        }

        int j;
        for (j = 0; j < width; j++)
        {
            matrice[i][j].symbole = ' ';
            matrice[i][j].degres = -1;
            matrice[i][j].etat = 0;
        }
    }

    return matrice;
}

void free_matrice(Element **matrice, int length)
{
    for (int i = 0; i < length; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}

void display_matrice(Element **matrice, int length, int width)
{
    int i, j, k, l;
    for (i = 0; i < length; i++)
    {
        printf("+");
        for (k = 0; k < width; k++)
        {
            printf("---+");
        }

        printf("\n|");
        for (j = 0; j < width; j++)
        {
            printf(" %c |", matrice[i][j].symbole);
        }

        if (i == length - 1)
        {
            printf("\n");
            for (l = 0; l < width + 1; l++)
            {
                if (l == 0)
                    printf("+");
                else
                    printf("---+");
            }
        }
        printf("\n");
    }
}

void menu_1(int *length, int *width)
{
    printf("\n=========================INCENDIE========================\n\n");

    do
    {
        printf("\nEntrez le nombre de cellule en longueur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);
        scanf("%d", length);
    } while (*length < SIZEMIN || *length > SIZEMAX);

    do
    {
        printf("\n\nEntrez le nombre de cellule en largeur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);
        scanf("%d", width);
    } while (*width < SIZEMIN || *width > SIZEMAX);
}

void menu_2(int *mode_game)
{
    printf("\n\nVeuillez choisir le mode de jeu de la simulation :\n\n\t 1 - Manuel\n\t 2- Automatique\n\n");
    do
    {
        scanf("%d", mode_game);
    } while (*mode_game != 1 && *mode_game != 2);
}

void manual_mode(
    Element **matrice,
    int length,
    int width,
    Element select,
    Element ground,
    Element tree,
    Element leaf,
    Element rock,
    Element grass,
    Element water,
    Element ash,
    Element inactive_ash)
{
    printf("\n\nVoici la surface de votre foret :\n\n");

    // affichage matrice
    display_matrice(matrice, length, width);

    // remplissage de la matrice par l'utilisateur
    int i, j;
    int choice;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            printf("\n\nCellule %d %d\n", i, j);
            printf("Choisissez :\n\n1 - Sol(+)\n2 - Arbre(*)\n3 - Feuille( )\n4 - Roche(#)\n5 - Herbe(x)\n6 - Eau(/)\n7 - Cendres(-)\n8 - Cendres eteintes(@)\n\n");

            matrice[i][j] = select;

            display_matrice(matrice, length, width);

            printf("\n");

            do
            {
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    matrice[i][j] = ground;
                    break;
                case 2:
                    matrice[i][j] = tree;
                    break;
                case 3:
                    matrice[i][j] = leaf;
                    break;
                case 4:
                    matrice[i][j] = rock;
                    break;
                case 5:
                    matrice[i][j] = grass;
                    break;
                case 6:
                    matrice[i][j] = water;
                    break;
                case 7:
                    matrice[i][j] = ash;
                    break;
                case 8:
                    matrice[i][j] = inactive_ash;
                    break;
                default:
                    printf("Veuillez entrer une option valide :\n");
                    break;
                }
            } while (choice < 0 || choice > 8);
        }
    }
}

void auto_mode(
    Element **matrice,
    int length,
    int width,
    Element ground,
    Element tree,
    Element leaf,
    Element rock,
    Element grass,
    Element water,
    Element ash,
    Element inactive_ash)
{
    // int i,j;
    // for (i = 0; i < length; i++)
    // {
    //     for (j = 0; j < width; j++)
    //     {
    //         srand(time(NULL));
    //         int random_number = (rand() % 6) + 1;
    //     }
    // }

    // //A finir
}

void menu_3(int *nb_tour, int *x_firstcase, int *y_firstcase)
{
    printf("\n\nEntrez le nombre de tour de la simulation \n\n");
    scanf("%d", nb_tour);

    printf("\n\nEntrez les coordonnees de la case du depart de feu (au format X,X) :\n\n");
    scanf("%d,%d", x_firstcase, y_firstcase);

    printf("\n\n Ok, c'est parti pour l'incendie !!!\n\n");
}

// void menu_4(int *nb_tour, int *x_firstcase, int *y_firstcase)
// {
//     int choix;
//     printf("\nVous êtes à l'étape %d de la simulation.\n\n", nb_tour);
//     printf("\t\t1 - Pour continuer la simulation.\n");
//     printf("\t\t2 - Pour revenir en arrière dans la simulation.\n");
//     printf("\t\t3 - Pour interrompre et choisir une case à modifier dans la simulation.\n");
//     printf("\t\t4 - Pour arrêter la simulation et revenir au debut du jeu.\n");
//     scanf("%d", &choix);

//     switch (choix)
//     {
//     case 1:
//         break;
//     case 2:
//         break;
//     case 3:
//         break;
//     default:
//         break;
//     }
// }

int isEmpty(struct Node *top)
{
    if (top == NULL)
    {
        return 0;
    }
    return 1;
}

void push(struct Node **top, Element data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Pile pleine. Allocation memoire echouee.\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

void pop(struct Node **top, Element *popped)
{
    if (isEmpty(*top))
    {
        printf("Pile vide. Impossible de retirer un element.\n");
    }
    else
    {
        struct Node *temp = *top;
        *popped = temp->data;
        *top = temp->next;
        free(temp);
    }
}

void game(Element **matrice, int length, int width, int *x_firstcase, int *y_firstcase)
{
    // On met d'abord le feu à la case selectionnée par l'utilisateur
    matrice[*x_firstcase][*y_firstcase].etat = 1;
    int i, j;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            // On verifie est-ce que la cellule en question est en feu
            if (matrice[i][j].etat == 1)
            {
                // Puis on verifie si le degres est superieur à 1
                if (matrice[i][j].degres > 1)
                {
                    // On diminue le degres de la case
                    matrice[i][j].degres--;
                    // Le traitement à effectuer maintenant est de faire en sorte de mettre en feu les 8 cases
                    // entourant la case actuelle (si c'est possible)
                    // Premierement les cases qui sont bien entourées de 8 autres cases
                    if (i != 0 && i != length - 1)
                    {
                        if (j != 0 && j != width - 1)
                        {
                            // Verification si l'état de la case n'est pas déjà en feu
                            if (matrice[i - 1][j - 1].etat == 0)
                            {
                                if (matrice[i - 1][j - 1].degres != 0)
                                {
                                    matrice[i - 1][j - 1].etat = 1;
                                    matrice[i - 1][j - 1].degres--;
                                    if (matrice[i - 1][j - 1].degres == 1)
                                    {
                                        matrice[i - 1][j - 1].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i - 1][j].etat == 0)
                            {
                                if (matrice[i - 1][j].degres != 0)
                                {
                                    matrice[i - 1][j].etat = 1;
                                    matrice[i - 1][j].degres--;
                                    if (matrice[i - 1][j].degres == 1)
                                    {
                                        matrice[i - 1][j].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i - 1][j + 1].etat == 0)
                            {
                                if (matrice[i - 1][j + 1].degres != 0)
                                {
                                    matrice[i - 1][j + 1].etat = 1;
                                    matrice[i - 1][j + 1].degres--;
                                    if (matrice[i - 1][j + 1].degres == 1)
                                    {
                                        matrice[i - 1][j + 1].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i][j - 1].etat == 0)
                            {
                                if (matrice[i][j - 1].degres != 0)
                                {
                                    matrice[i][j - 1].etat = 1;
                                    matrice[i][j - 1].degres--;
                                    if (matrice[i][j - 1].degres == 1)
                                    {
                                        matrice[i][j - 1].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i][j + 1].etat == 0)
                            {
                                if (matrice[i][j + 1].degres != 0)
                                {
                                    matrice[i][j + 1].etat = 1;
                                    matrice[i][j + 1].degres--;
                                    if (matrice[i][j + 1].degres == 1)
                                    {
                                        matrice[i][j + 1].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i + 1][j - 1].etat == 0)
                            {
                                if (matrice[i + 1][j - 1].degres != 0)
                                {
                                    matrice[i + 1][j - 1].etat = 1;
                                    matrice[i + 1][j - 1].degres--;
                                    if (matrice[i + 1][j - 1].degres == 1)
                                    {
                                        matrice[i + 1][j - 1].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i + 1][j].etat == 0)
                            {
                                if (matrice[i + 1][j].degres != 0)
                                {
                                    matrice[i + 1][j].etat = 1;
                                    matrice[i + 1][j].degres--;
                                    if (matrice[i + 1][j].degres == 1)
                                    {
                                        matrice[i + 1][j].symbole = '-';
                                    }
                                }
                            }

                            if (matrice[i + 1][j + 1].etat == 0)
                            {
                                if (matrice[i + 1][j + 1].degres != 0)
                                {
                                    matrice[i + 1][j + 1].etat = 1;
                                    matrice[i + 1][j + 1].degres--;
                                    if (matrice[i + 1][j + 1].degres == 1)
                                    {
                                        matrice[i + 1][j + 1].symbole = '-';
                                    }
                                }
                            }
                        }
                        else
                        {
                            // Mise en feu des 5 cases (si possible) entourant la case actuelle, car elle se
                            // trouve du coté gauche ou du coté droit
                            if (j == 0)
                            {
                                if (matrice[i - 1][j].etat == 0)
                                {
                                    if (matrice[i - 1][j].degres != 0)
                                    {
                                        matrice[i - 1][j].etat = 1;
                                        matrice[i - 1][j].degres--;
                                        if (matrice[i - 1][j].degres == 1)
                                        {
                                            matrice[i - 1][j].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i - 1][j + 1].etat == 0)
                                {
                                    if (matrice[i - 1][j + 1].degres != 0)
                                    {
                                        matrice[i - 1][j + 1].etat = 1;
                                        matrice[i - 1][j + 1].degres--;
                                        if (matrice[i - 1][j + 1].degres == 1)
                                        {
                                            matrice[i - 1][j + 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i][j + 1].etat == 0)
                                {
                                    if (matrice[i][j + 1].degres != 0)
                                    {
                                        matrice[i][j + 1].etat = 1;
                                        matrice[i][j + 1].degres--;
                                        if (matrice[i][j + 1].degres == 1)
                                        {
                                            matrice[i][j + 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j + 1].etat == 0)
                                {
                                    if (matrice[i + 1][j + 1].degres != 0)
                                    {
                                        matrice[i + 1][j + 1].etat = 1;
                                        matrice[i + 1][j + 1].degres--;
                                        if (matrice[i + 1][j + 1].degres == 1)
                                        {
                                            matrice[i + 1][j + 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j].etat == 0)
                                {
                                    if (matrice[i + 1][j].degres != 0)
                                    {
                                        matrice[i + 1][j].etat = 1;
                                        matrice[i + 1][j].degres--;
                                        if (matrice[i + 1][j].degres == 1)
                                        {
                                            matrice[i + 1][j].symbole = '-';
                                        }
                                    }
                                }
                            }

                            if (j == width - 1)
                            {
                                if (matrice[i - 1][j].etat == 0)
                                {
                                    if (matrice[i - 1][j].degres != 0)
                                    {
                                        matrice[i - 1][j].etat = 1;
                                        matrice[i - 1][j].degres--;
                                        if (matrice[i - 1][j].degres == 1)
                                        {
                                            matrice[i - 1][j].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i - 1][j - 1].etat == 0)
                                {
                                    if (matrice[i - 1][j - 1].degres != 0)
                                    {
                                        matrice[i - 1][j - 1].etat = 1;
                                        matrice[i - 1][j - 1].degres--;
                                        if (matrice[i - 1][j - 1].degres == 1)
                                        {
                                            matrice[i - 1][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i][j - 1].etat == 0)
                                {
                                    if (matrice[i][j - 1].degres != 0)
                                    {
                                        matrice[i][j - 1].etat = 1;
                                        matrice[i][j - 1].degres--;
                                        if (matrice[i][j - 1].degres == 1)
                                        {
                                            matrice[i][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j - 1].etat == 0)
                                {
                                    if (matrice[i + 1][j - 1].degres != 0)
                                    {
                                        matrice[i + 1][j - 1].etat = 1;
                                        matrice[i + 1][j - 1].degres--;
                                        if (matrice[i + 1][j - 1].degres == 1)
                                        {
                                            matrice[i + 1][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j].etat == 0)
                                {
                                    if (matrice[i + 1][j].degres != 0)
                                    {
                                        matrice[i + 1][j].etat = 1;
                                        matrice[i + 1][j].degres--;
                                        if (matrice[i + 1][j].degres == 1)
                                        {
                                            matrice[i + 1][j].symbole = '-';
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // Mise en feu des 5 cases (si possible) entourant la case actuelle, car elle se
                        // trouve en haut ou en bas
                        if (j != 0 && j != width - 1)
                        {
                            if (i == 0)
                            {
                                if (matrice[i][j - 1].etat == 0)
                                {
                                    if (matrice[i][j - 1].degres != 0)
                                    {
                                        matrice[i][j - 1].etat = 1;
                                        matrice[i][j - 1].degres--;
                                        if (matrice[i][j - 1].degres == 1)
                                        {
                                            matrice[i][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j - 1].etat == 0)
                                {
                                    if (matrice[i + 1][j - 1].degres != 0)
                                    {
                                        matrice[i + 1][j - 1].etat = 1;
                                        matrice[i + 1][j - 1].degres--;
                                        if (matrice[i + 1][j - 1].degres == 1)
                                        {
                                            matrice[i + 1][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j].etat == 0)
                                {
                                    if (matrice[i + 1][j].degres != 0)
                                    {
                                        matrice[i + 1][j].etat = 1;
                                        matrice[i + 1][j].degres--;
                                        if (matrice[i + 1][j].degres == 1)
                                        {
                                            matrice[i + 1][j].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i + 1][j + 1].etat == 0)
                                {
                                    if (matrice[i + 1][j + 1].degres != 0)
                                    {
                                        matrice[i + 1][j + 1].etat = 1;
                                        matrice[i + 1][j + 1].degres--;
                                        if (matrice[i + 1][j + 1].degres == 1)
                                        {
                                            matrice[i + 1][j + 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i][j + 1].etat == 0)
                                {
                                    if (matrice[i][j + 1].degres != 0)
                                    {
                                        matrice[i][j + 1].etat = 1;
                                        matrice[i][j + 1].degres--;
                                        if (matrice[i][j + 1].degres == 1)
                                        {
                                            matrice[i][j + 1].symbole = '-';
                                        }
                                    }
                                }
                            }

                            if (i == length - 1)
                            {
                                if (matrice[i][j - 1].etat == 0)
                                {
                                    if (matrice[i][j - 1].degres != 0)
                                    {
                                        matrice[i][j - 1].etat = 1;
                                        matrice[i][j - 1].degres--;
                                        if (matrice[i][j - 1].degres == 1)
                                        {
                                            matrice[i][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i - 1][j - 1].etat == 0)
                                {
                                    if (matrice[i - 1][j - 1].degres != 0)
                                    {
                                        matrice[i - 1][j - 1].etat = 1;
                                        matrice[i - 1][j - 1].degres--;
                                        if (matrice[i - 1][j - 1].degres == 1)
                                        {
                                            matrice[i - 1][j - 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i - 1][j].etat == 0)
                                {
                                    if (matrice[i - 1][j].degres != 0)
                                    {
                                        matrice[i - 1][j].etat = 1;
                                        matrice[i - 1][j].degres--;
                                        if (matrice[i - 1][j].degres == 1)
                                        {
                                            matrice[i - 1][j].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i - 1][j + 1].etat == 0)
                                {
                                    if (matrice[i - 1][j + 1].degres != 0)
                                    {
                                        matrice[i - 1][j + 1].etat = 1;
                                        matrice[i - 1][j + 1].degres--;
                                        if (matrice[i - 1][j + 1].degres == 1)
                                        {
                                            matrice[i - 1][j + 1].symbole = '-';
                                        }
                                    }
                                }

                                if (matrice[i][j + 1].etat == 0)
                                {
                                    if (matrice[i][j + 1].degres != 0)
                                    {
                                        matrice[i][j + 1].etat = 1;
                                        matrice[i][j + 1].degres--;
                                        if (matrice[i][j + 1].degres == 1)
                                        {
                                            matrice[i][j + 1].symbole = '-';
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // Nous faisons enfin le traitement pour les angles pour changer les 3 cases aux alentours
                    //  de cette derniere
                    if (i == 0 && j == 0)
                    {
                        if (matrice[i][j + 1].etat == 0)
                        {
                            if (matrice[i][j + 1].degres != 0)
                            {
                                matrice[i][j + 1].etat = 1;
                                matrice[i][j + 1].degres--;
                                if (matrice[i][j + 1].degres == 1)
                                {
                                    matrice[i][j + 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i + 1][j + 1].etat == 0)
                        {
                            if (matrice[i + 1][j + 1].degres != 0)
                            {
                                matrice[i + 1][j + 1].etat = 1;
                                matrice[i + 1][j + 1].degres--;
                                if (matrice[i + 1][j + 1].degres == 1)
                                {
                                    matrice[i + 1][j + 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i + 1][j].etat == 0)
                        {
                            if (matrice[i + 1][j].degres != 0)
                            {
                                matrice[i + 1][j].etat = 1;
                                matrice[i + 1][j].degres--;
                                if (matrice[i + 1][j].degres == 1)
                                {
                                    matrice[i + 1][j].symbole = '-';
                                }
                            }
                        }
                    }

                    if (i == 0 && j == width - 1)
                    {
                        if (matrice[i][j - 1].etat == 0)
                        {
                            if (matrice[i][j - 1].degres != 0)
                            {
                                matrice[i][j - 1].etat = 1;
                                matrice[i][j - 1].degres--;
                                if (matrice[i][j - 1].degres == 1)
                                {
                                    matrice[i][j - 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i + 1][j - 1].etat == 0)
                        {
                            if (matrice[i + 1][j - 1].degres != 0)
                            {
                                matrice[i + 1][j - 1].etat = 1;
                                matrice[i + 1][j - 1].degres--;
                                if (matrice[i + 1][j - 1].degres == 1)
                                {
                                    matrice[i + 1][j - 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i + 1][j].etat == 0)
                        {
                            if (matrice[i + 1][j].degres != 0)
                            {
                                matrice[i + 1][j].etat = 1;
                                matrice[i + 1][j].degres--;
                                if (matrice[i + 1][j].degres == 1)
                                {
                                    matrice[i + 1][j].symbole = '-';
                                }
                            }
                        }
                    }

                    if (i == length - 1 && j == width - 1)
                    {
                        if (matrice[i][j - 1].etat == 0)
                        {
                            if (matrice[i][j - 1].degres != 0)
                            {
                                matrice[i][j - 1].etat = 1;
                                matrice[i][j - 1].degres--;
                                if (matrice[i][j - 1].degres == 1)
                                {
                                    matrice[i][j - 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i - 1][j - 1].etat == 0)
                        {
                            if (matrice[i - 1][j - 1].degres != 0)
                            {
                                matrice[i - 1][j - 1].etat = 1;
                                matrice[i - 1][j - 1].degres--;
                                if (matrice[i - 1][j - 1].degres == 1)
                                {
                                    matrice[i - 1][j - 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i - 1][j].etat == 0)
                        {
                            if (matrice[i - 1][j].degres != 0)
                            {
                                matrice[i - 1][j].etat = 1;
                                matrice[i - 1][j].degres--;
                                if (matrice[i - 1][j].degres == 1)
                                {
                                    matrice[i - 1][j].symbole = '-';
                                }
                            }
                        }
                    }

                    if (i == length - 1 && j == 0)
                    {
                        if (matrice[i][j + 1].etat == 0)
                        {
                            if (matrice[i][j + 1].degres != 0)
                            {
                                matrice[i][j + 1].etat = 1;
                                matrice[i][j + 1].degres--;
                                if (matrice[i][j + 1].degres == 1)
                                {
                                    matrice[i][j + 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i - 1][j + 1].etat == 0)
                        {
                            if (matrice[i - 1][j + 1].degres != 0)
                            {
                                matrice[i - 1][j + 1].etat = 1;
                                matrice[i - 1][j + 1].degres--;
                                if (matrice[i - 1][j + 1].degres == 1)
                                {
                                    matrice[i - 1][j + 1].symbole = '-';
                                }
                            }
                        }

                        if (matrice[i - 1][j].etat == 0)
                        {
                            if (matrice[i - 1][j].degres != 0)
                            {
                                matrice[i - 1][j].etat = 1;
                                matrice[i - 1][j].degres--;
                                if (matrice[i - 1][j].degres == 1)
                                {
                                    matrice[i - 1][j].symbole = '-';
                                }
                            }
                        }
                    }
                }
                else if (matrice[i][j].degres == 1)
                {
                    matrice[i][j].symbole = '-';
                    matrice[i][j].etat = 0;
                    matrice[i][j].degres = 0;
                }
            }
        }
    }

    // A partir de là on presente un menu à l'utilisateur et on lui demande quelle action il veut faire par la
    // suite à travers le menu4.
}