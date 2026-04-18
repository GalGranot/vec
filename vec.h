#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdlib.h>

#define VEC_INITIAL_CAPACITY 4

#define VEC_IMPL(T, Name) \
typedef struct { \
    T *data; \
    size_t capacity; \
} Name##Slice; \
\
typedef struct { \
    Name##Slice slice; \
    size_t len; \
} Name; \
\
static inline Name Name##_new(void) { \
    return (Name){ \
        .slice = (Name##Slice){ .data = NULL, .capacity = 0 }, \
        .len = 0 \
    }; \
} \
\
static inline void Name##_initial_alloc(Name *vec) { \
    vec->slice.data = malloc(VEC_INITIAL_CAPACITY * sizeof(T)); \
    vec->slice.capacity = VEC_INITIAL_CAPACITY; \
} \
\
static inline void Name##_double_capacity(Name *vec) { \
    size_t new_capacity = vec->slice.capacity * 2; \
    void *new_data = realloc(vec->slice.data, new_capacity * sizeof(T)); \
    vec->slice.data = new_data; \
    vec->slice.capacity = new_capacity; \
} \
\
static inline void Name##_push(Name *vec, T value) { \
    if (!vec->slice.data) { \
        Name##_initial_alloc(vec); \
    } else if (vec->len == vec->slice.capacity) { \
        Name##_double_capacity(vec); \
    } \
    vec->slice.data[vec->len++] = value; \
} \
\
static inline T Name##_get(const Name *vec, size_t i) { \
    return vec->slice.data[i]; \
} \
\
static inline void Name##_free(Name *vec) { \
    free(vec->slice.data); \
    vec->slice.data = NULL; \
    vec->slice.capacity = 0; \
    vec->len = 0; \
}

typedef struct {
  int *data;
  size_t capacity;
} IntVecSlice;

typedef struct {
  IntVecSlice slice;
  size_t len;
} IntVec;

static inline IntVec IntVec_new(void) {
  return (IntVec){.slice = (IntVecSlice){.data = ((void *)0), .capacity = 0},
                  .len = 0};
}

static inline void IntVec_initial_alloc(IntVec *vec) {
  vec->slice.data = malloc(4 * sizeof(int));
  vec->slice.capacity = 4;
}

static inline void IntVec_double_capacity(IntVec *vec) {
  size_t new_capacity = vec->slice.capacity * 2;
  void *new_data = realloc(vec->slice.data, new_capacity * sizeof(int));
  vec->slice.data = new_data;
  vec->slice.capacity = new_capacity;
}

static inline void IntVec_push(IntVec *vec, int value) {
  if (!vec->slice.data) {
    IntVec_initial_alloc(vec);
  } else if (vec->len == vec->slice.capacity) {
    IntVec_double_capacity(vec);
  }
  vec->slice.data[vec->len++] = value;
}

static inline int IntVec_get(const IntVec *vec, size_t i) {
  return vec->slice.data[i];
}

static inline void IntVec_free(IntVec *vec) {
  free(vec->slice.data);
  vec->slice.data = ((void *)0);
  vec->slice.capacity = 0;
  vec->len = 0;
}

#endif // VEC_H