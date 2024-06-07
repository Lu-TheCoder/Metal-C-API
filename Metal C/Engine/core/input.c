//
//  input.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#include "input.h"
#include <stdlib.h>
#include <string.h>

typedef struct keyboard_state {
    bool keys[256];
}keyboard_state;

typedef struct mouse_state {
    uint16_t x;
    uint16_t y;
    bool buttons[MOUSE_BUTTON_MAX];
    bool dragging[MOUSE_BUTTON_MAX];
}mouse_state;

typedef struct input_state {
    keyboard_state keyboard_current;
    keyboard_state keyboard_previous;
    mouse_state mouse_current;
    mouse_state mouse_previous;
    
    bool allow_key_repeats;
}input_state;

static input_state* state_ptr;

bool input_system_initialize(void* state) {
    if(state == 0){
        return true;
    }
    
    memset(state, 0, sizeof(input_state));
    state_ptr = state;
    
    state_ptr->allow_key_repeats = false;
    
    printf("Input System Initialized...\n");
    
    return true;
}

void input_system_shutdown(void* state) {
    state_ptr = 0;
}

// MARK: Keyboard Input

bool input_is_key_down(keys key) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->keyboard_current.keys[key] == true;
}

bool input_is_key_up(keys key) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->keyboard_current.keys[key] == false;
}

bool input_was_key_down(keys key) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->keyboard_previous.keys[key] == true;
}

bool input_was_key_up(keys key) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->keyboard_previous.keys[key] == false;
}

void input_process_key(keys key, bool is_pressed) {
    if(!state_ptr){
        return;
    }
    
    bool is_repeat = is_pressed && state_ptr->keyboard_current.keys[key];
    bool changed = state_ptr->keyboard_current.keys[key] != is_pressed;
    
    if (state_ptr->allow_key_repeats || changed) {
        
        state_ptr->keyboard_current.keys[key] = is_pressed;
        
        // TODO: fire an event..
    }
}

// MARK: Mouse Input

bool input_is_mouse_button_down(mouse_buttons button) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->mouse_current.buttons[button] == true;
}

bool input_is_mouse_button_up(mouse_buttons button) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->mouse_current.buttons[button] == false;
}

bool input_was_mouse_button_down(mouse_buttons button) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->mouse_previous.buttons[button] == true;
}

bool input_was_mouse_button_up(mouse_buttons button) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->mouse_previous.buttons[button] == false;
}

bool input_is_mouse_button_dragging(mouse_buttons button) {
    if(!state_ptr){
        return false;
    }
    
    return state_ptr->mouse_current.dragging[button];
}

void input_get_mouse_position(uint32_t* x, uint32_t* y) {
    if (!state_ptr) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state_ptr->mouse_current.x;
    *y = state_ptr->mouse_current.y;
}

void input_get_previous_mouse_position(uint32_t* x, uint32_t* y) {
    if (!state_ptr) {
        *x = 0;
        *y = 0;
        return;
    }
    *x = state_ptr->mouse_previous.x;
    *y = state_ptr->mouse_previous.y;
}

void input_process_mouse_button(mouse_buttons button, bool is_pressed) {
    
    if (state_ptr->mouse_current.buttons[button] != is_pressed){
        state_ptr->mouse_current.buttons[button] = is_pressed;
        
        // TODO: Fire an Event.
    }
    
    // Handle Dragging
    if (!is_pressed) {
        if (state_ptr->mouse_current.dragging[button]) {
            // lets issue a drag event.
            state_ptr->mouse_current.dragging[false] = false;
            
            // TODO: Fire an Event.
        } else {
            // If we not a drag release, then its a normal click.
            
            // TODO: fire Event.
        }
    }
}

void input_process_mouse_move(uint16_t x, uint16_t y) {
    // Only process if position is different.
    if (state_ptr->mouse_current.x != x || state_ptr->mouse_current.y != y) {
        
        // Update internal state.
        state_ptr->mouse_current.x = x;
        state_ptr->mouse_current.y = y;
        
        // TODO: Fire an Event.
        
        for (uint16_t i = 0; i < MOUSE_BUTTON_MAX; i++){
            // Check if button is down.
            if (state_ptr->mouse_current.buttons[i]) {
                if (!state_ptr->mouse_previous.dragging[i] && !state_ptr->mouse_current.dragging[i]) {
                    // Start dragging for this button.
                    
                    state_ptr->mouse_current.dragging[i] = true;
                    
                    // TODO: Fire an Event.
                    
                } else if (state_ptr->mouse_current.dragging[i]) {
                    // Issue a continuance of a drag operation.
                    // TODO: Fire an Event.
                    
                }
            }
        }
        
    }
}

void input_process_mouse_wheel(uint8_t z_delta) {
    // No internal state to update.
    
    // TODO: Fire an Event.
    
}

