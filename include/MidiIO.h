#ifndef MIDI_BASE
#define MIDI_BASE

#include <libremidi/libremidi.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <memory>

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

struct MidiSender : public MidiBase {
    libremidi::midi_out midi_out;
    MidiSender();
    void openPort(int id);
    void openPort(libremidi::output_port port);
    static std::vector<libremidi::output_port> getOutputPorts();
    static size_t getOutputPortCount();
};

#endif