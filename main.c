#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "functions.h"

#define SIZEMIN 1
#define SIZEMAX 20

typedef struct Element
{
    char symbole;
    char name[10];
    int degres;
    int etat;
} Element;


typedef struct Node Node;
struct Node
{
    Element data;
    Node* next;
};


int isEmpty(struct Node* top) {

    if(top == NULL)
    {
        return 0;
    }
}

void push(struct Node** top, Element data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Pile pleine. Allocation mémoire échouée.\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

void pop(struct Node** top, Element* popped) {
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


int main(int argc, char *argv[]){

    //dimensions matrice
    int length;
    int width;


    int random_number;
    int nbtours;



    //Menu selection taille matrice
    printf("\n=========================INCENDIE========================\n\n");

    do
    {
        printf("\nEntrez le nombre de cellules en longueur de la foret, compris entre 1 et 20: \n\n");
        scanf("%d", &length);
    } while (length < SIZEMIN || length > SIZEMAX);

    do
    {
        printf("\nEntrez le nombre de cellules en largeur de la foret, compris entre 1 et 20: \n\n");
        scanf("%d", &width);
    } while (width < SIZEMIN || width > SIZEMAX);

    // génération de la matrice
    Element **matrice = malloc(length * sizeof(Element *));
    if (matrice == NULL)
    {
        printf("Echec de l'allocation\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < length; i++)
    {
        matrice[i] = malloc(width * sizeof(Element));
        if (matrice[i] == NULL)
        {
            printf("Echec de l'allocation\n");
            return EXIT_FAILURE;
        }
    }

    // Affichage de la foret a l'utilisateur, selection mode de jeu, et initialisation foret
    int mode;
    printf("Veuillez choisir le mode de jeu de la simulation :\n\n\t 1 - Manuel\n\t 2- Automatique\n");
    do
    {
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2);

    if (mode == 1)
    {
        printf("Voici la surface de votre foret.\n");
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    printf("+");
                else
                    printf("---+");
            }
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    printf("\n|");
                else
                    printf("   |");
            }
            if (i == length - 1)
            {
                printf("\n");
                for (int k = 0; k < width; k++)
                {
                    if (k == 0)
                        printf("+");
                    else
                        printf("---+");
                }
            }
            printf("\n");
        }

        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("\n\nEntrez le type de la cellule %d %d : ", i, j);
                printf("Choisissez :\n1 - Sol(+)\n2 - Arbre(*)\n3 - Feuille( )\n4 - Roche(#)\n5 - Herbe(x)\n6 - Eau(/)\n7 - Cendres(-)\n8 - Cendres eteintes(@)");
                int choix;
                do
                {
                    scanf("%d", &choix);
                    switch (choix)
                    {
                    case 1:
                        matrice[i][j].symbole = '+';
                        strcpy(matrice[i][j].name, "Sol");
                        matrice[i][j].degres = 0;
                        matrice[i][j].etat = 0;
                        break;
                    case 2:
                        matrice[i][j].symbole = '*';
                        strcpy(matrice[i][j].name, "Arbre");
                        matrice[i][j].degres = 4;
                        matrice[i][j].etat = 0;
                        break;
                    case 3:
                        matrice[i][j].symbole = ' ';
                        strcpy(matrice[i][j].name, "Feuille");
                        matrice[i][j].degres = 2;
                        matrice[i][j].etat = 0;
                        break;
                    case 4:
                        matrice[i][j].symbole = '#';
                        strcpy(matrice[i][j].name, "Roche");
                        matrice[i][j].degres = 5;
                        matrice[i][j].etat = 0;
                        break;
                    case 5:
                        matrice[i][j].symbole = 'x';
                        strcpy(matrice[i][j].name, "Herbe");
                        matrice[i][j].degres = 3;
                        matrice[i][j].etat = 0;
                        break;
                    case 6:
                        matrice[i][j].symbole = '/';
                        strcpy(matrice[i][j].name, "Eau");
                        matrice[i][j].degres = 0;
                        matrice[i][j].etat = 0;
                        break;
                    case 7:
                        matrice[i][j].symbole = '-';
                        strcpy(matrice[i][j].name, "Cendres");
                        matrice[i][j].degres = 1;
                        matrice[i][j].etat = 0;
                        break;
                    case 8:
                        matrice[i][j].symbole = '@';
                        strcpy(matrice[i][j].name, "Cendres eteintes");
                        matrice[i][j].degres = 0;
                        matrice[i][j].etat = 0;
                        break;
                    default:
                        printf("Veuillez entrer une option valide :\n");
                        break;
                    }
                    while (choix < 0 || choix > 8)
                        ;
                }
            }
        }
    }
    else if (mode == 2)
    {
          for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                srand(time(NULL));
                int random_number = (rand() % 6) + 1;
            }
        }
    
    }


    printf("\nlancement de la simulation\ndonnée le nombre de tours de la simulation \n");
    scanf("%d", &nbtours);

    printf("déclarer la case du départ de feu\n");

    int p;
    for (p = 0; p < nbtours; p++)
    {
        int i,j;
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (matrice[i][j].degres > 1)
                {
                    if ((matrice[i - 1][j - 1].etat || matrice[i - 1][j + 1].etat || matrice[i + 1][j - 1].etat || matrice[i + 1][j + 1].etat || matrice[i + 1][j].etat || matrice[i][j + 1].etat || matrice[i - 1][j].etat || matrice[i][j - 1].etat) == 1)
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


    return 0;
}
