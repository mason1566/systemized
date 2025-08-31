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
    static ma_context context;
    return context;
}

AudioIO::AudioIO()
{
    if (ma_context_init(NULL, 0, NULL, &getContext()) != MA_SUCCESS) {
        throw std::runtime_error("Miniaudio Error: Context object could not initialize");
    }
}

AudioIO::~AudioIO()
{
    ma_context_uninit(&getContext());
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

AudioPlaybackDevice::AudioPlaybackDevice()
{
    ma_device_config config = ma_device_config_init(ma_device_type_playback);
    config.playback.format   = ma_format_f32;   // Set to ma_format_unknown to use the device's native format.
    config.playback.channels = 2;               // Set to 0 to use the device's native channel count.
    config.sampleRate        = 48000;           // Set to 0 to use the device's native sample rate.
    config.dataCallback      = dataCallback;   // This function will be called when miniaudio needs more data.
    config.pUserData         = (void*)this;   // Can be accessed from the device object (device.pUserData).

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        throw std::runtime_error("Error in AudioDevice: Failed to initialize the device.");
    }

    ma_device_start(&device);     // The device is sleeping by default so you'll need to start it manually.
}

AudioCaptureDevice::AudioCaptureDevice()
{
    ma_device_config config = ma_device_config_init(ma_device_type_capture);
    config.playback.format   = ma_format_f32;   // Set to ma_format_unknown to use the device's native format.
    config.playback.channels = 2;               // Set to 0 to use the device's native channel count.
    config.sampleRate        = 48000;           // Set to 0 to use the device's native sample rate.
    config.dataCallback      = dataCallback;   // This function will be called when miniaudio needs more data.
    config.pUserData         = (void*)this;   // Can be accessed from the device object (device.pUserData).

    if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
        throw std::runtime_error("Error in AudioDevice: Failed to initialize the device.");
    }

    ma_device_start(&device);     // The device is sleeping by default so you'll need to start it manually.
}

AudioDevice::~AudioDevice()
{
    ma_device_uninit(&device);
}

// Static
void AudioDevice::dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    // Call device-specific data callback function
    ((AudioDevice*)pDevice->pUserData)->customDataCallback(pDevice, pOutput, pInput, frameCount);
}

void AudioCaptureDevice::customDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    std::cout << "Input Device Data Callback Called!\n";
}

void AudioPlaybackDevice::customDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    std::cout << "Output Device Data Callback Called!\n";
}
