#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "functions.h"

int main(int argc, char *argv[])
{
	// images affichage graphique
	char background[] = "images/background.png";
	char title[] = "images/title.png";
	char button_LG[] = "images/button_LG.png";
	char menu1_text1[] = "images/menu1_text1.png";
	char menu1_text2[] = "images/menu1_text2.png";
	char menu2_text1[] = "images/menu2_text1.png";

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
		0};

	// Initialisation du jeu
	display_init(background, title, button_LG);

	// Detection action utilisateur (bouton ou barre espace clavier)
	action_next_menu();

	// Selection dimentions de la matrice
	int length, width;
	menu_1(&length, &width, background, menu1_text1, menu1_text2);

	// Déclaration et initialisation de la matrice
	Element **matrice = allocate_matrice(length, width);

	// Selection du mode de jeu
	long mode_game;
	menu_2(&mode_game, background, menu2_text1);

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

	//Mise en pile de la matrice initialisée
	Stack stack;
	push(&stack, matrice, length, width);

	// On met d'abord le feu à la case selectionnée par l'utilisateur
	matrice[x_firstcase][y_firstcase].etat = 1;

	display_matrice(matrice, length, width);

	// Déroulement du jeu
	int p;
	for (p = 0; p < nb_tour; p++)
	{
		propagation(matrice, length, width, &stack);

		display_matrice(matrice, length, width);

		menu_4(nb_tour - p);

		int unicode = 0;
		while (
			!(
				unicode == 32 ||
				unicode == 8 ||
				unicode == 99 ||
				unicode == 113
			)
		)
		{
			MLV_wait_keyboard(NULL, NULL, &unicode);
		}

		// Appuie sur ESPACE : continuer la simulation
		if (unicode == 32)
		{
			push(&stack, matrice, length, width);
		}
		// Appuie sur BACKSPACE : retourner en arrière
		else if (unicode == 8)
		{
			pop(&stack, length, width);
		}
		// Appuie sur C :changer le contenu d'une case
		else if (unicode == 99)
		{
			printf("Entrez les coordonnees de la case a modifier (au format X,X):\n\n");

			int x_modify;
			int y_modify;
			if (scanf("%d,%d", &x_modify, &y_modify) == 2)
			{
				printf("Le choix renseigne est %d,%d.\n\n", x_modify,y_modify);

				//scanf + modify_case à implenter ici

			}
			else
			{
				printf("Erreur de lecture du choix.\n");
			}
 
			int choice;
			int status = scanf("%d", &choice);
			if (status != 1)
			{
				printf("Entree invalide. Veuillez entrer un nombre entre 1 et 8.\n");

				while (getchar() != '\n');
				continue;
			}

			modify_case(
				matrice,
				length,
				width,
				x_modify, 
				y_modify,
				choice,
				ground,
				tree,
				leaf,
				rock,
				grass,
				water,
				ash,
				inactive_ash
			);
		}
		// Appuie sur Q : quitter la partie/recommencer au début
		else if (unicode == 113)
		{
			break;
		}
	}

	// Libération de la mémoire de la matrice
	free_matrice(matrice, length);

	return 0;
}