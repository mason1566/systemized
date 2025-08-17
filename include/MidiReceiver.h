#ifndef MIDI_RECEIVER
#define MIDI_RECEIVER

#include "MidiBase.h"

#include <functional>
#include <memory>

// Singleton
// Holds a callback: "std::function<void(const MidiMessage&)> onMessage;""
// Called when MIDI is received.
struct MidiReceiver : public MidiBase {
public:
    std::unique_ptr<libremidi::midi_in> midi_in;
public:
    MidiReceiver();
    void openPort(int id);
    void openPort(libremidi::input_port port);
    void setMidiCallbackFunction(std::function<void(const libremidi::message&)> callback) { externalMidiCallback = callback; };
    static std::vector<libremidi::input_port> getInputPorts();
    static size_t getInputPortCount();
private:
    std::function<void(const libremidi::message&)> externalMidiCallback;
private:
    void handleMidiCallback(const libremidi::message& message);
};

#endif