#ifndef BINARY_TREE
#define BINARY_TREE

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(int val);
Node *insert_node(int val, Node *root);
Node *search_value(Node *root, int val);
Node *findMinOfRightTree(Node *root);
Node *delete_val(Node *root, int val);
void dealloc_tree(Node *root);

void print_node(int val, int padding);
void print_tree(Node *root, int padding);

#endif