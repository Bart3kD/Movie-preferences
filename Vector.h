#include <stdint.h>

#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_STARTING_SIZE 10

typedef struct Vector {
    int* data;
    int current_amount;
    int capacity;
} Vector;

Vector init_vector();
void double_vector_size(Vector* vector);
void append_to_vector(Vector* vector, int element);
void free_vector(Vector* vector);


#endif //VECTOR_H
