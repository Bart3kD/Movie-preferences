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

void add_child(Node* root, int parentID, int userID) {
    if (!root) {
        printf("ERROR\n");
        return;
    }

    Node* parent = find_user(parentID, root);
    if (!parent) {
        printf("ERROR\n");
        return;
    }

    if (find_user(userID, root)) {
        printf("ERROR\n");
        return;
    }

    Node* user = init_node(userID);
    if (!user) {
        printf("ERROR: Failed to create user node\n");
        return;
    }

    append_to_tree(root, user);

    if (!parent->children) {
        parent->children = init_node_vector();
        if (!parent->children) {
            printf("ERROR: Failed to initialize children vector for parent ID %d\n", parentID);
            free_node(user);
            return;
        }
    }

    NodeVector* children = parent->children;
    if (children->length >= children->capacity) {
        int new_capacity = children->capacity * 2;
        Node** temp = realloc(children->nodes, sizeof(Node*) * new_capacity);
        if (!temp) {
            printf("ERROR: Failed to expand children vector\n");
            free_node(user);
            return;
        }
        children->nodes = temp;
        children->capacity = new_capacity;
    }

    children->nodes[children->length] = user;
    children->length++;

    user->parent = parent;

    printf("OK\n");
}

void add_existing_child(Node* parent, Node* child) {
    if (!parent || !child) return;

    if (!parent->children) {
        parent->children = malloc(sizeof(NodeVector));
        parent->children->nodes = malloc(sizeof(Node*) * 2); // Initial capacity
        parent->children->capacity = 2;
        parent->children->length = 0;
    }

    // Resize if necessary
    if (parent->children->length == parent->children->capacity) {
        parent->children->capacity *= 2;
        parent->children->nodes = realloc(parent->children->nodes, parent->children->capacity * sizeof(Node*));
    }

    // Add the child
    parent->children->nodes[parent->children->length++] = child;
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

    printf("OK\n");
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
            if (result.current_amount == 0 || result.data[result.current_amount - 1] != user_data[user_index]) {
                append_to_vector(&result, user_data[user_index]);
            }
            user_index++;
        } else if (user_data[user_index] > parent_data[parent_index]) {
            if (result.current_amount == 0 || result.data[result.current_amount - 1] != parent_data[parent_index]) {
                append_to_vector(&result, parent_data[parent_index]);
            }
            parent_index++;
        } else {
            // Both are equal, add only once
            if (result.current_amount == 0 || result.data[result.current_amount - 1] != user_data[user_index]) {
                append_to_vector(&result, user_data[user_index]);
            }
            user_index++;
            parent_index++;
        }
    }

    while (user_index < user_movies->current_amount) {
        int* user_data = user_movies->data;
        if (result.current_amount == 0 || result.data[result.current_amount - 1] != user_data[user_index]) {
            append_to_vector(&result, user_data[user_index]);
        }
        user_index++;
    }

    while (parent_index < parent_movies->current_amount) {
        int* parent_data = parent_movies->data;
        if (result.current_amount == 0 || result.data[result.current_amount - 1] != parent_data[parent_index]) {
            append_to_vector(&result, parent_data[parent_index]);
        }
        parent_index++;
    }

    return result;
}



void remove_movie(Node* user, int movie) {
    if (!user || user->movies.current_amount == 0) {
        printf("ERROR\n");
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
        printf("ERROR\n");
    } else {
        printf("OK\n");
    }
}

void print_movies(Node* user) {
    if (!user) {
        printf("ERROR\n");
        return;
    }

    if (user->movies.current_amount == 0 && (!user->parent || user->parent->movies.current_amount == 0)) {
        printf("\n");
        return;
    }

    Node* parent = user->parent;

    // Merge movies from the user and their new parent
    Vector merged_movies = init_vector();
    if (parent) {
        merged_movies = merge_movies(user, parent);
    } else {
        // Only the user's movies
        merged_movies = user->movies;
    }

    if (merged_movies.current_amount == 0) {
        printf("\n");
        free_vector(&merged_movies);
        return;
    }

    for (int i = 0; i < merged_movies.current_amount; i++) {
        printf("%d ", ((int*)merged_movies.data)[i]);
    }

    printf("\n");

    if (parent) {
        free_vector(&merged_movies);
    }
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
        return NULL;
    }

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        // Node to be deleted found
        if (root->left == NULL) {
            Node* temp = root->right;
            root->right = NULL;  // Avoid recursive free
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            root->left = NULL;  // Avoid recursive free
            return temp;
        }

        // Node with two children
        Node* temp = find_min(root->right);
        root->id = temp->id;
        root->right = delete_node(root->right, temp->id);
    }

    return root;
}


void delete_user(Node** root, int userID) {
    if (!root || !(*root)) {
        printf("ERROR\n");
        return;
    }

    Node* user = find_user(userID, *root);
    if (!user) {
        printf("ERROR\n");
        return;
    }

    Node* parent = user->parent;

    // Reassign children to parent
    if (user->children) {
        for (int i = 0; i < user->children->length; i++) {
            Node* child = user->children->nodes[i];
            child->parent = parent;
            if (parent) {
                add_existing_child(parent, child);
            } else {
                child->parent = NULL;
            }
        }
    }

    // Remove from parent's children vector
    if (parent && parent->children) {
        NodeVector* siblings = parent->children;
        for (int i = 0; i < siblings->length; i++) {
            if (siblings->nodes[i] == user) {
                for (int j = i; j < siblings->length - 1; j++) {
                    siblings->nodes[j] = siblings->nodes[j + 1];
                }
                siblings->length--;
                break;
            }
        }
    }

    // Free the user's resources and remove it from the tree
    free_node(user);
    *root = delete_node(*root, userID);  // This removes the node from the tree without re-freeing it.

    printf("OK\n");
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
