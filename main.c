#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    MLV_Image *background;



    // affichage de selection de case pour le mode manuel
    Element select = {
        's',
        -9,
        -9};

    // déclaration des éléments
    Element ground = {
        '+',
        0,
        0};

    Element tree = {
        '*',
        4,
        0};

    Element leaf = {
        ' ',
        2,
        0};

    Element rock = {
        '#',
        5,
        0};

    Element grass = {
        'x',
        3,
        0};

    Element water = {
        '/',
        0,
        0};

    Element ash = {
        '-',
        1,
        0};

    Element inactive_ash = {
        '@',
        0,
        0
    };


    MLV_create_window (
        "Incendie - Le Jeu",
		"Incendie",
		WIDTH_WINDOW,
		HEIGHT_WINDOW 
	);

    background = MLV_load_image("images/Background.png");

    MLV_draw_image(
        background,
		0,
        0 
	);

    MLV_actualise_window();



    // Selection dimentions de la matrice
    int length, width;
    menu_1(&length, &width);

    // Déclaration et initialisation de la matrice
    Element **matrice = allocate_matrice(length, width);

    // Selection du mode de jeu
    int mode_game;
    menu_2(&mode_game);

    // Initialisation de la matrice
    if (mode_game == 1)
    {
        manual_mode(
            matrice,
            length,
            width,
            select,
            ground,
            tree,
            leaf,
            rock,
            grass,
            water,
            ash,
            inactive_ash);
    }
    else if (mode_game == 2)
    {
        auto_mode(
            matrice,
            length,
            width,
            ground,
            tree,
            leaf,
            rock,
            grass,
            water,
            ash,
            inactive_ash);
    }

    printf("\n\nVoici votre foret !\n\n");
    display_matrice(matrice, length, width);

    // Selection du nombre de tour et de la case de départ
    int nb_tour;
    int x_firstcase, y_firstcase;
    menu_3(&nb_tour, &x_firstcase, &y_firstcase);

    // Déroulement du jeu
    int p;
    for (p = 0; p < nb_tour; p++)
    {
        // On met d'abord le feu à la case selectionnée par l'utilisateur
        matrice[x_firstcase][y_firstcase].etat = 1;
        display_matrice(matrice, length, width);
        game(matrice, length, width);
        display_matrice(matrice, length, width);
        printf("\n\n\n\n\n");
    }

    // Libération de la mémoire de la matrice
    free_matrice(matrice, length);

    return 0;
}
