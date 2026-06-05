# Apple's Metal Graphics API for C

An unofficial C wrapper for Apple's Metal graphics API, inspired by the C++
[metal-cpp](https://github.com/bkaradzic/metal-cpp). It lets you use Metal from
a pure C codebase — game engines, renderers, tools — without writing
Objective-C or Swift.

<img width="1277" alt="Screenshot 2025-06-18 at 19 15 47" src="https://github.com/user-attachments/assets/f8f5b292-07fe-4263-81a9-d434e660d52a" />
<img width="1277" alt="Screenshot 2025-06-18 at 19 18 23" src="https://github.com/user-attachments/assets/ddf4cd85-3578-4cf8-93aa-c703785391e0" />

![Screen Recording 2024-06-04 at 20 40 15](https://github.com/Lu-TheCoder/Metal-C-API/assets/90724319/e7e6b8ae-378e-4c07-90b9-de645c5ff0c2)

It wraps both the classic Metal API (`mt_*`) and the new **Metal 4** command
model (`mt4_*`, SDK 26 / macOS 26), which coexist in the same library.

> [!WARNING]
> Still in active development and pre-1.0. The core is solid and the main paths
> are runtime-verified (see "Status"), but API names may still change and not
> every feature has been exercised on-device. Use at your own risk.

## How it works

The wrapper is **header-only**. Every function is a `static inline` that calls
the Objective-C runtime directly via type-cast `objc_msgSend`. There is no
library to link beyond the system frameworks — you just include the headers.

- **Targets ARM64 (Apple Silicon) only.** All `objc_msgSend` calls use the
  explicit function-pointer casts ARM64 requires; struct arguments and struct
  returns are handled correctly.
- **Type-safe handles.** Each Metal object is a distinct opaque pointer
  (`MTBuffer`, `MTTexture`, `MTDevice`, …), not `void*`, so the compiler catches
  mistakes like passing a texture where a buffer is expected. This costs nothing
  at runtime.
- **Manual memory management** (built with `-fno-objc-arc`). You release what you
  own — see the ownership rule below.

## Conventions

### Memory ownership — the one rule

> **`mt_*_create(...)` returns an object you own. Call `mt_release()` on it when
> done. Anything else — `mt_*_get_*(...)` and per-frame transients — you must
> NOT release.**

| Pattern | Ownership | Release? | Examples |
|---|---|---|---|
| `mt_*_create(...)` | **+1, you own it** | **Yes** | `mt_device_create_buffer_with_length`, `mt_render_pipeline_descriptor_create`, `mt_texture_descriptor_create`, `mt_library_create_function` |
| `mt_*_get_*(...)` | borrowed | No | `mt_buffer_get_contents`, `mt_device_get_name` |
| Per-frame transients | autoreleased | No (the autoreleasepool owns them) | `mt_command_queue_get_command_buffer`, `mt_command_buffer_get_render_encoder`, `cametal_layer_next_drawable` |

Wrap your frame in an `autoreleasepool { ... }` block (provided by the wrapper)
so the transients are cleaned up automatically.

### Error handling

Functions that can fail take an `MTError*` out-parameter (mirrors Metal's
`NSError**`):

```c
MTError error = NULL;
MTLibrary library = mt_device_create_library_with_url(device, fileURL, &error);
if (!library) {
    printf("Failed: %s\n", mt_error_get_localized_description(error));
}
```

## Basic usage

```c
#include "Metal/Metal.h"
#include "Metal/MTFoundation/Foundation.h"

int main(void) {
    // ... create your window / CAMetalLayer (platform-specific) ...

    MTDevice device = mt_create_system_default_device();
    MTCommandQueue queue = mt_device_create_command_queue(device);

    // Load a precompiled .metallib and grab the shader functions.
    MTError error = NULL;
    MTURL url = mt_bundle_url_for_resource_(mt_string_from_utf8("default"),
                                            mt_string_from_utf8("metallib"));
    MTLibrary library = mt_device_create_library_with_url(device, url, &error);
    mt_release(url);
    if (!library) {
        printf("Failed to load library: %s\n", mt_error_get_localized_description(error));
        return 1;
    }

    MTFunction vertFn = mt_library_create_function(library, mt_string_from_utf8("vert"));
    MTFunction fragFn = mt_library_create_function(library, mt_string_from_utf8("frag"));
    mt_release(library); // functions retain what they need

    // Vertex layout.
    MTVertexDescriptor vertDesc = mt_vertex_descriptor_create();
    mt_vertex_descriptor_set_vertex_attribute(vertDesc, 0, MTVertexFormatFloat3, 0, 0);
    mt_vertex_descriptor_set_vertex_layout(vertDesc, 0, sizeof(float) * 3, 1,
                                           MTVertexStepFunctionPerVertex);

    // Pipeline.
    MTRenderPipelineDescriptor pipeDesc = mt_render_pipeline_descriptor_create();
    mt_render_pipeline_descriptor_set_label(pipeDesc, "Default Pipeline");
    mt_render_pipeline_descriptor_set_vertex_function(pipeDesc, vertFn);
    mt_render_pipeline_descriptor_set_fragment_function(pipeDesc, fragFn);
    mt_render_pipeline_descriptor_set_vertex_descriptor(pipeDesc, vertDesc);
    mt_render_pipeline_descriptor_set_color_attachments_pixel_format(pipeDesc, 0, MTPixelFormatBGRA8Unorm);

    MTRenderPipelineState pipeline = mt_device_create_render_pipeline_state(device, pipeDesc, &error);
    if (!pipeline) {
        printf("Pipeline failed: %s\n", mt_error_get_localized_description(error));
        return 1;
    }

    float verts[] = { -0.5f, 0.5f, 0.0f,  -0.5f, -0.5f, 0.0f,  0.5f, -0.5f, 0.0f };
    MTBuffer vbuf = mt_device_create_buffer_with_bytes(device, verts, sizeof(verts),
                                                       MTResourceStorageModeShared);

    // These were created (+1) and are no longer needed.
    mt_release(vertFn);
    mt_release(fragFn);
    mt_release(vertDesc);
    mt_release(pipeDesc);

    bool running = true;
    while (running) {
        // running = platform_pump_messages();

        autoreleasepool {
            // next drawable + command buffer + encoder are transients:
            // do NOT release them.
            CAMetalDrawable drawable = platform_get_next_drawable();
            MTCommandBuffer cmd = mt_command_queue_get_command_buffer(queue);

            MTRenderPassDescriptor pass = mt_render_pass_create();
            MTRenderPassColorAttachmentDescriptor ca = mt_render_pass_color_attachment(pass, 0);
            mt_render_pass_color_attachment_set_texture(ca, cametal_drawable_get_texture(drawable));
            mt_render_pass_color_attachment_set_load_action(ca, MTLoadActionClear);
            mt_render_pass_color_attachment_set_store_action(ca, MTStoreActionStore);
            mt_render_pass_color_attachment_set_clear_color(ca, mt_clear_color(0.1, 0.1, 0.1, 1.0));

            MTRenderCommandEncoder enc = mt_command_buffer_get_render_encoder(cmd, pass);
            mt_release(pass); // the render pass descriptor IS owned (+1)

            mt_render_command_encoder_set_viewport(enc, mt_viewport_make(0, 0, 1024, 768, 0, 1));
            mt_render_command_encoder_set_pipeline_state(enc, pipeline);
            mt_render_command_encoder_set_vertex_buffer(enc, vbuf, 0, 0);
            mt_render_command_encoder_draw_primitives(enc, MTPrimitiveTypeTriangle, 0, 3);
            mt_render_command_encoder_end_encoding(enc);

            mt_command_buffer_present_drawable(cmd, (MTDrawable)drawable);
            mt_command_buffer_commit(cmd);
        } // transients (drawable, cmd, enc) released here
    }

    mt_release(vbuf);
    mt_release(pipeline);
    mt_release(queue);
    mt_release(device);
    return 0;
}
```

> Note: `mt_render_pass_create()` returns an owned (+1) descriptor, so it is
> released explicitly. The drawable, command buffer, and encoder are transients
> owned by the `autoreleasepool` — they are never released by hand.

## Metal 4 (`mt4_*`)

The wrapper also covers Apple's **Metal 4** command model (macOS 26+), exposed
under the `mt4_*` prefix and distinct `MT4*` handles. It coexists with the
classic API — use whichever you need. The Metal 4 model differs in a few ways:

- **Explicit command submission** — `MT4CommandQueue` + reusable
  `MT4CommandBuffer` + a ring of `MT4CommandAllocator`s, paced with an
  `MTSharedEvent`.
- **Argument tables** (`MT4ArgumentTable`) replace `setBuffer:atIndex:` — you
  bind by GPU address (`mt_buffer_get_gpu_address`) or `MTResourceID`
  (`mt_texture_get_gpu_resource_id`).
- **Residency sets** (`MTResidencySet`) — you make resources resident explicitly.
- **An explicit compiler** (`MT4Compiler`) builds pipeline states (sync + async),
  with on-disk caching via archives + pipeline-data-set serializers.
- Stage-based **barriers** for synchronizing across encoders.

A Metal 4 frame, in outline:

```c
// --- setup (once) ---
MT4Compiler      compiler  = mt4_device_create_compiler(device, compilerDesc, &error);
MT4CommandQueue  queue     = mt4_device_create_command_queue(device);
MT4CommandBuffer cmd       = mt4_device_create_command_buffer(device);
MT4CommandAllocator alloc[3] = { /* mt4_device_create_command_allocator(device) x3 */ };
MT4ArgumentTable argTable  = mt4_device_create_argument_table(device, atDesc, &error);
MTResidencySet   residency = mt_device_create_residency_set(device, rsDesc, &error);
// add resources to `residency`, commit, then mt4_command_queue_add_residency_set(queue, residency)

// --- per frame ---
mt_shared_event_wait_until_signaled_value(frameEvent, frameIndex - 3, 100);
mt4_command_allocator_reset(alloc[frameIndex % 3]);
mt4_command_buffer_begin(cmd, alloc[frameIndex % 3]);

MT4RenderCommandEncoder enc = mt4_command_buffer_get_render_encoder(cmd, passDesc);
mt4_render_command_encoder_set_pipeline_state(enc, pipeline);
mt4_render_command_encoder_set_argument_table(enc, argTable, MTLRenderStageVertex | MTLRenderStageFragment);
mt4_argument_table_set_address(argTable, mt_buffer_get_gpu_address(vbuf), 0);
mt4_render_command_encoder_draw_primitives(enc, MTPrimitiveTypeTriangle, 0, 3);
mt4_command_encoder_end_encoding((MT4CommandEncoder)enc);  // shared base-encoder ops take MT4CommandEncoder

mt4_command_buffer_use_residency_set(cmd, cametal_layer_get_residency_set(layer)); // drawable residency
mt4_command_buffer_end(cmd);

mt4_command_queue_wait_for_drawable(queue, (MTDrawable)drawable);
mt4_command_queue_commit(queue, &cmd, 1);
mt4_command_queue_signal_event(queue, (MTEvent)frameEvent, frameIndex++);
mt4_command_queue_signal_drawable(queue, (MTDrawable)drawable);
mt_drawable_present((MTDrawable)drawable);
```

Compute works the same way via `mt4_command_buffer_get_compute_encoder` +
`mt4_compute_command_encoder_dispatch_threads`; an `MT4MachineLearningCommandEncoder`
is available too. Synchronize across encoders with the base-encoder barriers
(`mt4_command_encoder_barrier_after_stages`, etc.).

## Shader reflection

Request reflection at pipeline-build time, then walk the bindings:

```c
// Metal 4: MT4PipelineOptions opts; mt4_pipeline_options_set_shader_reflection(opts, MT4ShaderReflectionBindingInfo);
//          mt4_render_pipeline_descriptor_set_options(desc, opts);
MTRenderPipelineReflection r = mt_render_pipeline_state_get_reflection(pipeline);
MTArray bindings = mt_render_pipeline_reflection_get_vertex_bindings(r);
for (NSUInteger i = 0; i < mt_array_get_count(bindings); i++) {
    MTBinding b = mt_array_get_binding_at_index(bindings, i);
    printf("%s (type %d, index %lu)\n", mt_string_to_utf8(mt_binding_get_name(b)),
           mt_binding_get_type(b), (unsigned long)mt_binding_get_index(b));
}
```

The full reflection type graph (`MTBinding`, `MTBufferBinding`, `MTStructType`,
`MTArrayType`, `MTPointerType`, …) is in `MTArgument.h`.

## Building

The repo ships a small macOS demo (`Metal C/main.c`) — currently a **Metal 4
compute test**: a compute shader writes an animated plasma into a texture, which
the render path then displays fullscreen.

```sh
make        # compiles shaders + the demo into ./bin/metal_app
make run    # build and launch
make clean
```

The build is ARM64, `-Wall -Wextra`, ARC disabled (`-fno-objc-arc`), linking
`Foundation`, `QuartzCore`, `Cocoa`, and `Metal`. There is also an Xcode project
(`Metal C.xcodeproj`) that builds the same demo. Run with the Metal validation
layer via `MTL_DEBUG_LAYER=1` to catch API/GPU misuse.

> Shaders live in `Metal C/shaders/`. New `.metal` files must be registered in
> **both** the `Makefile` and the Xcode project, or terminal and Xcode runs will
> diverge.

To use the wrapper in **your own** project, add `Metal C/Metal` to your include
path and `#include "Metal/Metal.h"` (or include just the individual headers you
need — they're self-contained). The headers are platform-agnostic; you provide
your own windowing / `CAMetalLayer` (the macOS demo windowing under
`Metal C/Platform/macos` is not part of the wrapper).

The `mt_*` (classic) path runs on any Apple Silicon Mac; the `mt4_*` (Metal 4)
path requires **macOS 26+**.

## Status

**Production-capable for the proven core paths; not yet fully hardened.**

Solid and **runtime-verified** on real macOS 26 hardware under the Metal API +
GPU validation layer (zero validation errors):

- Correct ARM64 `objc_msgSend` bridging (struct args/returns included), cached
  selectors/classes, type-safe opaque handles, one clear ownership rule.
- Every header compiles **standalone** (include just what you use).
- **Classic Metal 3 render path** — full frame render.
- **Metal 4 render path** — queue/allocator/command buffer, argument tables,
  residency sets, the explicit compiler, shared-event pacing, present.
- **Metal 4 compute path** — compute dispatch, writable-texture binding,
  compute→fragment barrier, then sampled by the render path.
- **Shader reflection** — classic + Metal 4 binding enumeration.
- GPU residency + synchronization (fences, events, memory barriers).

Broad coverage across: device, command queue/buffer, render/compute/blit
encoders, render & compute pipelines, buffers, textures, samplers,
depth/stencil, heaps, indirect command buffers, fast resource loading (MTLIO) +
compression, binary archives, libraries (sync + async). Metal 4: command
submission, argument tables, residency, compiler (+ async/archives/serializers),
counters/timestamps, commit feedback, ML pipeline + encoder.

Not yet done / honest gaps:

- **No automated test suite** — verification so far is smoke compiles + manual
  on-device runs under validation. This is the top item before "production".
- **Ray tracing / acceleration structures: not ported** (a large subsystem
  built on classic acceleration-structure descriptors — deferred).
- **Some Metal 4 features compile but haven't been run on-device yet**: counters,
  async compile, archives/serializers, commit feedback, the ML encoder/pipeline.
- Validated on a **single GPU/OS configuration** only.
- Minor: `NSUInteger`/`CFTimeInterval` are redefined (relies on C11 identical-
  typedef); no formal null-handle contract; some naming inconsistencies
  (`mt_render_pass_*` vs `mt_render_pass_*`, `mt_string_*` vs `mt_string_*`).

## Contributions

PRs welcome. The codebase is C (header-only inline wrappers). When adding
functions, follow the ownership naming rule: `mt_*_create` for objects the
caller owns (+1), `mt_*_get_*` / transient names for borrowed objects.
