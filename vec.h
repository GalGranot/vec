#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdlib.h>

#define VEC_INITIAL_CAPACITY 4

typedef struct {
    int *data;
    size_t capacity;
} IntSlice;

typedef struct {
    IntSlice slice;
    size_t len;
} IntVec;

static inline void int_vec_double_capacity(IntVec *vec) {
    size_t new_capacity = vec->slice.capacity * 2;
    void *new_data = realloc(vec->slice.data, new_capacity * sizeof(int));
    *vec = (IntVec) {
        .slice = (IntSlice) { .data = new_data, .capacity = new_capacity },
        .len = vec->len,
    };
}

static inline void int_vec_initial_alloc(IntVec *vec) {
    vec->slice = (IntSlice) { 
        .data = malloc(VEC_INITIAL_CAPACITY * sizeof(int)),
        .capacity = VEC_INITIAL_CAPACITY,
    };
}

static inline IntVec int_vec_new(void) {
    return (IntVec) {
        .slice = (IntSlice) { .data = NULL, .capacity = 0, },
        .len = 0,
    };
}

static inline void int_vec_push(IntVec *vec, int value) {
    if(!vec->slice.data) {
        int_vec_initial_alloc(vec);
    } else if(vec->len == vec->slice.capacity) {
        int_vec_double_capacity(vec);
    }
    vec->slice.data[vec->len] = value;
    vec->len += 1;
}

static inline int int_vec_get(const IntVec *vec, size_t i) {
    return vec->slice.data[i];
}

static inline void int_vec_free(IntVec *vec) {
    free(vec->slice.data);
}

#endif // VEC_H