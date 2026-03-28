#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

int main() {
    Node *root = NULL;

    int i = 0;

    root = insert_val(root, 10);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 20);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 30);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 40);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 50);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 60);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 70);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 80);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 90);
    print_tree(root);
    printf("\n");
    root = insert_val(root, 100);
    print_tree(root);
    printf("\n");

    print_tree(root);

    dealloc_tree(root);

    return 0;
}