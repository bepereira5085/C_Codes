#ifndef B_TREE
#define B_TREE

#define DEGREE 6

typedef  struct Node
{
    int keys_amount;
    int keys[DEGREE - 1];
    struct Node *children[DEGREE];
    int is_leaf;
} Node;

Node *create_node(int is_leaf);
Node *insert_val(Node *root, int val);
Node *search_val(Node *root, int val);

void dealloc_tree(Node *root);
void insert_on_node(Node *node, int val);
void split_node(Node *parent, Node *left_node, int left_node_index);

void print_tree(Node *root);
void print_b_tree_lines(Node *node, char *prefix, int position);

#endif