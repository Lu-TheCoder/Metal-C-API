//
//  NSBundle.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTURL.h"
#include "MTString.h"
#include "defines.h"
#include <stdlib.h>

typedef void* MTBundle;
typedef void* MTArray;
typedef void* MTError;

// ============================================================================
// Bundle Creation
// ============================================================================

MT_INLINE MTBundle mt_bundle_main(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("NSBundle"), MT_SEL("mainBundle"));
}

MT_INLINE MTBundle mt_bundle_with_path(MTString path) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSBundle"), MT_SEL("bundleWithPath:"), id, path);
}

MT_INLINE MTBundle mt_bundle_init_with_path(MTBundle bundle, MTString path) {
    return MT_MSG_SEND_1(id, bundle, MT_SEL("initWithPath:"), id, path);
}

MT_INLINE MTBundle mt_bundle_with_url(MTURL url) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSBundle"), MT_SEL("bundleWithURL:"), id, url);
}

MT_INLINE MTBundle mt_bundle_init_with_url(MTBundle bundle, MTURL url) {
    return MT_MSG_SEND_1(id, bundle, MT_SEL("initWithURL:"), id, url);
}

MT_INLINE MTBundle mt_bundle_for_class(void *aClass) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSBundle"), MT_SEL("bundleForClass:"), Class, aClass);
}

MT_INLINE MTBundle mt_bundle_with_identifier(MTString identifier) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSBundle"), MT_SEL("bundleWithIdentifier:"), id, identifier);
}

// ============================================================================
// Bundle Collections
// ============================================================================

MT_INLINE void mt_bundle_all_bundles(MTBundle **outBundles, unsigned long *outCount) {
    id array = MT_MSG_SEND_CLASS(id, MT_CLASS("NSBundle"), MT_SEL("allBundles"));
    if (outBundles && outCount && array) {
        unsigned long count = MT_MSG_SEND(unsigned long, array, MT_SEL("count"));
        *outCount = count;
        MTBundle *bundles = (MTBundle *)malloc(sizeof(MTBundle) * count);
        for (unsigned long i = 0; i < count; i++) {
            bundles[i] = MT_MSG_SEND_1(id, array, MT_SEL("objectAtIndex:"), unsigned long, i);
        }
        *outBundles = bundles;
    }
}

MT_INLINE void mt_bundle_all_frameworks(MTBundle **outBundles, unsigned long *outCount) {
    id array = MT_MSG_SEND_CLASS(id, MT_CLASS("NSBundle"), MT_SEL("allFrameworks"));
    if (outBundles && outCount && array) {
        unsigned long count = MT_MSG_SEND(unsigned long, array, MT_SEL("count"));
        *outCount = count;
        MTBundle *bundles = (MTBundle *)malloc(sizeof(MTBundle) * count);
        for (unsigned long i = 0; i < count; i++) {
            bundles[i] = MT_MSG_SEND_1(id, array, MT_SEL("objectAtIndex:"), unsigned long, i);
        }
        *outBundles = bundles;
    }
}

// ============================================================================
// Loading
// ============================================================================

MT_INLINE bool mt_bundle_load(MTBundle bundle) {
    return MT_MSG_SEND(BOOL, bundle, MT_SEL("load"));
}

MT_INLINE bool mt_bundle_is_loaded(MTBundle bundle) {
    return MT_MSG_SEND(BOOL, bundle, MT_SEL("isLoaded"));
}

MT_INLINE bool mt_bundle_unload(MTBundle bundle) {
    return MT_MSG_SEND(BOOL, bundle, MT_SEL("unload"));
}

MT_INLINE bool mt_bundle_preflight_and_return_error(MTBundle bundle, MTError** outError) {
    return MT_MSG_SEND_1(BOOL, bundle, MT_SEL("preflightAndReturnError:"), MTError**, outError);
}

MT_INLINE bool mt_bundle_load_and_return_error(MTBundle bundle, MTError** outError) {
    return MT_MSG_SEND_1(BOOL, bundle, MT_SEL("loadAndReturnError:"), MTError**, outError);
}

