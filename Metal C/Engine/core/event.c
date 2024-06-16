//
//  event.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#include "event.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../containers/dynlist.h"

typedef struct registered_event {
    void* listener;
    PFN_on_event callback;
} registered_event;

typedef struct event_code_entry {
    registered_event* events;
} event_code_entry;

// This should be more than enough codes...
#define MAX_MESSAGE_CODES 16384

// State structure.
typedef struct event_system_state {
    // Lookup table for event codes.
    event_code_entry registered[MAX_MESSAGE_CODES];
} event_system_state;

static event_system_state* state_ptr;

bool event_system_initialize(uint64_t* memory_requirement, void* state){
    *memory_requirement = sizeof(event_system_state);
    if (state == 0){
        return true;
    }
    
    memset(state, 0, sizeof(state));
    state_ptr = state;
    
//    event_register(EVENT_CODE_APPLICATION_QUIT, 0, 0);

    return true;
}

void event_system_shutdown(void* state){
    if (state_ptr) {
        for (uint16_t i = 0; i < MAX_MESSAGE_CODES; i++){
            if (state_ptr->registered[i].events != 0){
                dynlist_destroy(state_ptr->registered[i].events);
                state_ptr->registered[i].events = 0;
            }
        }
    }
    state_ptr = 0;
}

bool event_register(uint16_t code, void* listener, PFN_on_event on_event){
    if (!state_ptr) {
        printf("NO EVENT SYSTEM!! \n");
        return false;
    }
    
    if (state_ptr->registered[code].events == 0){
        state_ptr->registered[code].events = dynlist_create(registered_event);
        printf("EVENT SYSTEM -> Malloced events \n");
    }
//    
    uint64_t registered_count = dynlist_length(state_ptr->registered[code].events);
    printf("Registered Count: %llu \n", registered_count);
    
    for (uint64_t i = 0; i < registered_count; ++i) {
        if (state_ptr->registered[code].events[i].listener == listener && state_ptr->registered[code].events[i].callback == on_event) {
            printf("Event has already been registered with the code %hu and the callback of %p", code, on_event);
            return false;
        }
    }
    
    registered_event event;
    event.listener = listener;
    event.callback = on_event;
    dynlist_push(state_ptr->registered[code].events, event);
    
    return true;
}

bool event_unregister(uint16_t code, void* listener, PFN_on_event on_event){
    if (!state_ptr) {
        return false;
    }
    
    if (state_ptr->registered[code].events == 0){
        // TODO: WARN
        return false;
    }
    
    uint64_t registered_count = dynlist_length(state_ptr->registered[code].events);
    for (uint64_t i = 0; i < registered_count; ++i) {
        registered_event e = state_ptr->registered[code].events[i];
        if (e.listener == listener && e.callback == on_event) {
            // Found one, remove it
            registered_event popped_event;
            dynlist_pop_at(state_ptr->registered[code].events, i, &popped_event);
            return true;
        }
    }
    
    // Not found.
    return  false;
}

bool event_fire(uint16_t code, void* sender, event_context context){
    if (!state_ptr) {
        return false;
    }
    
    // If nothing is registered for the code, boot out.
    if (state_ptr->registered[code].events == 0){
        return false;
    }
    
    uint64_t registered_count = dynlist_length(state_ptr->registered[code].events);
    for (uint64_t i = 0; i < registered_count; ++i) {
        registered_event e = state_ptr->registered[code].events[i];
        if (e.callback(code, sender, e.listener, context)) {
            // Message has been handled, do not send to other listeners.
            return true;
        }

    }

    // Not found.
    return false;
}
