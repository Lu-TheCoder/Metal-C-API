//
//  event.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct event_context {
    union {
        int64_t  i64[2];
        uint64_t u64[2];
        double   f64[2];
        
        int32_t  i32[4];
        uint32_t u32[4];
        float    f32[4];
        
        int16_t  i16[8];
        uint16_t u16[8];
        
        int8_t    i8[16];
        uint8_t   u8[16];
    } data;
}event_context;

typedef bool (*PFN_on_event)(uint16_t code, void* sender, void* listener_inst, event_context data);

bool event_system_initialize(uint64_t* memory_requirement, void* state);
void event_system_shutdown(void* state);

bool event_register(uint16_t code, void* listener, PFN_on_event on_event);
bool event_unregister(uint16_t code, void* listener, PFN_on_event on_event);

bool event_fire(uint16_t code, void* sender, event_context context);

typedef enum event_code {
    EVENT_CODE_APPLICATION_QUIT = 1,
    EVENT_CODE_KEY_PRESSED = 0x02,
    EVENT_CODE_KEY_RELEASED = 0x03,
    EVENT_CODE_MOUSE_BUTTON_PRESSED = 0x04,
    EVENT_CODE_MOUSE_BUTTON_RELEASED = 0x05,
    EVENT_CODE_MOUSE_BUTTON_CLICKED = 0x06,
    EVENT_CODE_MOUSE_DRAG_BEGIN = 0x07,
    EVENT_CODE_MOUSE_DRAGGED = 0x08,
    EVENT_CODE_MOUSE_DRAG_END = 0x09,
    
    EVENT_CODE_MOUSE_MOVED = 0x0A,
    EVENT_CODE_MOUSE_WHEEL = 0x10,
    EVENT_CODE_RESIZED = 12,
    MAX_EVENT_CODE = 0xFF
}event_code;

