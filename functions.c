#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

void generate_matrice(int length, int width)
{
    Element **matrice = malloc(length * sizeof(Element *));
    if (matrice == NULL)
    {
        printf("Echec de l'allocation\n");
        return EXIT_FAILURE;
    }
    int i;
    for(i = 0; i < length; i++)
    {
        matrice[i] = malloc(width * sizeof(Element));
        if (matrice[i] == NULL)
        {
            printf("Echec de l'allocation\n");
            return EXIT_FAILURE;
        }
    }
}

void display_matrice(Element matrice)
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


int isEmpty(struct Node* top)
{
    if(top == NULL)
    {
        return 0;
    }
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