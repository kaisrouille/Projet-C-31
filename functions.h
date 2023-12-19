#define WIDTH_WINDOW 1175
#define HEIGHT_WINDOW 700

#define SIZEMIN 1
#define SIZEMAX 20

typedef struct Element
{
	char symbole;
	int degres;
	int etat;
} Element;

// Structure noeud pile
typedef struct Node
{
	Element **data;
	struct Node *next;
} Node;

// Structure pile
typedef struct Stack
{
	Node *top;
} Stack;

// Allocation de mémoire de la matrice
Element **allocate_matrice(int length, int width);

// Libération de mémoire de la matrice
void free_matrice(Element **matrice, int length);

// Affichage console de la matrice
void display_matrice(Element **matrice, int length, int width);

// Detection action utilisateur (bouton ou barre espace clavier)
void action_next_menu();

// Menu de sélection des dimensions de la matrice
void menu_1(int *length, int *width, char *background_path, char *text1_menu1_path, char *text2_menu1_path);

// Menu de sélection du mode de jeu
void menu_2(long *mode_game, char *background_path, char *text1_menu2_path);

//Modifier une case
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
	Element inactive_ash
);

// Remplissage manuel de la matrice
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
	Element inactive_ash);

// Remplissage auto de la matrice
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
	Element inactive_ash);

void menu_3(int *nb_tour, int *x_firstcase, int *y_firstcase);

void menu_4(int nb_tour);

void push(Stack *stack, Element **matrice, int length, int width);

void pop(Stack *stack, int length, int width);

void propagation(Element **matrice, int length, int width, Stack *stack);

void display_init(char *background_path, char *title_path, char *button_LG_path);