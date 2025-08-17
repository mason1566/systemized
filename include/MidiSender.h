#ifndef MIDI_SENDER
#define MIDI_SENDER

#include "MidiBase.h"

#include <vector>

struct MidiSender : public MidiBase {
    libremidi::midi_out midi_out;
    MidiSender();
    void openPort(int id);
    void openPort(libremidi::output_port port);
    static std::vector<libremidi::output_port> getOutputPorts();
    static size_t getOutputPortCount();
};

#endif