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

    // Allocation de mémoire pour chaque ligne (tableau de Element)
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
        HEIGHT_WINDOW);

    MLV_Image *background = MLV_load_image(background_path);
    MLV_Image *title = MLV_load_image(title_path);
    MLV_Image *button_LG = MLV_load_image(button_LG_path);

    MLV_draw_image(
        background,
        0, 0);

    MLV_draw_image(
        title,
        WIDTH_WINDOW / 2 - MLV_get_image_width(title) / 2,
        HEIGHT_WINDOW / 6 - MLV_get_image_height(title) / 2);

    MLV_draw_image(
        button_LG,
        WIDTH_WINDOW / 2 - MLV_get_image_width(button_LG) / 2,
        HEIGHT_WINDOW / 1.5 - MLV_get_image_height(button_LG) / 2);

    MLV_actualise_window();
}

void action_next_menu()
{
    int unicode = 0;
    int mouse_x;
    int mouse_y;
    while (
        !(
            unicode == 32 || // touche ESPACE
            (mouse_x >= 420 &&
             mouse_x <= 772 &&
             mouse_y >= 375 &&
             mouse_y <= 585)))
    {
        MLV_wait_keyboard_or_mouse(NULL, NULL, &unicode, &mouse_x, &mouse_y);
    }
}

