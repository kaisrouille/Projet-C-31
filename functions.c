#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("\n=========================L'INCENDIE========================\n\n\n");

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
			(
				mouse_x >= 420 &&
			 	mouse_x <= 772 &&
				mouse_y >= 375 &&
			 	mouse_y <= 585
			)
		)
	)
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
	printf("Entrez le nombre de cellule en longueur de la foret, compris entre %d et %d : \n\n", SIZEMIN, SIZEMAX);

	// Affichage des images
	MLV_draw_image(
		background,
		0, 0);

	MLV_draw_image(
		menu1_text1,
		0, 0);

	//Securisation entrée user
	char *text_response_length;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"Longueur : ",
			&text_response_length);

		// Convertir l'entrée utilisateur (char) en long
		long tmp_length = strtol(text_response_length, NULL, 10);

		// Vérifier si la valeur convertie est dans la plage valide
		if (tmp_length < SIZEMIN || tmp_length > SIZEMAX)
		{
			printf("Longueur invalide. Veuillez entrer une valeur entre %d et %d.\n", SIZEMIN, SIZEMAX);

			// Libérer la mémoire avant de demander à nouveau
			free(text_response_length);

			MLV_actualise_window();

			// Continuer la boucle si la valeur n'est pas valide
			continue;
		}

		*length = (int)tmp_length;

		// Libération de la mémoire si la valeur est valide et sortie de la boucle
		free(text_response_length);

		break;

	} while (1);

	printf("Longueur choisie : %d\n\n\n", *length);

	// Largeur

	printf("Entrez le nombre de cellule en largeur de la foret, compris entre %d et %d : \n\n", SIZEMIN, SIZEMAX);

	MLV_draw_image(
		background,
		0, 0);

	MLV_draw_image(
		menu1_text2,
		0, 0);

	// Securisation entrée user
	char *text_response_width;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"Largeur : ",
			&text_response_width);

		// Convertir l'entrée utilisateur (char) en long
		long tmp_width = strtol(text_response_width, NULL, 10);

		// Vérifier si la valeur convertie est dans la plage valide
		if (tmp_width < SIZEMIN || tmp_width > SIZEMAX)
		{
			printf("Largeur invalide. Veuillez entrer une valeur entre %d et %d.\n", SIZEMIN, SIZEMAX);

			// Libérer la mémoire avant de demander à nouveau
			free(text_response_width);

			MLV_actualise_window();

			// Continuer la boucle si la valeur n'est pas valide
			continue;
		}

		*width = (int)tmp_width;

		// Libération de la mémoire si la valeur est valide et sortie de la boucle
		free(text_response_width);

		break;

	} while (1);

	printf("Largeur choisie : %d\n\n\n", *width);
}

void menu_2(long *mode_game, char *background_path, char *text1_menu2_path)
{
	printf("Veuillez choisir le mode de remplissage de la foret :\n\n\t 1 - Manuel\n\t 2- Automatique\n\n");

	MLV_Image *background = MLV_load_image(background_path);
	MLV_Image *text1_menu2 = MLV_load_image(text1_menu2_path);

	MLV_draw_image(
		background,
		0, 0);

	MLV_draw_image(
		text1_menu2,
		0, 0);

	char *text_response_mode;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"Mode de jeu : ",
			&text_response_mode);

		// Conversion de l'entrée user (qui est en char dans la textbox) en long
		long temp_mode = strtol(text_response_mode, NULL, 10);

		//Sécurisation de l'entrée user
		if (temp_mode != 1 && temp_mode != 2)
		{
			printf("Selection du mode de jeu invalide, entrez 1(Manuel) ou 2(Automatique) :\n");

			free(text_response_mode);

			MLV_actualise_window();

			continue; // Continuer la boucle si la valeur n'est pas valide
		}

		*mode_game = temp_mode;
		free(text_response_mode);

		break;

	} while (1);

	if (*mode_game == 1)
	{
		printf("Mode de remplissage choisi : Manuel\n\n\n");
	}
	else if (*mode_game == 2)
	{
		printf("Mode de remplissage choisi : Aleatoire\n\n\n");
	}
}

