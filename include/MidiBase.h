#ifndef MIDI_BASE
#define MIDI_BASE

#include <libremidi/libremidi.hpp>
#include <vector>

struct MidiBase {
protected:
    static libremidi::observer& getMidiObserver()
    {
        static libremidi::observer observer;
        return observer;
    }
};

#endif