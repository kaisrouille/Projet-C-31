#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char symbole;
    char name[10];
    int degres;
    int etat;
} Entity;


typedef struct Node Node;
struct Node
{
    Entity data;
    Node* next;
};


int isEmpty(struct Node* top) {

    if(top == NULL)
    {
        return 0;
    }
}

void push(struct Node** top, Entity data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Pile pleine. Allocation mémoire échouée.\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

void pop(struct Node** top, Entity* popped) {
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
    int length;
    int width;
    int nombrealeatoire;
    int nbtours;
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
          for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < width; j++)
            {
                srand(time(NULL));
                int nombrealeatoire = (rand() % 6) + 1;
            }
        }
        printf("lancement de la simulation\n");
        printf("donnée le nombre de tours de la simulation \n");
        scanf("%d", &nbtours);
        printf("déclarer la case du départ de feu");
        for (int p = 0; p < nbtours; p++)
        {
            for (int i = 0; i < length; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (Entity.degres > 1)
                    {
                        if ((matrice[i - 1][j - 1].etat || matrice[i - 1][j + 1].etat || matrice[i + 1][j - 1].etat || matrice[i + 1][j + 1].etat || matrice[i + 1][j].etat || matrice[i][j + 1].etat || matrice[i - 1][j].etat || matrice[i][j - 1].etat) == 1)
                        {
                            matrice[i][j].etat = 1;
                        }
                    }
                    if (matrice[i][j].etat == 1)
                    {
                        Entity.degres = Entity.degres - 1;
                    }
                }
            }
        }

    }
    return 0;
}
