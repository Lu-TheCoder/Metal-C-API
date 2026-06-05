//
//  MT4MachineLearningCommandEncoder.h
//  Metal C
//
//  MTL4MachineLearningCommandEncoder — dispatches ML networks on Apple silicon.
//  Obtain one from mt4_command_buffer_get_machine_learning_encoder.
//
//  Bind a machine-learning pipeline state and an argument table (the network's
//  inputs), then dispatch, providing a heap Metal uses for intermediate
//  tensors. Query the required heap size from the pipeline state (Stage 4).
//
//  Shared ops (barriers, fences, debug, end_encoding) are in MT4CommandEncoder.h
//  — cast this encoder to MT4CommandEncoder.
//

#pragma once
#include "MTFoundation/defines.h"

MT_INLINE void mt4_machine_learning_command_encoder_set_pipeline_state(MT4MachineLearningCommandEncoder encoder, MT4MachineLearningPipelineState state) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setPipelineState:"), id, state);
}

MT_INLINE void mt4_machine_learning_command_encoder_set_argument_table(MT4MachineLearningCommandEncoder encoder, MT4ArgumentTable table) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setArgumentTable:"), id, table);
}

// Dispatch the network. `heap` provides scratch space for intermediate tensors;
// size it with the pipeline state's intermediatesHeapSize.
MT_INLINE void mt4_machine_learning_command_encoder_dispatch_network(MT4MachineLearningCommandEncoder encoder, MTHeap intermediates_heap) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("dispatchNetworkWithIntermediatesHeap:"), id, intermediates_heap);
}
