//
// Created by Bartek on 12/6/2024.
//
#include <stdint.h>

#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_STARTING_SIZE 10

typedef struct Vector {
    void* data;
    uint64_t data_size;
    int current_amount;
    int capacity;
} Vector;

Vector init_vector(uint64_t data_size);
void double_vector_size(Vector* vector);
void append_to_vector(Vector* vector, void* element);

#endif //VECTOR_H
