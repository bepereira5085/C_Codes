#include <stdio.h>
#include <stdlib.h>
#include "b_tree.h"

#define MIN_DEGREE ((DEGREE + 1) / 2)
#define MIN_KEYS (MIN_DEGREE - 1)

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

Node *split_node(Node *parent, Node *left_node, int left_node_index) {
    int mid = MAX_KEYS / 2;

    Node *right_node = create_node(left_node->is_leaf);

    right_node->keys_amount = MAX_KEYS - mid - 1;

    for (int i = 0; i < right_node->keys_amount; i++) {
        right_node->elements[i] = left_node->elements[mid + 1 + i];
    }

    if (!left_node->is_leaf) {
        for (int i = 0; i <= right_node->keys_amount; i++) {
            right_node->children[i] = left_node->children[mid + 1 + i];
            left_node->children[mid + 1 + i] = NULL;
        }
    }

    left_node->keys_amount = mid;

    for (int i = parent->keys_amount; i > left_node_index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[left_node_index + 1] = right_node;

    for (int i = parent->keys_amount - 1; i >= left_node_index; i--) {
        parent->elements[i + 1] = parent->elements[i];
    }

    parent->elements[left_node_index] = left_node->elements[mid];
    parent->keys_amount++;

    return right_node;
}

void insert_on_node(Node *node, Element elem) {
    int i = node->keys_amount-1;
    if (node->is_leaf) {
        for (; i >= 0 && node->elements[i].matricula > elem.matricula; i--) {
            node->elements[i+1] = node->elements[i];
        }

        node->elements[i+1] = elem;
        node->keys_amount++;
    } else {
        while (i >= 0 && node->elements[i].matricula > elem.matricula) {
            i--;
        } i++;

        if (node->children[i] != NULL && node->children[i]->keys_amount == MAX_KEYS) {
            split_node(node, node->children[i], i);
            if (node->elements[i].matricula < elem.matricula) {
                i++;
            }
        }

        insert_on_node(node->children[i], elem);
    }
}

Node *insert_val(Node *root, Element elem) {
    if (root == NULL) {
        root = create_node(1);
        root->elements[0] = elem;
        root->keys_amount = 1;

        return root;
    }

    if (root->keys_amount == MAX_KEYS) {
        Node *new_root = create_node(0);
        new_root->children[0] = root;

        split_node(new_root, root, 0);

        insert_on_node(new_root, elem);

        return new_root;
    } else {
        insert_on_node(root, elem);
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

Element *search_val(Node *root, int matricula) {
    if (root == NULL) return NULL;

    for (int i = 0; i < root->keys_amount; i++) {
        if (root->elements[i].matricula == matricula) return &(root->elements[i]);
    }

    if (root->is_leaf) return NULL;

    for (int i = 0; i < root->keys_amount; i++) {
        if (root->elements[i].matricula > matricula) {
            return search_val(root->children[i], matricula);
        }
    }

    return search_val(root->children[root->keys_amount], matricula);
}

// Print functions (não testei as funções após a conversão de int pra Element)

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
        printf("%d", node->elements[i].matricula);
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