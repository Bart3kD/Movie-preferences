#include "Node.h"
#include "Vector.h"

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
    node->parent = NULL;
    node->children = NULL;
    node->movies = init_vector();

    return node;
}

NodeVector* init_node_vector() {
    NodeVector* vector = (NodeVector*)malloc(sizeof(NodeVector));
    if (!vector) {
        printf("Failed to allocate memory for node vector");
        return NULL;
    }

    vector->nodes = (Node**)malloc(sizeof(Node*) * VECTOR_STARTING_SIZE);
    if (!vector->nodes) {
        free(vector);
        printf("Failed to allocate memory for node vector data");
        return NULL;
    }

    vector->length = 0;
    vector->capacity = VECTOR_STARTING_SIZE;
    return vector;
}

void add_child(Node* parent, Node* child) {
    if (!parent || !child) {
        printf("Invalid input for add_child");
        return;
    }


    if (!parent->children) {
        parent->children = init_node_vector();
        if (!parent->children) {
            printf("Failed to allocate memory for children");
            return;
        }
    }

    NodeVector* children = parent->children;

    if (children->length >= children->capacity) {
        int new_capacity = children->capacity * 2;
        Node** temp = (Node**)realloc(children->nodes, sizeof(Node*) * new_capacity);
        if (!temp) {
            printf("Failed to double the children vector capacity");
            return;
        }
        children->nodes = temp;
        children->capacity = new_capacity;
    }

    children->nodes[children->length] = child;
    children->length++;

    child->parent = parent;
}

void add_movie(Node* user, int movie) {
    if (!user) {
        printf("Invalid user\n");
        return;
    }

    int* movies = user->movies.data;
    int i = user->movies.current_amount - 1;

    while (i >= 0 && movies[i] > movie) {
        movies[i + 1] = movies[i];
        i--;
    }

    movies[i + 1] = movie;
    user->movies.current_amount++;
}

Vector merge_movies(Node* user, Node* parent) {
    Vector result = init_vector();
    Vector* user_movies = &user->movies;
    Vector* parent_movies = &parent->movies;

    int user_index = 0, parent_index = 0;

    while (user_index < user_movies->current_amount && parent_index < parent_movies->current_amount) {
        int* user_data = user_movies->data;
        int* parent_data = parent_movies->data;

        if (user_data[user_index] < parent_data[parent_index]) {
            append_to_vector(&result, user_data[user_index]);
            user_index++;
        } else {
            append_to_vector(&result, parent_data[parent_index]);
            parent_index++;
        }
    }

    while (user_index < user_movies->current_amount) {
        int* user_data = (int*)user_movies->data;
        append_to_vector(&result, user_data[user_index]);
        user_index++;
    }

    while (parent_index < parent_movies->current_amount) {
        int* parent_data = (int*)parent_movies->data;
        append_to_vector(&result, parent_data[parent_index]);
        parent_index++;
    }

    return result;
}


void remove_movie(Node* user, int movie) {
    if (!user || user->movies.current_amount == 0) {
        printf("ERROR");
        return;
    }

    int* movies = (int*)user->movies.data;
    int found = 0;

    for (int i = 0; i < user->movies.current_amount; i++) {
        if (movies[i] == movie) {
            found = 1;
            for (int j = i; j < user->movies.current_amount - 1; j++) {
                movies[j] = movies[j + 1];
            }
            user->movies.current_amount--;
            break;
        }
    }

    if (!found) {
        printf("Movie %d not found for user %d.\n", movie, user->id);
    } else {
        printf("Movie %d removed for user %d.\n", movie, user->id);
    }
}

void print_movies(Node* user) {
    if (!user) {
        printf("ERROR\n");
        return;
    }

    if (user->movies.current_amount == 0) {
        printf("User %d has no movies.\n", user->id);
        return;
    }

    Node* parent = user->parent;

    if (!parent) {
        printf("User %d has no parent.\n", user->id);
    }

    Vector merged_movies = merge_movies(user, parent);

    if (merged_movies.current_amount == 0) {
        printf("No movies to display.\n");
        free_vector(&merged_movies);
        return;
    }

    for (int i = 0; i < merged_movies.current_amount; i++) {
        printf("%d ", ((int*)merged_movies.data)[i]);
    }

    printf("\n");
    free_vector(&merged_movies);
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

Node* find_min(Node* node) {
    Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* delete_node(Node* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = find_min(root->right);
        root->id = temp->id;
        root->right = delete_node(root->right, temp->id);
    }

    return root;
}


void delete_user(Node** root, int userID) {
    if (userID == 0) {
        printf("ERROR\n");
        return;
    }

    Node* user = find_user(*root, userID);
    if (user == NULL) {
        printf("ERROR\n");
        return;
    }


    if (user->children != NULL) {
        for (int i = 0; i < user->children->length; i++) {
            Node* child = user->children->nodes[i];
            child->parent = user->parent;


            if (user->parent) {
                add_child(user->parent, child);
            }
        }
    }

    *root = delete_node(*root, userID);

    if (find_user(*root, userID) == NULL) {
        printf("OK\n");
    } else {
        printf("ERROR\n");
    }
}

// CLEAN UP
void free_node_vector(NodeVector* vector) {
    if (!vector) return;

    free(vector->nodes);
    free(vector);
}

void free_node(Node* node) {
    if (!node) return;

    if (node->children) {
        for (int i = 0; i < node->children->length; i++) {
            free_node(node->children->nodes[i]);
        }
        free_node_vector(node->children);
    }

    free(node);
}
