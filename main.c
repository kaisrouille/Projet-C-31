#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    //déclaration des éléments
    Element ground = {
        '+',
        0,
        0
    };

    Element tree = {
        '*',
        4,
        0
    };

    Element leaf = {
        ' ',
        2,
        0
    };

    Element rock = {
        '#',
        5,
        0
    };

    Element grass = {
        'x',
        3,
        0
    };

    Element water = {
        '/',
        0,
        0
    };

    Element ash = {
        '-',
        1,
        0
    };

    Element inactive_ash = {
        '@',
        0,
        0
    };


    //Selection dimentions de la matrice
    int length, width;
    menu_1(&length, &width);

    //Déclaration et initialisation de la matrice
    Element **matrice = allocate_matrice(length, width);


    //Selection du mode de jeu
    int mode_game;
    menu_2(&mode_game);

    if (mode_game == 1)
    {
        manual_mode(matrice, length, width);
    }
    else if (mode_game == 2)
    {
        auto_mode(matrice, length, width);    
    }


    int nb_tour;
    int x_firstcase, y_firstcase;
    menu_3(&nb_tour, &x_firstcase, &y_firstcase);


    int p;
    for (p = 0; p < nb_tour; p++)
    {
        game();
    }

    free_matrice(matrice, length);

    return 0;
}
