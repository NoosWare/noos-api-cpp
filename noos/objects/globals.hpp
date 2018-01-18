#ifndef NOOS_OBJECTS_GLOBALS
#define NOOS_OBJECTS_GLOBALS
namespace noos {
/// @brief Type-defined namespace
namespace types {    
/// @brief Clarification 
typedef char byte;

/// @brief Audio sources allowed in speech classes
enum audio_source 
{ 
    nao_ogg = 0, 
    nao_wav_1_ch = 1, 
    nao_wav_4_ch = 2,
    headset = 3 
};

}
}
#endif