// ============================================================================
// Resource Lookup
// ============================================================================

MT_INLINE MTURL mt_bundle_url_for_resource_with_extension(MTBundle bundle, MTString name, MTString extension) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("URLForResource:withExtension:"), id, name, id, extension);
}

MT_INLINE MTString mt_bundle_get_info_dict_value(MTBundle bundle, const char* key_utf8) {
    MTString key = mt_string_from_utf8(key_utf8);
    return MT_MSG_SEND_1(id, bundle, MT_SEL("objectForInfoDictionaryKey:"), id, key);
}

// ============================================================================
// Path Properties
// ============================================================================

MT_INLINE MTString mt_bundle_get_bundle_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("bundlePath"));
}

MT_INLINE MTString mt_bundle_get_resource_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("resourcePath"));
}

MT_INLINE MTString mt_bundle_get_executable_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("executablePath"));
}

MT_INLINE MTString mt_bundle_path_for_auxiliary_executable(MTBundle bundle, MTString executableName) {
    return MT_MSG_SEND_1(id, bundle, MT_SEL("pathForAuxiliaryExecutable:"), id, executableName);
}

MT_INLINE MTString mt_bundle_get_private_frameworks_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("privateFrameworksPath"));
}

MT_INLINE MTString mt_bundle_get_shared_frameworks_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("sharedFrameworksPath"));
}

MT_INLINE MTString mt_bundle_get_shared_support_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("sharedSupportPath"));
}

MT_INLINE MTString mt_bundle_get_builtin_plugins_path(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("builtInPlugInsPath"));
}

// ============================================================================
// URL Properties
// ============================================================================

MT_INLINE MTURL mt_bundle_get_bundle_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("bundleURL"));
}

MT_INLINE MTURL mt_bundle_get_resource_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("resourceURL"));
}

MT_INLINE MTURL mt_bundle_get_executable_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("executableURL"));
}

MT_INLINE MTURL mt_bundle_url_for_auxiliary_executable(MTBundle bundle, MTString executableName) {
    return MT_MSG_SEND_1(id, bundle, MT_SEL("URLForAuxiliaryExecutable:"), id, executableName);
}

MT_INLINE MTURL mt_bundle_get_private_frameworks_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("privateFrameworksURL"));
}

MT_INLINE MTURL mt_bundle_get_shared_frameworks_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("sharedFrameworksURL"));
}

MT_INLINE MTURL mt_bundle_get_shared_support_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("sharedSupportURL"));
}

MT_INLINE MTURL mt_bundle_get_builtin_plugins_url(MTBundle bundle) {
    return MT_MSG_SEND(id, bundle, MT_SEL("builtInPlugInsURL"));
}

MT_INLINE MTString mt_bundle_get_lib_path(MTBundle bundle, MTString file_name, MTString file_extension) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("pathForResource:ofType:"), id, file_name, id, file_extension);
}

// ============================================================================
// Class Methods (NSURL Return)
// ============================================================================

MT_INLINE MTURL mt_bundle_url_for_resource_in_bundle(MTString name, MTString ext, MTString subdir, MTURL bundleURL) {
    return MT_MSG_SEND_CLASS_2(id, MT_CLASS("NSBundle"), MT_SEL("URLForResource:withExtension:subdirectory:inBundleWithURL:"), id, name, id, ext);
    // Note: This needs MSG_SEND_4 for full implementation
}

MT_INLINE MTArray mt_bundle_urls_for_resources_in_bundle(MTString ext, MTString subdir, MTURL bundleURL) {
    return MT_MSG_SEND_CLASS_2(id, MT_CLASS("NSBundle"), MT_SEL("URLsForResourcesWithExtension:subdirectory:inBundleWithURL:"), id, ext, id, subdir);
}

MT_INLINE MTURL mt_bundle_url_for_resource_(MTString name, MTString ext) {
    id mainBundle = MT_MSG_SEND_CLASS(id, MT_CLASS("NSBundle"), MT_SEL("mainBundle"));
    return MT_MSG_SEND_2(id, mainBundle, MT_SEL("URLForResource:withExtension:"), id, name, id, ext);
}

