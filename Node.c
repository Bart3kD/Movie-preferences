#include "Node.h"

#include <stdio.h>
#include <stdlib.h>

Node* init_node(int id) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->id = id;
    node->left = NULL;
    node->right = NULL;
    node->movies = NULL;
    node->parent = NULL;
    node->children = NULL;
    return node;
}

void addUser(Node* root, int parent, int user) {
    Node* parent_node = find_user(parent, root);
    Node* new_user = init_node(user);
    parent_node->children
}

NodeVector* init_tree() {
    NodeVector* tree = (struct NodeVector*)malloc(sizeof(NodeVector));
    tree->length = 0;
    tree->root = NULL;
    return tree;
}

void append_to_tree(Node* root, Node* user) {
    if (root == NULL || user == NULL || user->id == root->id ) {
        return;
    }

    if (user->id < root->id) {
        if (root->left == NULL) {
            root->left = user;
        }else {
            append_to_tree(root->left, user);
        }
    } else {
        if (root->right == NULL) {
            root->right= user;
        }
        else {
            append_to_tree(root->right, user);
        }
    }
}

Node* find_user(int id, Node* root) {
    if (root == NULL) {
        return NULL;
    }

    if (root->id == id) {
        return root;
    }

    if (id < root->id) {
        return find_user(id, root->left);
    }

    return find_user(id, root->right);
}

void print_tree(Node* root) {
    if (root == NULL) {
        return;
    }
    print_tree(root->left);
    printf("%d ", root->id);
    print_tree(root->right);
}
