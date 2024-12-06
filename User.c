#include "User.h"

User init_user(unsigned int id, Vector* movies, User* parent) {
    User user = {id, movies, parent};
    return  user;
};