// ============================================================================
// Instance Methods (NSURL Return)
// ============================================================================

MT_INLINE MTURL mt_bundle_url_for_resource(MTBundle bundle, MTString name, MTString ext) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("URLForResource:withExtension:"), id, name, id, ext);
}

MT_INLINE MTURL mt_bundle_url_for_resource_in_subdir(MTBundle bundle, MTString name, MTString ext, MTString subdir) {
    return MT_MSG_SEND_3(id, bundle, MT_SEL("URLForResource:withExtension:subdirectory:"), id, name, id, ext, id, subdir);
}

MT_INLINE MTURL mt_bundle_url_for_resource_in_subdir_with_localization(MTBundle bundle, MTString name, MTString ext, MTString subdir, MTString localization) {
    return MT_MSG_SEND_4(id, bundle, MT_SEL("URLForResource:withExtension:subdirectory:localization:"), id, name, id, ext, id, subdir, id, localization);
}

MT_INLINE MTArray mt_bundle_urls_for_resources_in_subdir(MTBundle bundle, MTString ext, MTString subdir) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("URLsForResourcesWithExtension:subdirectory:"), id, ext, id, subdir);
}

MT_INLINE MTArray mt_bundle_urls_for_resources_in_subdir_with_localization(MTBundle bundle, MTString ext, MTString subdir, MTString localization) {
    return MT_MSG_SEND_3(id, bundle, MT_SEL("URLsForResourcesWithExtension:subdirectory:localization:"), id, ext, id, subdir, id, localization);
}

// ============================================================================
// Class Methods (NSString* Return)
// ============================================================================

MT_INLINE MTString mt_bundle_path_for_resource_in_dir(MTString name, MTString ext, MTString bundlePath) {
    return MT_MSG_SEND_CLASS_2(id, MT_CLASS("NSBundle"), MT_SEL("pathForResource:ofType:inDirectory:"), id, name, id, ext);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir(MTString ext, MTString bundlePath) {
    return MT_MSG_SEND_CLASS_2(id, MT_CLASS("NSBundle"), MT_SEL("pathsForResourcesOfType:inDirectory:"), id, ext, id, bundlePath);
}

MT_INLINE MTString mt_bundle_path_for_resource_(MTString name, MTString ext) {
    id mainBundle = MT_MSG_SEND_CLASS(id, MT_CLASS("NSBundle"), MT_SEL("mainBundle"));
    return MT_MSG_SEND_2(id, mainBundle, MT_SEL("pathForResource:ofType:"), id, name, id, ext);
}

// ============================================================================
// Instance Methods (NSString* Return)
// ============================================================================

MT_INLINE MTString mt_bundle_path_for_resource(MTBundle bundle, MTString name, MTString ext) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("pathForResource:ofType:"), id, name, id, ext);
}

MT_INLINE MTString mt_bundle_path_for_resource_in_dir_bundle(MTBundle bundle, MTString name, MTString ext, MTString subdir) {
    return MT_MSG_SEND_3(id, bundle, MT_SEL("pathForResource:ofType:inDirectory:"), id, name, id, ext, id, subdir);
}

MT_INLINE MTString mt_bundle_path_for_resource_in_dir_with_localization(MTBundle bundle, MTString name, MTString ext, MTString subdir, MTString localization) {
    return MT_MSG_SEND_4(id, bundle, MT_SEL("pathForResource:ofType:inDirectory:forLocalization:"), id, name, id, ext, id, subdir, id, localization);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir_instance(MTBundle bundle, MTString ext, MTString subdir) {
    return MT_MSG_SEND_2(id, bundle, MT_SEL("pathsForResourcesOfType:inDirectory:"), id, ext, id, subdir);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir_with_localization(MTBundle bundle, MTString ext, MTString subdir, MTString localization) {
    return MT_MSG_SEND_3(id, bundle, MT_SEL("pathsForResourcesOfType:inDirectory:forLocalization:"), id, ext, id, subdir, id, localization);
}
