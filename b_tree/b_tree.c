#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

#define MAX_KEYS (DEGREE-1)
#define MIN_KEYS (MAX_KEYS/2)

Node *create_node(int is_leaf) {
    Node *p = (Node *)calloc(1, sizeof(Node));
    if (p == NULL) {
        printf("Erro ao alocar a memoria");
        exit(1);
    }

    p->is_leaf = is_leaf;
    p->keys_amount = 0;

    for (int i = 0; i < DEGREE; i++) p->children[i] = NULL;

    return p;
}

void split_node(Node *parent, Node *left_node, int left_node_index) {
    Node *right_node = (Node *)calloc(1, sizeof(Node));
    right_node->keys_amount = MIN_KEYS;
    right_node->is_leaf = left_node->is_leaf;

    for (int i = 0; i < MIN_KEYS; i++) {
        right_node->keys[i] = left_node->keys[MIN_KEYS + 1 + i];
    }

    if (!left_node->is_leaf) {
        for (int i = 0; i < MIN_KEYS + 1; i++) {
            right_node->children[i] = left_node->children[MIN_KEYS + 1 + i];
        }
    }

    left_node->keys_amount = MIN_KEYS;
    for (int i = parent->keys_amount; i >= left_node_index + 1; i--) {
        parent->children[i+1] = parent->children[i];
    }
    parent->children[left_node_index + 1] = right_node;

    for (int i = parent->keys_amount - 1; i >= left_node_index; i--) {
        parent->keys[i+1] = parent->keys[i];
    }
    parent->keys[left_node_index] = left_node->keys[MIN_KEYS];
    parent->keys_amount++;
}

void insert_on_node(Node *node, int val) {
    int i = node->keys_amount-1;
    if (node->is_leaf) {
        for (; i >= 0 && node->keys[i] > val; i--) {
            node->keys[i+1] = node->keys[i];
        }

        node->keys[i+1] = val;
        node->keys_amount++;
    } else {
        while (i >= 0 && node->keys[i] > val) {
            i--;
        } i++;

        if (node->children[i]->keys_amount == MAX_KEYS) {
            split_node(node, node->children[i], i);
            if (node->keys[i] < val) {
                i++;
            }
        }

        insert_on_node(node->children[i], val);
    }
}

Node *insert_val(Node *root, int val) {
    if (root == NULL) {
        root = create_node(1);
        root->keys[0] = val;
        root->keys_amount = 1;

        return root;
    }

    if (root->keys_amount == MAX_KEYS) {
        Node *new_root = create_node(0);
        new_root->children[0] = root;

        split_node(new_root, root, 0);
        insert_on_node(new_root, val);

        return new_root;
    } else {
        insert_on_node(root, val);
        return root;
    }
}

void dealloc_tree(Node *root) {
    if (root != NULL) {
        if (!root->is_leaf) {
            for (int i = 0; i <= root->keys_amount; i++) {
                dealloc_tree(root->children[i]);
            }
        }
        free(root);
    }
}

// Print functions

void print_b_tree_lines(Node *node, char *prefix, int position) {
    if (node == NULL) return;

    char new_prefix[256];
    int num_children = node->keys_amount + 1;
    int mid = num_children / 2;

    if (!node->is_leaf) {
        for (int i = num_children - 1; i >= mid; i--) {
            int is_topmost = (i == num_children - 1);
            int child_pos = is_topmost ? 1 : 3;

            sprintf(new_prefix, "%s%s", prefix, (position == 2 || position == 4) ? "|       " : "        ");
            print_b_tree_lines(node->children[i], new_prefix, child_pos);
        }
    }

    printf("%s", prefix);
    if (position == 0) printf("--- ");
    else if (position == 1) printf("/-- ");
    else if (position == 2) printf("\\-- ");
    else printf("|-- ");

    printf("[");
    for (int i = 0; i < node->keys_amount; i++) {
        printf("%d", node->keys[i]);
        if (i < node->keys_amount - 1) printf(", ");
    }
    printf("]\n");

    if (!node->is_leaf) {
        for (int i = mid - 1; i >= 0; i--) {
            int is_bottommost = (i == 0);
            int child_pos = is_bottommost ? 2 : 4;

            sprintf(new_prefix, "%s%s", prefix, (position == 1 || position == 3) ? "|       " : "        ");
            print_b_tree_lines(node->children[i], new_prefix, child_pos);
        }
    }
}

void print_tree(Node *root) {
    if (root == NULL) {
        printf("A arvore esta vazia.\n");
    } else {
        print_b_tree_lines(root, "", 0);
    }
}