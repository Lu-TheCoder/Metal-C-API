//
//  MTVersion.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once

#define METALC_VERSION_MAJOR 367
#define METALC_VERSION_MINOR 4
#define METALC_VERSION_PATCH 2

#define METALC_SUPPORTS_VERSION(major, minor, patch) \
    ((major < METALC_VERSION_MAJOR) || \
    (major == METALC_VERSION_MAJOR && minor < METALC_VERSION_MINOR) || \
    (major == METALC_VERSION_MAJOR && minor == METALC_VERSION_MINOR && patch <= METALC_VERSION_PATCH))
