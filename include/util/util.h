#ifndef ___UTIL_H___
#define ___UTIL_H___

#define CREATE_TYPED_DYNARRAY(type) \
struct dynamic_array_##type \
{ \
    type *array; \
    size_t arr_length; \
    size_t e_size; \
    double grow_factor; \
}; \
typedef struct dynamic_array_##type dynamic_array_##type; \
void \
dynarray_##type##_init(dynamic_array_##type *arr, size_t init_size, double grow_factor) \
{ \
    if(arr == NULL) \
        return; \
    if((arr->array = calloc(init_size, sizeof(type))) == NULL) \
    { \
        fprintf(stderr, "Error on dynarray "#type" calloc(): %s\n", strerror(errno)); \
        exit(EXIT_FAILURE); \
    } \
    arr->e_size = sizeof(type); \
    arr->arr_length = init_size; \
    arr->grow_factor = grow_factor; \
} \
void \
dynarray_##type##_seti(dynamic_array_##type *arr, size_t index, type value) \
{ \
    arr->array[index] = value; \
} \
type \
dynarray_##type##_geti(dynamic_array_##type *arr, size_t index) \
{ \
    return arr->array[index]; \
} \
typedef struct dynamic_array_##type dynarray_##type


#endif