const char* input_get_keycode_string(keys key) {
    switch (key) {
        case KEY_BACKSPACE:
            return "backspace";
        case KEY_ENTER:
            return "enter";
        case KEY_TAB:
            return "tab";
        case KEY_CAPITAL:
            return "capslock";
        case KEY_ESCAPE:
            return "esc";

        case KEY_SPACE:
            return "space";
        case KEY_END:
            return "end";
        case KEY_HOME:
            return "home";
        case KEY_LEFT:
            return "left";
        case KEY_UP:
            return "up";
        case KEY_RIGHT:
            return "right";
        case KEY_PRINT:
            return "print";

        case KEY_0:
            return "0";
        case KEY_1:
            return "1";
        case KEY_2:
            return "2";
        case KEY_3:
            return "3";
        case KEY_4:
            return "4";
        case KEY_5:
            return "5";
        case KEY_6:
            return "6";
        case KEY_7:
            return "7";
        case KEY_8:
            return "8";
        case KEY_9:
            return "9";

        case KEY_A:
            return "a";
        case KEY_B:
            return "b";
        case KEY_C:
            return "c";
        case KEY_D:
            return "d";
        case KEY_E:
            return "e";
        case KEY_F:
            return "f";
        case KEY_G:
            return "g";
        case KEY_H:
            return "h";
        case KEY_I:
            return "i";
        case KEY_J:
            return "j";
        case KEY_K:
            return "k";
        case KEY_L:
            return "l";
        case KEY_M:
            return "m";
        case KEY_N:
            return "n";
        case KEY_O:
            return "o";
        case KEY_P:
            return "p";
        case KEY_Q:
            return "q";
        case KEY_R:
            return "r";
        case KEY_S:
            return "s";
        case KEY_T:
            return "t";
        case KEY_U:
            return "u";
        case KEY_V:
            return "v";
        case KEY_W:
            return "w";
        case KEY_X:
            return "x";
        case KEY_Y:
            return "y";
        case KEY_Z:
            return "z";

        case KEY_LSUPER:
            return "l_super";
        case KEY_RSUPER:
            return "r_super";

            // Numberpad keys
        case KEY_NUMPAD0:
            return "numpad_0";
        case KEY_NUMPAD1:
            return "numpad_1";
        case KEY_NUMPAD2:
            return "numpad_2";
        case KEY_NUMPAD3:
            return "numpad_3";
        case KEY_NUMPAD4:
            return "numpad_4";
        case KEY_NUMPAD5:
            return "numpad_5";
        case KEY_NUMPAD6:
            return "numpad_6";
        case KEY_NUMPAD7:
            return "numpad_7";
        case KEY_NUMPAD8:
            return "numpad_8";
        case KEY_NUMPAD9:
            return "numpad_9";
        case KEY_MULTIPLY:
            return "numpad_mult";
        case KEY_ADD:
            return "numpad_add";
        case KEY_SUBTRACT:
            return "numpad_sub";
        case KEY_DECIMAL:
            return "numpad_decimal";
        case KEY_DIVIDE:
            return "numpad_div";

        case KEY_F1:
            return "f1";
        case KEY_F2:
            return "f2";
        case KEY_F3:
            return "f3";
        case KEY_F4:
            return "f4";
        case KEY_F5:
            return "f5";
        case KEY_F6:
            return "f6";
        case KEY_F7:
            return "f7";
        case KEY_F8:
            return "f8";
        case KEY_F9:
            return "f9";
        case KEY_F10:
            return "f10";
        case KEY_F11:
            return "f11";
        case KEY_F12:
            return "f12";
        case KEY_F14:
            return "f14";
        case KEY_F15:
            return "f15";
        case KEY_F16:
            return "f16";
        case KEY_F17:
            return "f17";
        case KEY_F18:
            return "f18";
        case KEY_F19:
            return "f19";
        case KEY_F20:
            return "f20";

        case KEY_NUMLOCK:
            return "num_lock";
        case KEY_NUMPAD_EQUAL:
            return "numpad_equal";

        case KEY_LSHIFT:
            return "l_shift";
        case KEY_RSHIFT:
            return "r_shift";
        case KEY_LCONTROL:
            return "l_ctrl";
        case KEY_RCONTROL:
            return "r_ctrl";
        case KEY_LALT:
            return "l_alt";
        case KEY_RALT:
            return "r_alt";

        case KEY_SEMICOLON:
            return ";";

        case KEY_APOSTROPHE:
            return "'";
        case KEY_EQUAL:
            return "=";
        case KEY_COMMA:
            return ",";
        case KEY_MINUS:
            return "-";
        case KEY_PERIOD:
            return ".";
        case KEY_SLASH:
            return "/";

        case KEY_GRAVE:
            return "`";

        case KEY_LBRACKET:
            return "[";
        case KEY_RBRACKET:
            return "]";

        default:
            return "undefined";
    }
}
