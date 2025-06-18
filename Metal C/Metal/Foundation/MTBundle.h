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

typedef void* MTBundle;
typedef void* MTArray;
typedef void* MTError;

// Helper: objc_msgSend with NSString*
typedef id (*MsgSendStr3)(id, SEL, id, id, id);
typedef id (*MsgSendStr4)(id, SEL, id, id, id, id);

MT_INLINE MTBundle mt_bundle_main(void) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("mainBundle");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)((id)bundleClass, sel);
}

MT_INLINE MTBundle mt_bundle_with_path(MTString path) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("bundleWithPath:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)((id)bundleClass, sel, path);
}

MT_INLINE MTBundle mt_bundle_init_with_path(MTBundle bundle, MTString path) {
    SEL sel = sel_registerName("initWithPath:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, path);
}

MT_INLINE MTBundle mt_bundle_with_url(MTURL url) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("bundleWithURL:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)((id)bundleClass, sel, url);
}

MT_INLINE MTBundle mt_bundle_init_with_url(MTBundle bundle, MTURL url) {
    SEL sel = sel_registerName("initWithURL:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, url);
}

MT_INLINE MTBundle mt_bundle_for_class(void *aClass) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("bundleForClass:");
    typedef id (*MsgSendFn)(id, SEL, Class);
    return ((MsgSendFn)objc_msgSend)((id)bundleClass, sel, aClass);
}

MT_INLINE MTBundle mt_bundle_with_identifier(MTString identifier) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("bundleWithIdentifier:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)((id)bundleClass, sel, identifier);
}

MT_INLINE void mt_bundle_all_bundles(MTBundle **outBundles, unsigned long *outCount) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("allBundles");
    typedef id (*MsgSendFn)(id, SEL);
    id array = ((MsgSendFn)objc_msgSend)((id)bundleClass, sel);

    if (outBundles && outCount && array) {
        SEL countSel = sel_registerName("count");
        SEL objectAtIndexSel = sel_registerName("objectAtIndex:");
        typedef unsigned long (*CountFn)(id, SEL);
        typedef id (*ObjAtIndexFn)(id, SEL, unsigned long);

        unsigned long count = ((CountFn)objc_msgSend)(array, countSel);
        *outCount = count;

        MTBundle *bundles = (MTBundle *)malloc(sizeof(MTBundle) * count);
        for (unsigned long i = 0; i < count; i++) {
            bundles[i] = ((ObjAtIndexFn)objc_msgSend)(array, objectAtIndexSel, i);
        }
        *outBundles = bundles;
    }
}

MT_INLINE void mt_bundle_all_frameworks(MTBundle **outBundles, unsigned long *outCount) {
    Class bundleClass = objc_getClass("NSBundle");
    SEL sel = sel_registerName("allFrameworks");
    typedef id (*MsgSendFn)(id, SEL);
    id array = ((MsgSendFn)objc_msgSend)((id)bundleClass, sel);

    if (outBundles && outCount && array) {
        SEL countSel = sel_registerName("count");
        SEL objectAtIndexSel = sel_registerName("objectAtIndex:");
        typedef unsigned long (*CountFn)(id, SEL);
        typedef id (*ObjAtIndexFn)(id, SEL, unsigned long);

        unsigned long count = ((CountFn)objc_msgSend)(array, countSel);
        *outCount = count;

        MTBundle *bundles = (MTBundle *)malloc(sizeof(MTBundle) * count);
        for (unsigned long i = 0; i < count; i++) {
            bundles[i] = ((ObjAtIndexFn)objc_msgSend)(array, objectAtIndexSel, i);
        }
        *outBundles = bundles;
    }
}

