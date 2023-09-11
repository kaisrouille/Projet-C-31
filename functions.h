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

void generate_matrice(int length, int width);

void free_matrice(Element matrice);

void display_matrice(Element matrice);


int isEmpty(struct Node* top);

void push(struct Node** top, Element data);

void pop(struct Node** top, Element* popped);