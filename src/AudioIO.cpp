#define MINIAUDIO_IMPLEMENTATION
#include "AudioIO.h"
#include <stdexcept>
#include <iostream>

// singleton
AudioIO& AudioIO::getInstance()
{
    static AudioIO audio;
    return audio;
}

ma_context& AudioIO::getContext()
{
    // struct ContextWrapper {
    //     ma_context context;

    //     ContextWrapper() {
    //         if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS) {
    //             throw std::runtime_error("Miniaudio Error: Context object could not initialize");
    //         }
    //     }

    //     ~ContextWrapper() {
    //         ma_context_uninit(&context);
    //     }
    // };

    // static ContextWrapper wrapper {};
    // return wrapper.context;
    static ma_context context;
    return context;
}

AudioIO::AudioIO()
{
    if (ma_context_init(NULL, 0, NULL, &getContext()) != MA_SUCCESS) {
        throw std::runtime_error("Miniaudio Error: Context object could not initialize");
    }
}

void AudioIO::printDevices()
{
    ma_device_info* pPlaybackInfos;
    ma_uint32 playbackCount;
    ma_device_info* pCaptureInfos;
    ma_uint32 captureCount;
    if (ma_context_get_devices(&getContext(), &pPlaybackInfos, &playbackCount, &pCaptureInfos, &captureCount) != MA_SUCCESS) 
    {
        // Error.
        throw std::runtime_error("Miniaudio Error: Context failed when fetching devices\n");
    }

    std::cout << "\nPlayback Devices:\n";

    // Loop over each device info and do something with it. Here we just print the name with their index. You may want
    // to give the user the opportunity to choose which device they'd prefer.
    for (ma_uint32 i = 0; i < playbackCount; i++) 
    {
        std::cout << "  [" << i+1 << "] " << pPlaybackInfos[i].name << "\n";
    }

    std::cout << "\nCapture Devices:\n";
    for (ma_uint32 i = 0; i < captureCount; i++)
    {
        std::cout << "  [" << i+1 << "] " << pCaptureInfos[i].name << "\n";
    }
}