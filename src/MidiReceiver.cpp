#include "MidiReceiver.h"

#include <iostream>

MidiReceiver::MidiReceiver()
{
    // Create lambda expression callback function for midi message handling
    auto callback = [this](libremidi::message&& message) {
       handleMidiCallback(message);
    };

    midi_in = std::make_unique<libremidi::midi_in>(
        libremidi::input_configuration{ .on_message = callback }
    );

    // midi_in->open_port(getMidiObserver().get_input_ports()[0]);
}

void MidiReceiver::handleMidiCallback(const libremidi::message& message)
{
    if (externalMidiCallback) {
        externalMidiCallback(message);
    }
    else
        std::cout << "MIDI Input Received!\n";
}

void MidiReceiver::openPort(int id)
{
    if (id < 0 || id >= getInputPortCount())
        return;
    
    midi_in->open_port(getInputPorts()[id]);
}

void MidiReceiver::openPort(libremidi::input_port port)
{
    midi_in->open_port(port);
}

std::vector<libremidi::input_port> MidiReceiver::getInputPorts()
{
    return getMidiObserver().get_input_ports();
}

size_t MidiReceiver::getInputPortCount()
{
    return getMidiObserver().get_input_ports().size();
}