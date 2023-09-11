#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    Element matrice[][];

    //déclaration des éléments
    Element ground = {
        '+',
        0,
        0
    };

    Element tree = {
        '*',
        4,
        0
    };

    Element leaf = {
        ' ',
        2,
        0
    };

    Element rock = {
        '#',
        5,
        0
    };

    Element grass = {
        'x',
        3,
        0
    };

    Element water = {
        '/',
        0,
        0
    };

    Element ash = {
        '-',
        1,
        0
    };

    Element inactive_ash = {
        '@',
        0,
        0
    };


    int random_number;

    //dimensions matrice
    int length;
    int width;


    //Menu selection taille matrice
    printf("\n=========================INCENDIE========================\n\n");

    do
    {
        printf("\nEntrez le nombre de cellule en longueur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);
        scanf("%d", &length);
    } while (length < SIZEMIN || length > SIZEMAX);

    do
    {
        printf("\n\nEntrez le nombre de cellule en largeur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);
        scanf("%d", &width);
    } while (width < SIZEMIN || width > SIZEMAX);


    //Génération de la matrice
    matrice = generate_matrice(length, width);


    //Affichage de la foret a l'utilisateur, selection mode de jeu, et initialisation foret
    int mode_game;
    printf("\n\nVeuillez choisir le mode de jeu de la simulation :\n\n\t 1 - Manuel\n\t 2- Automatique\n\n");
    do
    {
        scanf("%d", &mode_game);
    } while (mode_game != 1 && mode_game != 2);

    //mode remplissage manuel
    if (mode_game == 1)
    {
        printf("\n\nVoici la surface de votre foret :\n\n");

        //affichage matrice
        display_matrice(matrice);

        //remplissage de la matrice par l'utilisateur
        int i,j;
        int choice;
        for(i = 0; i < length; i++)
        {
            for(j = 0; j < width; j++)
            {
                printf("\n\nCellule %d %d\n", i, j);
                printf("Choisissez :\n\n1 - Sol(+)\n2 - Arbre(*)\n3 - Feuille( )\n4 - Roche(#)\n5 - Herbe(x)\n6 - Eau(/)\n7 - Cendres(-)\n8 - Cendres eteintes(@)\n\n");
                
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
                    
                }while (choice < 0 || choice > 8);
            }
        }
    }

    //mode remplissage auto
    else if (mode_game == 2)
    {
        int i,j;
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < width; j++)
            {
                srand(time(NULL));
                int random_number = (rand() % 6) + 1;
                //mode auto à finaliser
            }
        }
    
    }


    int nb_tour;
    
    printf("\n\nEntrez le nombre de tour de la simulation \n");
    scanf("%d", &nb_tour);

    printf("\nEntrez les coordonnees de la case du départ de feu (au format x x)\n\n");
    // scanf("%d", &nb_tour);


    int p;
    for (p = 0; p < nb_tour; p++)
    {
        int i,j;
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (matrice[i][j].degres > 1)
                {
                    if ((
                        matrice[i - 1][j - 1].etat ||
                        matrice[i - 1][j + 1].etat ||
                        matrice[i + 1][j - 1].etat ||
                        matrice[i + 1][j + 1].etat ||
                        matrice[i + 1][j].etat ||
                        matrice[i][j + 1].etat ||
                        matrice[i - 1][j].etat ||
                        matrice[i][j - 1].etat
                        ) == 1)
                    {
                        matrice[i][j].etat = 1;
                    }
                }
                if (matrice[i][j].etat == 1)
                {
                    matrice[i][j].degres = matrice[i][j].degres - 1;
                }
            }
        }






    }

    free_matrice(matrice);

    return 0;
}
