#ifndef AUDIO_IO
#define AUDIO_IO

#include "miniaudio.h"

struct AudioIO
{
public:
    static AudioIO& getInstance();
    void printDevices();
private:
    static ma_context& getContext();
    AudioIO();
};

#endif