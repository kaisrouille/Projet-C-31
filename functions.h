#define WIDTH_WINDOW 1600
#define HEIGHT_WINDOW 950

#define SIZEMIN 1
#define SIZEMAX 20

typedef struct Element
{
    char symbole;
    int degres;
    int etat;
} Element;

typedef struct Node Node;
struct Node
{
    Element data;
    Node* next;
};



//Allocation de mémoire de la matrice
Element **allocate_matrice(int length, int width);

//Libération de mémoire de la matrice
void free_matrice(Element **matrice, int length);

//Affichage console de la matrice
void display_matrice(Element **matrice, int length, int width);


//Menu de sélection des dimensions de la matrice
void menu_1(int *length, int *width, char *background_path, char *text1_menu1_path, char *text2_menu1_path);


//Menu de sélection du mode de jeu
void menu_2(int *mode_game);

//Remplissage manuel de la matrice
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
    Element inactive_ash
);

//Remplissage auto de la matrice
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
    Element inactive_ash
);


void menu_3(int *nb_tour, int *x_firstcase, int *y_firstcase);

void menu_4(int *nb_tour, int *x_firstcase, int *y_firstcase);

int isEmpty(struct Node* top);

void push(struct Node** top, Element data);

void pop(struct Node** top, Element* popped);


void game(Element **matrice, int length, int width);


void display_init(char *background_path, char *title_path, char *button_LG_path);