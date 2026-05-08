#pragma once

namespace Flagging {
    enum class FlagContext {
        KEY_FLAG = 0,                   // Key flags
        PREPROCESS_FLAG,                // Preprocessing flags
        RUNTIME_FLAG,                   // Runtime flags, ciphers
        POSTPROCESS_FLAG                // Postprocess flags
    };                                  // Flag context, these can also be seen as priority values, we will make sure the gFlags global 
                                        // is populated in earlier indeces with preprocessing flags, then runtime flags and finally postprocessing flags
} // Flagging