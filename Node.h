//
// Created by Bartek on 12/10/2024.
//

#ifndef NODE_H
#define NODE_H

#define VECTOR_STARTING_SIZE 10

#include "Vector.h"

typedef struct Node Node;
typedef struct NodeVector NodeVector;

struct Node {
    int id;
    Node* left;
    Node* right;
    Vector movies;
    Node* parent;
    NodeVector* children;
};


Node* init_node(int id);
Node* find_min(Node* node);
Node* delete_node(Node* root, int id);
Node* find_user(int id, Node* root);
void add_movie(Node* user, int movie);
void remove_movie(Node* user, int movie);
Vector merge_movies(Node* user, Node* parent);
void print_movies(Node* user);

struct NodeVector {
    Node** nodes;
    int length;
    int capacity;
};


NodeVector* init_tree();
void add_child(Node* parent, Node* child);
void append_to_tree(Node* root, Node* user);
void print_tree(Node* root);
void delete_user(Node** root, int userID);
void free_node_vector(NodeVector* vector);
void free_node(Node* node);


#endif //NODE_H
