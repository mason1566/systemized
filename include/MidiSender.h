#ifndef MIDI_SENDER
#define MIDI_SENDER

#include "MidiBase.h"

class MidiSender : protected MidiBase {
public:
    // Singleton instance function
    static MidiSender& instance();
private:
    libremidi::midi_out midi_out;

    MidiSender();
};

#endif