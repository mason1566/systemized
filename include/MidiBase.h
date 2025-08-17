#ifndef MIDI_BASE
#define MIDI_BASE

#include <libremidi/libremidi.hpp>

class MidiBase {
public:
    static libremidi::observer& getMidiObserver()
    {
        static libremidi::observer observer;
        return observer;
    }
};

#endif