MT_INLINE bool mt_bundle_load(MTBundle bundle) {
    SEL sel = sel_registerName("load");
    typedef BOOL (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

MT_INLINE bool mt_bundle_is_loaded(MTBundle bundle) {
    SEL sel = sel_registerName("isLoaded");
    typedef BOOL (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

MT_INLINE bool mt_bundle_unload(MTBundle bundle) {
    SEL sel = sel_registerName("unload");
    typedef BOOL (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

MT_INLINE bool mt_bundle_preflight_and_return_error(MTBundle bundle, MTError *outError) {
    SEL sel = sel_registerName("preflightAndReturnError:");
    typedef BOOL (*MsgSendFn)(id, SEL, MTError *);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, outError);
}

MT_INLINE bool mt_bundle_load_and_return_error(MTBundle bundle, MTError *outError) {
    SEL sel = sel_registerName("loadAndReturnError:");
    typedef BOOL (*MsgSendFn)(id, SEL, MTError *);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, outError);
}

MT_INLINE MTURL mt_bundle_url_for_resource_with_extension(MTBundle bundle, MTString name, MTString extension) {
    SEL sel = sel_registerName("URLForResource:withExtension:");
    typedef id (*MsgSendFn)(id, SEL, id, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, name, extension);
}

/// Calls -[NSBundle objectForInfoDictionaryKey:]
MT_INLINE MTString mt_bundle_get_info_dict_value(MTBundle bundle, const char* key_utf8) {
    MTString key = mt_string_from_utf8(key_utf8);
    SEL sel = sel_registerName("objectForInfoDictionaryKey:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, key);
}


/// Returns NSString* for `bundlePath` property
MT_INLINE MTString mt_bundle_get_bundle_path(MTBundle bundle) {
    SEL sel = sel_registerName("bundlePath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSString* for `resourcePath` property (nullable)
MT_INLINE MTString mt_bundle_get_resource_path(MTBundle bundle) {
    SEL sel = sel_registerName("resourcePath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSString* for `executablePath` property (nullable)
MT_INLINE MTString mt_bundle_get_executable_path(MTBundle bundle) {
    SEL sel = sel_registerName("executablePath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Calls `-pathForAuxiliaryExecutable:` method and returns NSString* (nullable)
MT_INLINE MTString mt_bundle_path_for_auxiliary_executable(MTBundle bundle, MTString executableName) {
    SEL sel = sel_registerName("pathForAuxiliaryExecutable:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, executableName);
}

/// Returns NSString* for `privateFrameworksPath` property (nullable)
MT_INLINE MTString mt_bundle_get_private_frameworks_path(MTBundle bundle) {
    SEL sel = sel_registerName("privateFrameworksPath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSString* for `sharedFrameworksPath` property (nullable)
MT_INLINE MTString mt_bundle_get_shared_frameworks_path(MTBundle bundle) {
    SEL sel = sel_registerName("sharedFrameworksPath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSString* for `sharedSupportPath` property (nullable)
MT_INLINE MTString mt_bundle_get_shared_support_path(MTBundle bundle) {
    SEL sel = sel_registerName("sharedSupportPath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSString* for `builtInPlugInsPath` property (nullable)
MT_INLINE MTString mt_bundle_get_builtin_plugins_path(MTBundle bundle) {
    SEL sel = sel_registerName("builtInPlugInsPath");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `bundleURL` property
MT_INLINE MTURL mt_bundle_get_bundle_url(MTBundle bundle) {
    SEL sel = sel_registerName("bundleURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `resourceURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_resource_url(MTBundle bundle) {
    SEL sel = sel_registerName("resourceURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `executableURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_executable_url(MTBundle bundle) {
    SEL sel = sel_registerName("executableURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Calls `-URLForAuxiliaryExecutable:` method and returns NSURL* (nullable)
MT_INLINE MTURL mt_bundle_url_for_auxiliary_executable(MTBundle bundle, MTString executableName) {
    SEL sel = sel_registerName("URLForAuxiliaryExecutable:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)(bundle, sel, executableName);
}

/// Returns NSURL* for `privateFrameworksURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_private_frameworks_url(MTBundle bundle) {
    SEL sel = sel_registerName("privateFrameworksURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `sharedFrameworksURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_shared_frameworks_url(MTBundle bundle) {
    SEL sel = sel_registerName("sharedFrameworksURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `sharedSupportURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_shared_support_url(MTBundle bundle) {
    SEL sel = sel_registerName("sharedSupportURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

/// Returns NSURL* for `builtInPlugInsURL` property (nullable)
MT_INLINE MTURL mt_bundle_get_builtin_plugins_url(MTBundle bundle) {
    SEL sel = sel_registerName("builtInPlugInsURL");
    typedef id (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(bundle, sel);
}

MT_INLINE MTString mt_bundle_get_lib_path(MTBundle bundle, MTString file_name, MTString file_extension) {
    SEL sel = sel_registerName("pathForResource:ofType:");
    return ((id (*)(id, SEL, id, id))objc_msgSend)(bundle, sel, file_name, file_extension);
}

// --------- Class Methods (NSURL Return) ---------

MT_INLINE MTURL mt_bundle_url_for_resource_in_bundle(MTString name, MTString ext, MTString subdir, MTURL bundleURL) {
    SEL sel = sel_registerName("URLForResource:withExtension:subdirectory:inBundleWithURL:");
    Class cls = objc_getClass("NSBundle");
    return ((MsgSendStr4)objc_msgSend)((id)cls, sel, name, ext, subdir, bundleURL);
}


MT_INLINE MTArray mt_bundle_urls_for_resources_in_bundle(MTString ext, MTString subdir, MTURL bundleURL) {
    SEL sel = sel_registerName("URLsForResourcesWithExtension:subdirectory:inBundleWithURL:");
    Class cls = objc_getClass("NSBundle");
    return ((MsgSendStr3)objc_msgSend)((id)cls, sel, ext, subdir, bundleURL);
}

MT_INLINE MTURL mt_bundle_url_for_resource_(MTString name, MTString ext) {
    SEL sel = sel_registerName("URLForResource:withExtension:");
    Class cls = objc_getClass("NSBundle");
    id mainBundle = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_registerName("mainBundle"));
    return ((id (*)(id, SEL, id, id))objc_msgSend)(mainBundle, sel, name, ext);
}
// --------- Instance Methods (NSURL Return) ---------

MT_INLINE MTURL mt_bundle_url_for_resource(MTBundle bundle, MTString name, MTString ext) {
    SEL sel = sel_registerName("URLForResource:withExtension:");
    return ((id (*)(id, SEL, id, id))objc_msgSend)(bundle, sel, name, ext);
}

MT_INLINE MTURL mt_bundle_url_for_resource_in_subdir(MTBundle bundle, MTString name, MTString ext, MTString subdir) {
    SEL sel = sel_registerName("URLForResource:withExtension:subdirectory:");
    return ((MsgSendStr3)objc_msgSend)(bundle, sel, name, ext, subdir);
}

MT_INLINE MTURL mt_bundle_url_for_resource_in_subdir_with_localization(MTBundle bundle, MTString name, MTString ext, MTString subdir, MTString localization) {
    SEL sel = sel_registerName("URLForResource:withExtension:subdirectory:localization:");
    return ((MsgSendStr4)objc_msgSend)(bundle, sel, name, ext, subdir, localization);
}

MT_INLINE MTArray mt_bundle_urls_for_resources_in_subdir(MTBundle bundle, MTString ext, MTString subdir) {
    SEL sel = sel_registerName("URLsForResourcesWithExtension:subdirectory:");
    return ((id (*)(id, SEL, id, id))objc_msgSend)(bundle, sel, ext, subdir);
}

MT_INLINE MTArray mt_bundle_urls_for_resources_in_subdir_with_localization(MTBundle bundle, MTString ext, MTString subdir, MTString localization) {
    SEL sel = sel_registerName("URLsForResourcesWithExtension:subdirectory:localization:");
    return ((MsgSendStr3)objc_msgSend)(bundle, sel, ext, subdir, localization);
}

// --------- Class Methods (NSString* Return) ---------

MT_INLINE MTString mt_bundle_path_for_resource_in_dir(MTString name, MTString ext, MTString bundlePath) {
    SEL sel = sel_registerName("pathForResource:ofType:inDirectory:");
    Class cls = objc_getClass("NSBundle");
    return ((id (*)(id, SEL, id, id, id))objc_msgSend)((id)cls, sel, name, ext, bundlePath);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir(MTString ext, MTString bundlePath) {
    SEL sel = sel_registerName("pathsForResourcesOfType:inDirectory:");
    Class cls = objc_getClass("NSBundle");
    return ((id (*)(id, SEL, id, id))objc_msgSend)((id)cls, sel, ext, bundlePath);
}

MT_INLINE MTString mt_bundle_path_for_resource_(MTString name, MTString ext) {
    SEL sel = sel_registerName("pathForResource:ofType:");
    Class cls = objc_getClass("NSBundle");
    id mainBundle = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_registerName("mainBundle"));
    return ((id (*)(id, SEL, id, id))objc_msgSend)(mainBundle, sel, name, ext);
}

// --------- Instance Methods (NSString* Return) ---------

MT_INLINE MTString mt_bundle_path_for_resource(MTBundle bundle, MTString name, MTString ext) {
    SEL sel = sel_registerName("pathForResource:ofType:");
    return ((id (*)(id, SEL, id, id))objc_msgSend)(bundle, sel, name, ext);
}

MT_INLINE MTString mt_bundle_path_for_resource_in_dir_bundle(MTBundle bundle, MTString name, MTString ext, MTString subdir) {
    SEL sel = sel_registerName("pathForResource:ofType:inDirectory:");
    return ((id (*)(id, SEL, id, id, id))objc_msgSend)(bundle, sel, name, ext, subdir);
}

MT_INLINE MTString mt_bundle_path_for_resource_in_dir_with_localization(MTBundle bundle, MTString name, MTString ext, MTString subdir, MTString localization) {
    SEL sel = sel_registerName("pathForResource:ofType:inDirectory:forLocalization:");
    return ((MsgSendStr4)objc_msgSend)(bundle, sel, name, ext, subdir, localization);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir_instance(MTBundle bundle, MTString ext, MTString subdir) {
    SEL sel = sel_registerName("pathsForResourcesOfType:inDirectory:");
    return ((id (*)(id, SEL, id, id))objc_msgSend)(bundle, sel, ext, subdir);
}

MT_INLINE MTArray mt_bundle_paths_for_resources_in_dir_with_localization(MTBundle bundle, MTString ext, MTString subdir, MTString localization) {
    SEL sel = sel_registerName("pathsForResourcesOfType:inDirectory:forLocalization:");
    return ((MsgSendStr3)objc_msgSend)(bundle, sel, ext, subdir, localization);
}
