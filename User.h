//
// Created by Bartek on 12/6/2024.
//

#ifndef USER_H
#define USER_H

#include "Vector.h"

typedef struct User User;

struct User {
    int id;
    Vector* movies;
    User* parent;
};

User init_user(unsigned int id, Vector* movies, User* parent);

#endif //USER_H
