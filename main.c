#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Node.h"

int main(void) {
    Node* root = init_node(0);

    char command[50];
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "addUser") == 0) {
            int parentId, userId;
            scanf("%d %d", &parentId, &userId);
            add_child(root, parentId, userId);
        } else if (strcmp(command, "delUser") == 0) {
            int userId;
            scanf("%d", &userId);
            delete_user(&root, userId);
        } else if (strcmp(command, "addMovie") == 0) {
            int userId, movieId;
            scanf("%d %d", &userId, &movieId);
            Node* user = find_user(userId, root);
            add_movie(user, movieId);
        } else if (strcmp(command, "delMovie") == 0) {
            int userId, movieId;
            scanf("%d %d", &userId, &movieId);
            Node* user = find_user(userId, root);
            remove_movie(user, movieId);
        } else if (strcmp(command, "printUserMovies") == 0) {
            int userId;
            scanf("%d", &userId);
            Node* user = find_user(userId, root);
            print_movies(user);
        } else if (strcmp(command, NULL) == 0) {
            break;
        }
    }

    free_node(root);
    return 0;
}