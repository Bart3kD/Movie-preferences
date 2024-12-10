#include "Vector.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Vector init_vector() {
    void* data = malloc(sizeof(int) * VECTOR_STARTING_SIZE);
    if (!data) {
        printf("Failed to allocate memory for vector\n");
        exit(EXIT_FAILURE);
    }
    Vector vector = {data, 0, VECTOR_STARTING_SIZE};
    return vector;
}

void double_vector_size(Vector* vector) {
    void* temp = realloc(vector->data, vector->capacity * sizeof(int) * 2);
    if (!temp) {
        printf("Failed to allocate memory while resizing vector\n");
        exit(EXIT_FAILURE);
    }
    vector->data = temp;
    vector->capacity *= 2;
}

void free_vector(Vector* vector) {
    free(vector->data);
    vector->data = NULL;
    vector->current_amount = 0;
    vector->capacity = 0;
}


void append_to_vector(Vector* vector, int element) {
    if (vector->current_amount >= vector->capacity) {
        double_vector_size(vector);
    }
    ((int*)vector->data)[vector->current_amount] = element;
    vector->current_amount++;
}
