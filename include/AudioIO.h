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
    ~AudioIO();
};

struct AudioDevice
{
public:
    virtual ~AudioDevice();
protected:
    static void dataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

    ma_device device;
    virtual void customDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) = 0;
};

struct AudioPlaybackDevice : protected AudioDevice
{
public:
    AudioPlaybackDevice();
protected:
    void customDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) override;
};

struct AudioCaptureDevice : protected AudioDevice
{
public:
    AudioCaptureDevice();
protected:
    void customDataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) override;
};

#endif