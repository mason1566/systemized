#ifndef MIDI_RECEIVER
#define MIDI_RECEIVER

#include "MidiBase.h"

#include <functional>
#include <memory>

// Singleton
// Holds a callback: "std::function<void(const MidiMessage&)> onMessage;""
// Called when MIDI is received.
struct MidiReceiver : protected MidiBase {
    std::unique_ptr<libremidi::midi_in> midi_in;
    MidiReceiver();
    void openPort(int id);
    static std::vector<libremidi::input_port> getInputPorts();
    static size_t getInputPortCount();
};

#endif