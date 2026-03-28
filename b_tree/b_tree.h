#ifndef B_TREE_H
#define B_TREE_H

#define DEGREE 5
#define MAX_KEYS (DEGREE - 1)

typedef struct {
    int matricula;
    char nome[50];
    char telefone[20];
} Register;

typedef struct {
    int matricula;
    long offset;
} Element;

typedef struct Node {
    int keys_amount;
    Element elements[MAX_KEYS];
    struct Node *children[DEGREE];
    int is_leaf;
} Node;

Node *create_node(int is_leaf);
Node *insert_val(Node *root, Element el);
void insert_on_node(Node *node, Element el);
Node *split_node(Node *parent, Node *left_node, int left_node_index);
Element *search_val(Node *root, int matricula);
void dealloc_tree(Node *root);

void menu(Node **root, char *arq_dados, char *arq_arvore);
void register_student(Node **root, char *arq_dados);
void search_student(Node *root, char *arq_dados);
void save_tree(Node *root, char *arq_arvore);
Node *load_initial_file(char *arq_dados);

#endif