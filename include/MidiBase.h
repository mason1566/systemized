#ifndef MIDI_BASE
#define MIDI_BASE

#include <libremidi/libremidi.hpp>
#include <vector>
#include <string>
#include <sstream>

struct MidiBase {
    template<typename Port>
    static std::string getPortInformation(const Port& port)
    {
        std::stringstream str;
        str << port.display_name << ":\n";
        str << "  DEVICE NAME: " << port.device_name << "\n";
        str << "  MANUFACTURER: " << port.manufacturer << "\n";
        str << "  PORT NAME: " << port.port_name << "\n";
        return str.str();
    }
protected:
    static libremidi::observer& getMidiObserver()
    {
        static libremidi::observer observer;
        return observer;
    }
};

#endif