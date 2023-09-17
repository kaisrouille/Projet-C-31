#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

Element** allocate_matrice(int length, int width)
{
    Element **matrice;

    // Allocation de mémoire pour les lignes (tableau de pointeurs)
    matrice = (Element**)malloc(length * sizeof(Element *));
    if(matrice == NULL) {
        printf("Échec de l'allocation de mémoire.\n");
        return NULL;
    }

    // Allocation de mémoire pour chaque ligne (tableau de int)
    int i;
    for(i = 0; i < width; i++) {
        matrice[i] = (Element *)malloc(width * sizeof(Element));
        if (matrice[i] == NULL) {
            printf("Échec de l'allocation de mémoire pour la ligne %d.\n", i);
            return NULL;
        }
    }

    return matrice;
}

void free_matrice(Element **matrice, int length)
{
    for (int i = 0; i < length; i++) {
        free(matrice[i]);
    }
    free(matrice);
}

void display_matrice(Element **matrice, int length, int width)
{
    int i,j,k;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (j == 0)
                printf("+");
            else
                printf("---+");
        }
        for (j = 0; j < width; j++)
        {
            if (j == 0)
                printf("\n|");
            else
                printf("   |");
        }
        if (i == length - 1)
        {
            printf("\n");
            for (k = 0; k < width; k++)
            {
                if (k == 0)
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
    Element ground,
    Element tree,
    Element leaf,
    Element rock,
    Element grass,
    Element water,
    Element ash,
    Element inactive_ash
)
{
    printf("\n\nVoici la surface de votre foret :\n\n");

    //affichage matrice
    display_matrice(matrice, length, width);

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


    //A finir
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
    Element inactive_ash
)
{
    int i,j;
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < width; j++)
        {
            srand(time(NULL));
            int random_number = (rand() % 6) + 1;
        }
    }

    //A finir
}


void menu_3(int *nb_tour, int *x_firstcase, int *y_firstcase)
{
    printf("\n\nEntrez le nombre de tour de la simulation \n");
    scanf("%d", nb_tour);

    printf("\nEntrez les coordonnees de la case du départ de feu\n\n");
    // scanf("%d", &????);


    //A finir
}


int isEmpty(struct Node* top)
{
    if(top == NULL)
    {
        return 0;
    }
    return 1;
}

void push(struct Node** top, Element data)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Pile pleine. Allocation mémoire échouée.\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

void pop(struct Node** top, Element* popped)
{
    if (isEmpty(*top)) {
        printf("Pile vide. Impossible de retirer un élément.\n");
    }
    else
    {
        struct Node* temp = *top;
        *popped = temp->data;
        *top = temp->next;
        free(temp);
    }

}




void game(Element **matrice, int length, int width)
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

