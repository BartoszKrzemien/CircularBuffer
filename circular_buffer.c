#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N < 1) {
        return 1;
    }
    int *buffer = malloc(N * sizeof(int));
    if (buffer == NULL) {
        return 2;
    }
    a->ptr = buffer;
    a->capacity = N;
    a->end = 0;
    a->begin = 0;
    a->full = 0;
    return 0;

}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N < 1) {
        return 1;
    }
    struct circular_buffer_t *buffer = malloc(sizeof(struct circular_buffer_t));
    if (buffer == NULL) {
        return 2;
    }
    int result = circular_buffer_create(buffer, N);
    if (result == 2) {
        free(buffer);
        return 2;
    }
    *cb = buffer;
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a == NULL) {
        return;
    }
    free(a->ptr);
    a->ptr = NULL;
    a->begin = 0;
    a->end = 0;
    a->capacity = 0;
    a->full = 0;
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a) {
    if (a == NULL) {
        return;
    }
    struct circular_buffer_t *buffer = *a;
    if (buffer != NULL) {
        circular_buffer_destroy(buffer);
    }
    free(*a);
    *a = NULL;
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL || cb->capacity <= 0 || cb->ptr == NULL || cb->end < 0 || cb->begin < 0 || cb->end > cb->capacity || cb->begin > cb->capacity) {
        return 1;
    }

    if(circular_buffer_full(cb)){
        cb->begin++;
        if(cb->begin == cb->capacity){
            cb->begin = 0;
        }
    }

    int *temp_ptr = cb->ptr;

    *(temp_ptr + cb->end) = value;

    cb->end++;

    if(cb->end == cb->capacity){
        cb->end = 0;
    }

    if (cb->end == cb->begin) {
        cb->full = 1;
    }

    return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->capacity <= 0 || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->end > a->capacity || a->begin > a->capacity) {
        if(err_code){
            *err_code = 1;
        }
        return -1;
    }

    if(circular_buffer_empty(a)){
        if(err_code){
            *err_code = 2;
        }
        return -1;
    }

    int result = *(a->ptr + a->begin);

    a->begin++;
    a->full = 0;

    if(a->begin >= a->capacity){
        a->begin = 0;
    }


    if(err_code){
        *err_code = 0;
    }
    return result;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code) {
    if (a == NULL || a->capacity <= 0 || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->end > a->capacity || a->begin > a->capacity) {
        if(err_code){
            *err_code = 1;
        }
        return -1;
    }

    if(circular_buffer_empty(a)){
        if(err_code){
            *err_code = 2;
        }
        return -1;
    }

    a->end--;

    if(a->end < 0){
        a->end = a->end + a->capacity;
    }

    a->full = 0;
    int result = *(a->ptr + a->end);

    if(err_code){
        *err_code = 0;
    }
    return result;
}

int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a == NULL || a->capacity <= 0 || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->end > a->capacity || a->begin > a->capacity) {
        return -1;
    }

    if(a->full){
        return 0;
    }

    return a->begin == a->end;
}

int circular_buffer_full(const struct circular_buffer_t *a) {
    if (a == NULL || a->capacity <= 0 || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->end > a->capacity || a->begin > a->capacity) {
        return -1;
    }
    return a->full;
}

void circular_buffer_display(const struct circular_buffer_t *a) {
    if (a == NULL || a->capacity <= 0 || a->ptr == NULL || a->end < 0 || a->begin < 0 || a->end > a->capacity || a->begin > a->capacity ||
            circular_buffer_empty(a)) {
        return;
    }

    for (int i = a->begin; ;) {
        printf("%d ", *(a->ptr + i));

        i++;
        if (i >= a->capacity) {
            i -= a->capacity;
        }

        if (i == a->end) {
            break;
        }
    }
    printf("\n");
}