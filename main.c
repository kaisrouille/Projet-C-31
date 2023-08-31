#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[10];
    int type;
    int degres;
    int etat;
} entity;


int main(int argc, char *argv[])
{
    printf("\n-----INCENDIE-----\n\n");
    int length;
    int width;

    do {
        printf("Entrez le nombre de cellules en longueur compris entre 1 et 20: ");
        scanf("%d", &length);
    } while (length < 1 || length > 20);

    do {
        printf("Entrez le nombre de cellules en largeur compris entre 1 et 20: ");
        scanf("%d", &width);
    } while (width < 1 || width > 20);


    entity matrice[length][width];

    printf("Mode de jeu :\n\n1 - Manuel\n2- Automatique\n");

    if(getchar() == '1')
    {
        int i, j;
        for(i = 0; i < length; i++)
        {
            for(j = 0; j < width; j++)
            {
                printf("\n\nEntrez le type de la cellule %d %d : ", i, j);
                scanf("%d", &matrice[i][j].type);
                matrice[i][j].etat = 0;
            }
        }











    }
    else if (getchar() == '2')
    {
        




    }

    return 0;
}