void menu_1(
    int *length,
    int *width,
    char *background_path,
    char *menu1_text1_path,
    char *menu1_text2_path)
{
    MLV_Image *background = MLV_load_image(background_path);
    MLV_Image *menu1_text1 = MLV_load_image(menu1_text1_path);
    MLV_Image *menu1_text2 = MLV_load_image(menu1_text2_path);

    // Longueur

    printf("\nEntrez le nombre de cellule en longueur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);

    // Affichage des images
    MLV_draw_image(
        background,
        0, 0);

    MLV_draw_image(
        menu1_text1,
        0, 0);

    // Affichage de la boite de dialogue
    char *text_response_length;

    MLV_wait_input_box(
        WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
        200, 50,
        MLV_COLOR_BLACK,
        MLV_COLOR_BLACK,
        MLV_COLOR_WHITE,
        "Longueur : ",
        &text_response_length);

    // Convertion de l'entrée utilisateur (char) en int
    long tmp_length = strtol(text_response_length, NULL, 10);
    if (tmp_length >= SIZEMIN && tmp_length <= SIZEMAX)
    {
        *length = (int)tmp_length;
        printf("%d", *length);
    }
    else
    {
        printf("Longueur incorrecte");
    }
    free(text_response_length);

    MLV_actualise_window();

    // Largeur

    printf("\n\nEntrez le nombre de cellule en largeur de la foret, compris entre %d et %d: \n\n", SIZEMIN, SIZEMAX);

    MLV_draw_image(
        background,
        0, 0);

    MLV_draw_image(
        menu1_text2,
        0, 0);

    // Affichage de la boite de dialogue
    char *text_response_width;

    MLV_wait_input_box(
        WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
        200, 50,
        MLV_COLOR_BLACK,
        MLV_COLOR_BLACK,
        MLV_COLOR_WHITE,
        "Largeur : ",
        &text_response_width);

    // Convertion de l'entrée utilisateur (char) en int
    long tmp_width = strtol(text_response_width, NULL, 10);
    if (tmp_width >= SIZEMIN && tmp_width <= SIZEMAX)
    {
        *width = (int)tmp_width;
        printf("%d", *width);
    }
    else
    {
        printf("Largeur incorrecte");
    }
    free(text_response_width);

    MLV_actualise_window();
}

void menu_2(long *mode_game, char *background_path, char *text1_menu2_path)
{
    printf("\n\nVeuillez choisir le mode de jeu de la simulation :\n\n\t 1 - Manuel\n\t 2- Automatique\n\n");

    MLV_Image *background = MLV_load_image(background_path);
    MLV_Image *text1_menu2 = MLV_load_image(text1_menu2_path);

    MLV_draw_image(
        background,
        0, 0);

    MLV_draw_image(
        text1_menu2,
        0, 0);

    // Affichage de la boite de dialogue
    char *text_response_mode;

    MLV_wait_input_box(
        WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
        200, 50,
        MLV_COLOR_BLACK,
        MLV_COLOR_BLACK,
        MLV_COLOR_WHITE,
        "Mode de jeu : ",
        &text_response_mode);

    // Convertion de l'entrée utilisateur (char) en int
    long temp_mode = strtol(text_response_mode, NULL, 10);
    if (temp_mode == 1 || temp_mode == 2)
    {
        printf("%ld", temp_mode);
        *mode_game = temp_mode;
    }
    else
    {
        printf("Selection incorrecte");
    }
    free(text_response_mode);

    MLV_actualise_window();
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

    // dessin de la grille a faire
    // action_next_menu();

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

            int status;
            do
            {
                status = scanf("%d", &choice);

                //Securisation entrée user
                if (status != 1)
                {
                    printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 8.\n");

                    while (getchar() != '\n');
                    continue;
                }

                printf("Le choix renseignée est %d.\n\n", choice);

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

            } while (choice < 0 || choice > 8 || status != 1);
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
    if (scanf("%d", nb_tour) == 1)
    {
        printf("Le nombre de tours renseignés est %d.\n\n", *nb_tour);
    }
    else
    {
        printf("Erreur de lecture du nombre de tours.\n");
    }

    printf("\n\nEntrez les coordonnees de la case du depart de feu (au format X,X) :\n\n");
    if (scanf("%d,%d", x_firstcase, y_firstcase) == 2)
    {
        printf("Les coordonnées sont %d,%d.\n", *x_firstcase, *y_firstcase);
    }
    else
    {
        printf("Erreur de lecture des coordonnées.\n");
    }

    printf("\n\n Ok, c'est parti pour l'incendie !!!\n\n");
}

void menu_4(int *nb_tour)
{
    printf("\nIl reste actuellement %d stades de la simulation avant la fin de l'incendie.\n\n", *nb_tour);
    printf("\t\t1 (ou ESPACE) - Pour continuer la simulation.\n");
    printf("\t\t2 - Pour revenir en arrière dans la simulation.\n");
    printf("\t\t3 - Pour interrompre et choisir une case à modifier dans la simulation.\n");
    printf("\t\t4 - Pour arrêter la simulation et revenir au debut du jeu.\n");
}

void push(Stack *stack, Element **matrice, int length, int width)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL)
    {
        printf("erreur allocation memoire");
        return;
    }

    // Clonage de la matrice actuelle
    Element **new_matrice = allocate_matrice(length, width);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_matrice[i][j] = matrice[i][j];
        }
    }

    new_node->data = new_matrice;
    new_node->next = stack->top;
    stack->top = new_node;
}

void pop(Stack *stack, int length, int width)
{
    if (stack->top == NULL)
    {
        printf("La pile est vide.\n");
        return;
    }
    else
    {
        Node *temp = stack->top;

        // Libérer la mémoire de la matrice
        for (int i = 0; i < length; i++)
        {
            free(temp->data[i]);
        }
        free(temp->data);

        // Retirer le nœud du sommet de la pile
        stack->top = stack->top->next;

        // Libérer la mémoire du nœud
        free(temp);
    }
}

void propagation(Element **matrice, int length, int width, Stack *stack)
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
                        // Traitement de la case en haut à gauche
                        if (
                            j != 0 &&
                            matrice[i - 1][j - 1].etat == 0 &&
                            matrice[i - 1][j - 1].degres != 0)
                        {
                            matrice[i - 1][j - 1].etat = 1;
                            matrice[i - 1][j - 1].degres--;
                        }

                        // Traitement de la case en haut au milieu
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
    push(stack, matrice, length, width);
}