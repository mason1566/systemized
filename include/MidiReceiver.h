#ifndef MIDI_RECEIVER
#define MIDI_RECEIVER

#include "MidiBase.h"

#include <functional>

// Singleton
// Holds a callback: "std::function<void(const MidiMessage&)> onMessage;""
// Called when MIDI is received.
class MidiReceiver : protected MidiBase {
public:
    std::unique_ptr<libremidi::midi_in> midi_in;

    // Singleton instance function
    static MidiReceiver& instance();
private:
    MidiReceiver();
};

#endif