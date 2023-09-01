#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char symbole;
    char name[10];
    int degres;
    int etat;
} Entity;

typedef struct
{
    Entity data;
    Node next;
} Node;

int isEmpty(struct Node* top) {
    return top == 0;
}



int main(int argc, char *argv[]){
    int length;
    int width;

    //Menu selection taille matrice
    printf("\n=========================INCENDIE========================\n\n");

    do
    {
        printf("Entrez le nombre de cellules en longueur de la foret, compris entre 1 et 20: ");
        scanf("%d", &length);
    } while (length < 1 || length > 20);

    do
    {
        printf("Entrez le nombre de cellules en largeur de la foret, compris entre 1 et 20: ");
        scanf("%d", &width);
    } while (width < 1 || width > 20);


    //génération de la matrice
    Entity **matrice = malloc(length * sizeof(Entity *));
    if (matrice == NULL)
    {
        printf("Echec de l'allocation\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < length; i++)
    {
        matrice[i] = malloc(width * sizeof(Entity));
        if (matrice[i] == NULL)
        {
            printf("Echec de l'allocation\n");
            return EXIT_FAILURE;
        }
    }

    //menu selection mode de jeu
    printf("Mode de jeu :\n\n1 - Manuel\n2- Automatique\n");

    char mode;
    scanf(" %c", &mode);

    if (mode == '1')
    {
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                printf("\n\nEntrez le type de la cellule %d %d : ", i, j);
                scanf("%d", &(matrice[i][j].symbole));
                matrice[i][j].etat = 0;
            }
        }
    }
    else if (mode == '2')
    {
    }














    return 0;
}