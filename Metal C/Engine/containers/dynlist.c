//
//  dynlist.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/16.
//

#include "dynlist.h"
#include <stdlib.h>
#include <string.h>

void* _dynlist_create(uint64_t length, uint64_t stride) {
    uint64_t header_size = sizeof(dynlist_header);
    uint64_t list_size = length * stride;
    void* new_list = malloc(header_size + list_size);
    
    if (!new_list) {
        printf("dynlist_create: Memory allocation failed.\n");
        return 0;
    }
    
    memset(new_list, 0, header_size + list_size);
    
    if (length == 0) {
        // FATAL ERROR?
        printf("_dynlist_create called with length of 0.\n");
    }
    
    dynlist_header* header = (dynlist_header*)new_list;
    header->capacity = length;
    header->length = 0;
    header->stride = stride;
    
    return (void*)((uint8_t*)new_list + header_size);
}

void* _dynlist_resize(void* list) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    
    if (header->capacity == 0){
        printf("_dynlist_resize called on a list with 0 capacity. This should not be possible.\n");
        return 0;
    }
    
    void* temp = _dynlist_create((DYNLIST_RESIZE_FACTOR * header->capacity), header->stride);
    
    if (!temp) {
        printf("dynlist_resize: Failed to create temp list.\n");
        return 0;
    }
    
    dynlist_header* new_header = (dynlist_header*)((uint8_t*)temp - header_size);
    new_header->length = header->length;
    
    memcpy(temp, list, header->length * header->stride);
    
    dynlist_destroy(list);
    return temp;
}

void* _dynlist_push(void* list, const void* value_ptr) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    
    if (header->length >= header->capacity) {
        list = _dynlist_resize(list);
        header = (dynlist_header*)((uint8_t*)list - header_size);
    }
    
//    uint64_t addr = (uint64_t)list;
    uintptr_t addr = (uintptr_t)list;
    
    addr += (header->length * header->stride);
    memcpy((void*)addr, value_ptr, header->stride);
    dynlist_length_set(list, header->length + 1);
    return list;
}

void* _dynlist_insert_at(void* list, uint64_t index, void* value_ptr){
    uint64_t length = dynlist_length(list);
    uint64_t stride = dynlist_stride(list);
    
    if (index >= length) {
        printf("Index outside the bounds of this list! Length: %llu, index: %llu", length, index);
        return list;
    }
    
    if (length >= dynlist_capacity(list)){
        list = _dynlist_resize(list);
    }
    
//    uint64_t addr = (uint64_t)list;
    uintptr_t addr = (uintptr_t)list;
    
    // Push element(s) from index forward out by one. This should
    // even happen if inserted at the last index.
//    memcpy((void*)(addr + ((index + 1) * stride)),
//           (void*)(addr + (index * stride)),
//           stride * (length - index));
    
    // Use memmove instead of memcpy to handle overlapping regions
    memmove((void*)(addr + ((index + 1) * stride)),
         (void*)(addr + (index * stride)),
         stride * (length - index));
    
    // Set the value at the index.
    memcpy((void*)(addr + (index * stride)), value_ptr, stride);
    dynlist_length_set(list, length + 1);
    
    return list;
}

void dynlist_destroy(void* list) {
    if (list) {
        uint64_t header_size = sizeof(dynlist_header);
        dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
//        uint64_t total_size = header_size + header->capacity * header->stride;
        free(header);
    }
}

void dynlist_pop(void* list, void* dest) {
    uint64_t length = dynlist_length(list);
    uint64_t stride = dynlist_stride(list);
    
    if (length < 1) {
        printf("dynlist_pop called on an empty list. Nothing to be done.\n");
        return;
    }
    
//    uint64_t addr = (uint64_t)list;
    uintptr_t addr = (uintptr_t)list;
    
    addr += ((length - 1) * stride);
    
    if (dest) {
        memcpy(dest, (void*)addr, stride);
    }
    
    dynlist_length_set(list, length - 1);
}

void* dynlist_pop_at(void* list, uint64_t index, void* dest) {
    uint64_t length = dynlist_length(list);
    uint64_t stride = dynlist_stride(list);
    
    if (index >= length) {
        printf("Index outside the bounds of this list! Length: %llu, index: %llu", length, index);
        return list;
    }
    
//    uint64_t addr = (uint64_t)list;
    uintptr_t addr = (uintptr_t)list;
    if (dest) {
        memcpy(dest, (void*)(addr + (index * stride)), stride);
    }
    
//    // If not on the last element snip out entry and copy the rest inward.
//    if (index != length - 1) {
//        memcpy((void*)(addr + (index * stride)),
//               (void*)(addr + ((index + 1) * stride)),
//               stride * (length - (index - 1)));
//    }
    
    // Use memmove instead of memcpy to handle overlapping regions
    if (index != length - 1) {
       memmove((void*)(addr + (index * stride)),
              (void*)(addr + ((index + 1) * stride)),
              stride * (length - index - 1));
    }
    
    dynlist_length_set(list, length - 1);
    return list;
}

void dynlist_clear(void* list) {
    dynlist_length_set(list, 0);
}

uint64_t dynlist_capacity(void* list) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    return header->capacity;
}

uint64_t dynlist_length(void* list) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    return header->length;
}

uint64_t dynlist_stride(void* list) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    return header->stride;
}

void dynlist_length_set(void* list, uint64_t value) {
    uint64_t header_size = sizeof(dynlist_header);
    dynlist_header* header = (dynlist_header*)((uint8_t*)list - header_size);
    header->length = value;
}
