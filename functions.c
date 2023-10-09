#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

#include <MLV/MLV_all.h>

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


void display_init(char *background_path, char *title_path, char *button_LG_path)
{
    printf("\n=========================INCENDIE========================\n\n");

    MLV_create_window(
        "Incendie - Le Jeu",
        "Incendie",
        WIDTH_WINDOW,
        HEIGHT_WINDOW
    );

    MLV_Image *background = MLV_load_image(background_path);
    MLV_Image *title = MLV_load_image(title_path);
    MLV_Image *button_LG = MLV_load_image(button_LG_path);

    MLV_draw_image(
        background,
        0,0
    );

    MLV_draw_image(
        title,
        45,75
    );

    MLV_draw_image(
        button_LG,
        550,550
    );

    MLV_actualise_window();
}

void action_next_menu()
{
    MLV_Keyboard_button sym;
    MLV_Keyboard_modifier mod;
    int unicode = 0;
    int mouse_x;
    int mouse_y;
    while(
        !(
            unicode == 32 ||
            (
                mouse_x >= 550 &&
                mouse_x <= 1050 &&
                mouse_y >= 550 &&
                mouse_y <= 707
            )
        )
    )
    {
        MLV_wait_keyboard_or_mouse(&sym, &mod, &unicode, &mouse_x, &mouse_y);
    }
}


void menu_1(int *length, int *width, char *background_path, char *text1_menu1_path, char *text2_menu1_path)
{
    do
    {
        printf("\nEntrez le nombre de cellule en longueur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);

        MLV_Image *background = MLV_load_image(background_path);
        MLV_Image *text1_menu1 = MLV_load_image(text1_menu1_path);

        MLV_draw_image(
            background,
            0,0
        );

        MLV_draw_image(
            text1_menu1,
            120,400
        );
        
        MLV_actualise_window();

        scanf("%d", length);
    } while(*length < SIZEMIN || *length > SIZEMAX);

    do
    {
        printf("\n\nEntrez le nombre de cellule en largeur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);

        MLV_Image *background = MLV_load_image(background_path);
        MLV_Image *text2_menu1 = MLV_load_image(text2_menu1_path);

        MLV_draw_image(
            background,
            0,0
        );

        MLV_draw_image(
            text2_menu1,
            120,400
        );

        MLV_actualise_window();

        scanf("%d", width);
    } while(*width < SIZEMIN || *width > SIZEMAX);
}

void menu_2(int *mode_game, char *background_path, char *text1_menu2_path)
{
    printf("\n\nVeuillez choisir le mode de jeu de la simulation :\n\n\t 1 - Manuel\n\t 2- Automatique\n\n");

        MLV_Image *background = MLV_load_image(background_path);
        MLV_Image *text1_menu2 = MLV_load_image(text1_menu2_path);

        MLV_draw_image(
            background,
            0,0
        );

        MLV_draw_image(
            text1_menu2,
            40,300
        );
        
        MLV_actualise_window();

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








    //dessin de la grille a faire
    //action_next_menu();


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

int isEmpty(struct Node *top)
{
    if (top == NULL)
    {
        return 1;
    }
    return 0;
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

void menu_4(int *nb_tour, int *x_firstcase, int *y_firstcase)
{
    // int choix;
    // printf("\nVous êtes à l'étape %d de la simulation.\n\n", nb_tour);
    // printf("\t\t1 - Pour continuer la simulation.\n");
    // printf("\t\t2 - Pour revenir en arrière dans la simulation.\n");
    // printf("\t\t3 - Pour interrompre et choisir une case à modifier dans la simulation.\n");
    // printf("\t\t4 - Pour arrêter la simulation et revenir au debut du jeu.\n");
    // scanf("%d", &choix);

    // switch (choix)
    // {
    // case 1:
    //     break;
    // case 2:
    //     break;
    // case 3:
    //     break;
    // default:
    //     break;
    // }
}

void game(Element **matrice, int length, int width)
{
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

                    // Condition pour le traitement des cases du haut
                    if (i != 0)
                    {
                        // Traitement de la case en haut en gauche
                        if (
                            j != 0 &&
                            matrice[i - 1][j - 1].etat == 0 &&
                            matrice[i - 1][j - 1].degres != 0)
                        {
                            matrice[i - 1][j - 1].etat = 1;
                            matrice[i - 1][j - 1].degres--;
                        }

                        // Traitement de la case du dessus
                        if (matrice[i - 1][j].etat == 0 && matrice[i - 1][j].degres != 0)
                        {
                            matrice[i - 1][j].etat = 1;
                            matrice[i - 1][j].degres--;
                        }

                        // Traitement de la case en haut à droite
                        if (
                            j != width - 1 &&
                            matrice[i - 1][j + 1].etat == 0 &&
                            matrice[i - 1][j + 1].degres != 0)
                        {
                            matrice[i - 1][j + 1].etat = 1;
                            matrice[i - 1][j + 1].degres--;
                        }
                    }

                    // Condition pour le traitement des cases du bas
                    if (i != length - 1)
                    {
                        // Traitement de la case en bas à droite
                        if (
                            j != width - 1 &&
                            matrice[i + 1][j + 1].etat == 0 &&
                            matrice[i + 1][j + 1].degres != 0)
                        {
                            matrice[i + 1][j + 1].etat = 1;
                            matrice[i + 1][j + 1].degres--;
                        }

                        // Traitement de la case d'en bas
                        if (matrice[i + 1][j].etat == 0 && matrice[i + 1][j].degres != 0)
                        {
                            matrice[i + 1][j].etat = 1;
                            matrice[i + 1][j].degres--;
                        }

                        // Traitement de la case en bas à gauche
                        if (
                            j != 0 &&
                            matrice[i + 1][j - 1].etat == 0 &&
                            matrice[i + 1][j - 1].degres != 0)
                        {
                            matrice[i + 1][j - 1].etat = 1;
                            matrice[i + 1][j - 1].degres--;
                        }
                    }

                    // Condition pour le traitement de la case à gauche
                    if (
                        j != 0 &&
                        matrice[i][j + 1].etat == 0 &&
                        matrice[i][j + 1].degres != 0)
                    {
                        // Traitement de la case à droite
                        matrice[i][j + 1].etat = 1;
                        matrice[i][j + 1].degres--;
                    }

                    // Condition pour le traitement de la case à droite
                    if (
                        j != width - 1 &&
                        matrice[i][j - 1].etat == 0 &&
                        matrice[i][j - 1].degres != 0)
                    {
                        // Traitement de la case à gauche
                        matrice[i][j - 1].etat = 1;
                        matrice[i][j - 1].degres--;
                    }
                }
                // Si case est en feu mais que c'est des cendres
                else if (matrice[i][j].degres == 1)
                {
                    matrice[i][j].symbole = '@';
                    matrice[i][j].etat = 0;
                    matrice[i][j].degres = 0;
                }
            }
        }
    }

    // A partir de là on presente un menu à l'utilisateur et on lui demande quelle action il veut faire par la
    // suite à travers le menu4.
}