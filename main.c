#include <stdio.h>
#include <stdlib.h>
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


    //génération de la matrice
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


    //menu selection mode de jeu
    printf("Mode de jeu :\n\n1 - Manuel\n2- Automatique\n\n");

    int mode;
    scanf(" %d", &mode);

    if (mode == 1)
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("\n\nEntrez le type de la cellule %d %d : ", i, j);
                scanf("%c", &(matrice[i][j].symbole));
                matrice[i][j].etat = 0;
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
