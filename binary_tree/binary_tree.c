#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

Node *create_node(int val) {
    Node *p = (Node *)calloc(1, sizeof(Node));
    if (p == NULL) {
        printf("Erro ao alocar o nó na memória");
        exit(1);
    }

    p->value = val;
    p->left = NULL;
    p->right = NULL;

    return p;
}

Node *insert_node(int val, Node *root) {
    if (root == NULL) return create_node(val);

    if (root->value > val ) {
        root->left = insert_node(val, root->left);
    } else if (root->value < val ) {
        root->right = insert_node(val, root->right);
    }

    return root;
}

Node *search_value(Node *root, int val) {
    if (root == NULL || root->value == val) return root;

    if (root->value > val)  {
        return search_value(root->left, val);
    }

    return search_value(root->right, val);
}

void dealloc_tree(Node *root) {
    if (root != NULL) {
        dealloc_tree(root->left);
        dealloc_tree(root->right);
        free(root);
    }
}

Node *findMinOfRightTree(Node *root) {
    if (root->left != NULL) {
        return findMinOfRightTree(root->left);
    }

    return root;
}

Node *delete_val(Node *root, int val) {
    Node *aux = NULL;
    if (root == NULL) return root;

    if (val < root->value) {
        root->left = delete_val(root->left, val);
    } else if (val > root->value) {
        root->right = delete_val(root->right, val);
    } else {
        if (root->left == NULL) {
            aux = root->right;
            free(root);
            return aux;
        } else if (root->right == NULL) {
            aux = root->left;
            free(root);
            return aux;
        }

        aux = findMinOfRightTree(root->right);
        root->value = aux->value;

        root->right = delete_val(root->right, aux->value);
    }

    return root;
}

// Print Functions

void print_tree_lines(Node *root, char *prefix, int is_left) {
    if (root == NULL) return;

    char new_prefix[256];

    if (root->right != NULL) {
        sprintf(new_prefix, "%s%s", prefix, is_left == 1 ? "|   " : "    ");
        print_tree_lines(root->right, new_prefix, 0);
    }

    printf("%s", prefix);
    if (is_left == 0) {
        printf("/-- ");
    } else if (is_left == 1) {
        printf("\\-- ");
    } else {
        printf("--- ");
    }
    printf("%d\n", root->value);

    if (root->left != NULL) {
        sprintf(new_prefix, "%s%s", prefix, is_left == 0 ? "|   " : "    ");
        print_tree_lines(root->left, new_prefix, 1);
    }
}

void print_tree(Node *root, int padding) {
    printf("\n");
    print_tree_lines(root, "", 2);
    printf("\n");
}