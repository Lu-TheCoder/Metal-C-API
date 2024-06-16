//
//  platform.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/02.
//

#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct platform_system_config{
    const char* application_name;
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t flags;
}platform_system_config;

typedef struct GWindow {
    uint16_t width;
    uint16_t height;
    bool resizing;
}GWindow;


typedef void (*platform_window_resized_callback)(uint16_t width, uint16_t height);



bool platform_system_startup(platform_system_config* config);
void platform_system_shutdown(void);
bool platform_pump_messages(void);
void* platform_get_next_drawable(void);
void* platform_get_next_drawable_texture(void* drawable);
unsigned long platform_get_drawable_width(void);
unsigned long platform_get_drawable_height(void);
unsigned long platform_get_drawable_pixelFormat(void);
