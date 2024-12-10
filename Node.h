//
// Created by Bartek on 12/10/2024.
//

#ifndef NODE_H
#define NODE_H

#include "Vector.h"

typedef struct Node Node;
typedef struct NodeVector NodeVector;

struct Node {
    int id;
    Node* left;
    Node* right;
    Vector* movies;
    Node* parent;
    NodeVector* children;
};

Node* init_node(int id);
void addUser(Node* root, int parent, int user);
Node* find_user(int id, Node* root);

struct NodeVector {
    Node** root;
    int length;
};

NodeVector* init_tree();
void append_to_tree(Node* root, Node* user);
void print_tree(Node* root);


#endif //NODE_H
