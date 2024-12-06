#include "Vector.h"

#include <stdlib.h>
#include <string.h>

Vector init_vector(uint64_t data_size) {
    void* data = malloc(data_size * VECTOR_STARTING_SIZE);
    Vector vector ={data, data_size, VECTOR_STARTING_SIZE, 0};
    return vector;
};

void double_vector_size(Vector* vector) {
    void* temp = realloc(vector->data, vector->capacity * vector->data_size * 2);
    //TODO dodac free jezeli valgrind wywali
    if (temp) {
        vector->data = temp;
        vector->capacity *= 2;
    }
}

void append_to_vector(Vector* vector, void* element) {
    if (vector->capacity <= vector->current_amount) {
        double_vector_size(vector);
    }

    memcpy((char*)vector->data + vector->data_size * vector->current_amount, element, vector->data_size);
    vector->current_amount++;
}