void modify_case(
	Element **matrice,
	int length,
	int width,
	int x,
	int y,
	int choice,
	Element ground,
	Element tree,
	Element leaf,
	Element rock,
	Element grass,
	Element water,
	Element ash,
	Element inactive_ash)
{
	switch (choice)
	{
	case 1:
		matrice[x][y] = ground;
		break;
	case 2:
		matrice[x][y] = tree;
		break;
	case 3:
		matrice[x][y] = leaf;
		break;
	case 4:
		matrice[x][y] = rock;
		break;
	case 5:
		matrice[x][y] = grass;
		break;
	case 6:
		matrice[x][y] = water;
		break;
	case 7:
		matrice[x][y] = ash;
		break;
	case 8:
		matrice[x][y] = inactive_ash;
		break;
	default:
		break;
	}
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
	// remplissage de la matrice par l'utilisateur
	printf("Veuillez remplir la surface de votre foret :\n\n");
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			matrice[i][j] = select;

			// affichage matrice
			display_matrice(matrice, length, width);

			// Choix de l'utilisateur
			printf("Choisissez un element parmis :\n\n1 - Sol(+)\n2 - Arbre(*)\n3 - Feuille( )\n4 - Roche(#)\n5 - Herbe(x)\n6 - Eau(/)\n7 - Cendres(-)\n8 - Cendres eteintes(@)\n\n");

			int choice, status;
			do
			{
				printf("Element choisi : ");
				status = scanf("%d", &choice);

				// Vide le buffer d'entrée si la lecture échoue
				if (status != 1)
				{
					printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 8.\n");
					while (getchar() != '\n'); // Vide le buffer d'entrée
				}
				else if (choice < 1 || choice > 8)
				{
					printf("Entrée invalide. Veuillez entrer un nombre entre 1 et 8.\n");
					status = 0; // Force la continuation de la boucle
				}

			} while (status != 1);

			modify_case(
				matrice,
				length,
				width,
				i,
				j,
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

			printf("\n");
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
	srand(time(NULL));
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < width; j++)
		{
			int random_number = (rand() % 8) + 1;

			modify_case(
				matrice,
				length,
				width,
				i,
				j,
				random_number,
				ground,
				tree,
				leaf,
				rock,
				grass,
				water,
				ash,
				inactive_ash);
		}
	}
}

void menu_3(int *nb_tour, int *x_firstcase, int *y_firstcase, char *background_path, char *menu3_text1_path, char *menu3_text2_path)
{
	printf("Entrez le nombre d'etape de la simulation : \n\n");

	MLV_Image *background = MLV_load_image(background_path);
	MLV_Image *menu3_text1 = MLV_load_image(menu3_text1_path);

	MLV_draw_image(
		background,
		0, 0);

	MLV_draw_image(
		menu3_text1,
		0, 0
	);

	//Securisation entrée user
	char *text_response_nb_tour;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"Nombre d'etape : ",
			&text_response_nb_tour);

		// Convertir l'entrée utilisateur (char) en long
		long tmp_nb_tour = strtol(text_response_nb_tour, NULL, 10);

		// Vérifier si la valeur convertie est dans la plage valide
		if (tmp_nb_tour < 0)
		{
			printf("Nombre d'etape invalide. Veuillez entrer une valeur superieure a 0.\n");

			// Libérer la mémoire avant de demander à nouveau
			free(text_response_nb_tour);

			MLV_actualise_window();

			// Continuer la boucle si la valeur n'est pas valide
			continue;
		}

		*nb_tour = (int)tmp_nb_tour;

		// Libération de la mémoire si la valeur est valide et sortie de la boucle
		free(text_response_nb_tour);

		break;

	} while (1);

	printf("Nombre d'etape choisi : %d\n\n\n", *nb_tour);


	printf("Entrez les coordonnees de la case du depart de feu : \n\n");

	MLV_Image *menu3_text2 = MLV_load_image(menu3_text2_path);

	MLV_draw_image(
		background,
		0, 0);

	MLV_draw_image(
		menu3_text2,
		0, 0
	);

	//Securisation entrée user
	char *text_response_x_firstcase;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"x : ",
			&text_response_x_firstcase
		);

		// Convertir l'entrée utilisateur (char) en long
		long tmp_x_firstcase = strtol(text_response_x_firstcase, NULL, 10);

		// Vérifier si la valeur convertie est dans la plage valide
		if (tmp_x_firstcase < 0 )
		{
			printf("Coordonnee X invalide. Veuillez entrer une valeur superieure a 0 pour chaque parametre.\n");

			// Libérer la mémoire avant de demander à nouveau
			free(x_firstcase);

			MLV_actualise_window();

			// Continuer la boucle si la valeur n'est pas valide
			continue;
		}

		*x_firstcase = (int)tmp_x_firstcase;

		// Libération de la mémoire si la valeur est valide et sortie de la boucle
		free(text_response_x_firstcase);

		break;

	} while (1);

	printf("Coordonnee X de la premiere case en feu : %d\n", *x_firstcase);

	char *text_response_y_firstcase;
	do
	{
		// Affichage de la boite de dialogue
		MLV_wait_input_box(
			WIDTH_WINDOW / 2 - 100, HEIGHT_WINDOW / 2,
			200, 50,
			MLV_COLOR_BLACK,
			MLV_COLOR_BLACK,
			MLV_COLOR_WHITE,
			"y : ",
			&text_response_y_firstcase
		);

		// Convertir l'entrée utilisateur (char) en long
		long tmp_y_firstcase = strtol(text_response_y_firstcase, NULL, 10);

		// Vérifier si la valeur convertie est dans la plage valide
		if (tmp_y_firstcase < 0)
		{
			printf("Coordonnees invalides. Veuillez entrer une valeur superieure a 0 pour chaque parametre.\n");

			// Libérer la mémoire avant de demander à nouveau
			free(y_firstcase);

			MLV_actualise_window();

			// Continuer la boucle si la valeur n'est pas valide
			continue;
		}
		*y_firstcase = (int)tmp_y_firstcase;

		// Libération de la mémoire si la valeur est valide et sortie de la boucle
		free(text_response_y_firstcase);

		break;

	} while (1);

	printf("Coordonnee Y de la premiere case en feu : %d\n\n\n", *y_firstcase);

	printf("Ok, c'est parti pour l'incendie !!!\n\n");
}

