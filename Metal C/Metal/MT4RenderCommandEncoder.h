//
//  MT4RenderCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once

typedef enum MT4RenderEncoderOptions {
    /// Declares that this render pass doesn't suspend nor resume.
    MT4RenderEncoderOptionNone       = 0,
    
    /// Configures the render pass as *suspending*.
    ///
    /// Pass this option to ``MTL4CommandBuffer/renderCommandEncoderWithDescriptor:options:`` to specify that Metal can
    /// stitch the work a render command encoder encodes with a subsequent "resuming" render command encoder.
    MT4RenderEncoderOptionSuspending = (1 << 0),
    
    /// Configures the render pass to as *resuming*.
    ///
    /// Pass this option to ``MTL4CommandBuffer/renderCommandEncoderWithDescriptor:options:`` to specify that Metal can
    /// stitch the work a render command encoder encodes with a prior "suspending" render command encoder.
    MT4RenderEncoderOptionResuming   = (1 << 1)
} MT4RenderEncoderOptions;

