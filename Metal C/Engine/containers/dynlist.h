//
//  dynlist.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/16.
//

#pragma once

#include <stdio.h>
#include <stdint.h>

typedef struct dynlist_header {
    uint64_t capacity;
    uint64_t length;
    uint64_t stride;
} dynlist_header;

#define DYNLIST_DEFAULT_CAPACITY 1
#define DYNLIST_RESIZE_FACTOR 2

void* _dynlist_create(uint64_t length, uint64_t stride);
void* _dynlist_resize(void* list);
void* _dynlist_push(void* list, const void* value_ptr);
void* _dynlist_insert_at(void* list, uint64_t index, void* value_ptr);

#define dynlist_create(type) \
    (type*)_dynlist_create(DYNLIST_DEFAULT_CAPACITY, sizeof(type))

#define dynlist_reserve(type, capacity) \
    _dynlist_create(capacity, sizeof(type))

#define dynlist_push(list, value) \
{ \
    __typeof__(value) temp = value; \
    list = _dynlist_push(list, &temp); \
}

#define dynlist_insert_at(list, index, value) \
{ \
    __typeof__(value) temp = value; \
    list = _dynlist_insert_at(list, index, &temp); \
}

void dynlist_destroy(void* list);
void dynlist_pop(void* list, void* dest);
void* dynlist_pop_at(void* list, uint64_t index, void* dest);
void dynlist_clear(void* list);

uint64_t dynlist_capacity(void* list);
uint64_t dynlist_length(void* list);
uint64_t dynlist_stride(void* list);
void dynlist_length_set(void* list, uint64_t value);
