#ifndef MIDI_SENDER
#define MIDI_SENDER

#include "MidiBase.h"

#include <vector>

struct MidiSender : protected MidiBase {
    libremidi::midi_out midi_out;
    MidiSender();
    void openPort(int id);
    static std::vector<libremidi::output_port> getOutputPorts();
    static size_t getOutputPortCount();
};

#endif