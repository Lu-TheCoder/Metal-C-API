//
//  input.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "input_types.h"

bool input_system_initialize(void* state);
void input_system_shutdown(void* state);

bool input_is_key_down(keys key);
bool input_is_key_up(keys key);
bool input_was_key_down(keys key);
bool input_was_key_up(keys key);
void input_process_key(keys key, bool is_pressed);

bool input_is_mouse_button_down(mouse_buttons button);
bool input_is_mouse_button_up(mouse_buttons button);
bool input_was_mouse_button_down(mouse_buttons button);
bool input_was_mouse_button_up(mouse_buttons button);
bool input_is_mouse_button_dragging(mouse_buttons button);

void input_get_mouse_position(uint32_t* x, uint32_t* y);
void input_get_previous_mouse_position(uint32_t* x, uint32_t* y);

void input_process_mouse_button(mouse_buttons button, bool is_pressed);
void input_process_mouse_move(uint16_t x, uint16_t y);
void input_process_mouse_wheel(uint8_t z_delta);

const char* input_get_keycode_string(keys key);
