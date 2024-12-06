#include <stdio.h>
#include <stdlib.h>
#include "User.h"
#include "Vector.h"

User init_user_2(Vector* vector, uint64_t data_size, Vector* movies, User* parent) {
    User user = init_user(data_size, movies, parent);
    printf("Init user arrived here\n");
    append_to_vector(vector, &user);
    printf("Init user arrived here 2\n");
    return user;
}

void append_movie(unsigned long user_id, int movie) {

};

int main(void)
{
    Vector users = init_vector(sizeof(User*));

    Vector movies = init_vector(sizeof(int));
    Vector movies2 = init_vector(sizeof(int));
    printf("Arrived here\n ");
    User root = init_user_2(&users, 0, &movies, NULL);
    User child1 = init_user_2(&users,1, &movies2, &root);
    printf("Arrived here 2\n ");
    for (int i = 0; i <= users.current_amount; i++) {
        printf("%p",(User*)&users.data[i * users.data_size]);
    }

    printf("%d\n", child1.parent->id);
}