void menu_4(int nb_tour)
{
	printf("\nIl reste actuellement %d etape(s) de la simulation avant la fin de l'incendie.\n\n", nb_tour);
	printf("\t\tESPACE - Pour continuer la simulation.\n");
	printf("\t\tBACKSPACE - Pour revenir en arrière dans la simulation.\n");
	printf("\t\tC - Pour interrompre et modifier une case dans la simulation.\n");
	printf("\t\tQ - Pour arrêter la simulation et revenir au debut du jeu.\n\n");
}

void push(Stack *stack, Element **matrice, int length, int width)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (new_node == NULL)
	{
		printf("Erreur d'allocation memoire\n");
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

void propagation(Element **matrice, int length, int width)
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
					// Si la case n'avait pas déjà été modifié pendant cette propagation
					if (!matrice[i][j].case_modifiee)
					{
						if (matrice[i][j].degres == 2)
							matrice[i][j].symbole = '-';
						// On diminue le degres de la case
						matrice[i][j].degres--;
						matrice[i][j].case_modifiee = true;

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
								matrice[i - 1][j - 1].case_modifiee = true;
							}

							// Traitement de la case en haut au milieu
							if (matrice[i - 1][j].etat == 0 && matrice[i - 1][j].degres != 0)
							{
								matrice[i - 1][j].etat = 1;
								matrice[i - 1][j].degres--;
								matrice[i - 1][j].case_modifiee = true;
							}

							// Traitement de la case en haut à droite
							if (
								j != width - 1 &&
								matrice[i - 1][j + 1].etat == 0 &&
								matrice[i - 1][j + 1].degres != 0)
							{
								matrice[i - 1][j + 1].etat = 1;
								matrice[i - 1][j + 1].degres--;
								matrice[i - 1][j + 1].case_modifiee = true;
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
								matrice[i + 1][j + 1].case_modifiee = true;
							}

							// Traitement de la case d'en bas
							if (matrice[i + 1][j].etat == 0 && matrice[i + 1][j].degres != 0)
							{
								matrice[i + 1][j].etat = 1;
								matrice[i + 1][j].degres--;
								matrice[i + 1][j].case_modifiee = true;
							}

							// Traitement de la case en bas à gauche
							if (
								j != 0 &&
								matrice[i + 1][j - 1].etat == 0 &&
								matrice[i + 1][j - 1].degres != 0)
							{
								matrice[i + 1][j - 1].etat = 1;
								matrice[i + 1][j - 1].degres--;
								matrice[i + 1][j - 1].case_modifiee = true;
							}
						}

						// Condition pour le traitement de la case à gauche
						if (
							j != 0 &&
							matrice[i][j - 1].etat == 0 &&
							matrice[i][j - 1].degres != 0)
						{
							// Traitement de la case à gauche
							matrice[i][j - 1].etat = 1;
							matrice[i][j - 1].degres--;
							matrice[i][j - 1].case_modifiee = true;
						}

						// Condition pour le traitement de la case à droite
						if (
							j != width - 1 &&
							matrice[i][j + 1].etat == 0 &&
							matrice[i][j + 1].degres != 0)
						{
							// Traitement de la case à droite
							matrice[i][j + 1].etat = 1;
							matrice[i][j + 1].degres--;
							matrice[i][j + 1].case_modifiee = true;
						}
					}
				}
				// Si case est en feu mais que c'est des cendres
				else if (matrice[i][j].degres == 1 && !matrice[i][j].case_modifiee)
				{
					matrice[i][j].symbole = '@';
					matrice[i][j].etat = 0;
					matrice[i][j].degres = 0;
					matrice[i][j].case_modifiee = true;
				}
			}
		}
	}
}

// void propagation_a_b(Element **matrice, int length, int width, int xa, int xb) {}