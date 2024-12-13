#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct User User;

struct User {
    int id;
    int parentId;
    User* parent;
    User** children;
    int childrenCount;
    int childrenCapacity;
    int* movies;
    int moviesCount;
    int moviesCapacity;
};

#define INITIAL_LIST_CAPACITY 10

User* createUser(int id, User* parent);
void freeUser(User* user);
User* findUser(User* root, int userId);
void addUser(User* root, int parentId, int userId);
void delUser(User* root, int userId);
void addMovie(User* root, int userId, int movie);
void delMovie(User* root, int userId, int movie);
void printUserMovies(User* root, int userId);

int compareInts(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


int main(void) {
    User* root = createUser(0, NULL);

    char command[50];
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "addUser") == 0) {
            int parentId, userId;
            scanf("%d %d", &parentId, &userId);
            addUser(root, parentId, userId);
        } else if (strcmp(command, "delUser") == 0) {
            int userId;
            scanf("%d", &userId);
            delUser(root, userId);
        } else if (strcmp(command, "addMovie") == 0) {
            int userId, movieId;
            scanf("%d %d", &userId, &movieId);
            addMovie(root, userId, movieId);
        } else if (strcmp(command, "delMovie") == 0) {
            int userId, movieId;
            scanf("%d %d", &userId, &movieId);
            delMovie(root, userId, movieId);
        } else if (strcmp(command, "printUserMovies") == 0) {
            int userId;
            scanf("%d", &userId);
            printUserMovies(root, userId);
        }
    }

    freeUser(root);
    return 0;
}


User* createUser(int id, User* parent) {
    User* user = (User*)malloc(sizeof(User));
    memset(user, 0, sizeof(User));
    if (!user) {
        printf("User creation failed");
        exit(1);
    }
    user->id = id;
    user->parentId = parent ? parent->id : -1;
    user->parent = parent;
    user->children = (User**)malloc(sizeof(User*) * INITIAL_LIST_CAPACITY);
    user->childrenCount = 0;
    user->childrenCapacity = INITIAL_LIST_CAPACITY;
    user->movies = (int*)malloc(sizeof(int) * INITIAL_LIST_CAPACITY);
    user->moviesCount = 0;
    user->moviesCapacity = INITIAL_LIST_CAPACITY;

    return user;
}

void freeUser(User* user) {
    for (int i = 0; i < user->childrenCount; i++) {
        freeUser(user->children[i]);
    }
    free(user->children);
    free(user->movies);
    free(user);
}

User* findUser(User* root, int userId) {
    if (root->id == userId) {
        return root;
    }
    for (int i = 0; i < root->childrenCount; i++) {
        User* found = findUser(root->children[i], userId);
        if (found) {
            return found;
        }
    }
    return NULL;
}

void addUser(User* root, int parentId, int userId) {
    User* parent = findUser(root, parentId);
    if (!parent || findUser(root, userId)) {
        printf("ERROR\n");
        return;
    }

    if (parent->childrenCount >= parent->childrenCapacity) {
        parent->childrenCapacity *= 2;
        parent->children = (User**)realloc(parent->children, sizeof(User*) * parent->childrenCapacity);
        if (!parent->children) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    User* user = createUser(userId, parent);
    parent->children[parent->childrenCount++] = user;
    printf("OK\n");
}

void delUser(User* root, int userId) {
    if (userId ==0) {
        printf("ERROR\n");
        return;
    }

    User* user = findUser(root, userId);
    if(!user) {
        printf("ERROR\n");
        return;
    }

    User* parent = user->parent;

    while (parent->childrenCount + user->childrenCount > parent->childrenCapacity) {
        parent->childrenCapacity *= 2;
        parent->children = (User**)realloc(parent->children, sizeof(User*) * parent->childrenCapacity);
        if (!parent->children) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    for (int i = 0; i < user->childrenCount; i++) {
        user->children[i]->parent = parent;
        parent->children[parent->childrenCount++] = user->children[i];
    }

    for (int i = 0; i < parent->childrenCount; i++) {
        if (parent->children[i]->id == userId) {
            memmove(&parent->children[i], &parent->children[i + 1],
                    (parent->childrenCount - i - 1) * sizeof(User*));
            parent->childrenCount--;
            break;
        }
    }

    free(user->children);
    free(user->movies);
    free(user);

    printf("OK\n");
}

void addMovie(User* root, int userId, int movie) {
    User* user = findUser(root, userId);

    if(!user) {
        printf("ERROR\n");
        return;
    }

    for (int i = 0; i < user->moviesCount; i++) {
        if (user->movies[i] == movie) {
            printf("ERROR\n");
            return;
        }
    }

    if (user->moviesCount >= user->moviesCapacity) {
        user->moviesCapacity *= 2;
        user->movies = (int*)realloc(user->movies, sizeof(int) * user->moviesCapacity);
        if (!user->movies) {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }


    int i;
    for (i = user->moviesCount - 1; i >= 0 && user->movies[i] > movie; i--) {
        user->movies[i + 1] = user->movies[i];
    }
    user->movies[i + 1] = movie;
    user->moviesCount++;

    printf("OK\n");
}

void delMovie(User* root, int userId, int movie) {
    User* user = findUser(root, userId);

    if(!user) {
        printf("ERROR\n");
        return;
    }

    for (int i = 0; i < user->moviesCount; i++) {
        if (user->movies[i] == movie) {
            memmove(&user->movies[i], &user->movies[i+1], (user->moviesCount - i - 1) * sizeof(int));
            user->moviesCount--;
            printf("OK\n");
            return;
        }
    }

    printf("ERROR\n");
}

void printUserMovies(User* root, int userId) {
    User* user = findUser(root, userId);
    if (!user) {
        printf("ERROR\n");
        return;
    }

    User* parent = user->parent;

    if (!parent) {
        for (int i = 0; i < user->moviesCount; i++) {
            printf("%d ", user->movies[i]);
        }
        printf("\n");
        return;
    }

    if ((parent->moviesCount + user->moviesCount) == 0) {
        printf("\n");
        return;
    }

    int userIndex = 0;
    int parentIndex = 0;

    while (userIndex < user->moviesCount && parentIndex < parent->moviesCount) {
        if (user->movies[userIndex] < parent->movies[parentIndex]) {
            printf("%d ", user->movies[userIndex++]);
        } else if (user->movies[userIndex] > parent->movies[parentIndex]) {
            printf("%d ", parent->movies[parentIndex++]);
        } else {
            printf("%d ", user->movies[userIndex++]);
            parentIndex++;
        }
    }
    while (userIndex < user->moviesCount) printf("%d ", user->movies[userIndex++]);
    while (parentIndex < parent->moviesCount) printf("%d ", parent->movies[parentIndex++]);
    printf("\n");
}