#include "MidiReceiver.h"

#include <iostream>

MidiReceiver::MidiReceiver()
{
    // Create lambda expression callback function for midi message handling
    auto callback = [this](libremidi::message&& message) {
       std::cout << "MIDI INPUT!\n";
    };

    midi_in = std::make_unique<libremidi::midi_in>(
        libremidi::input_configuration{ .on_message = callback }
    );

    // midi_in->open_port(getMidiObserver().get_input_ports()[0]);
}

void MidiReceiver::openPort(int id)
{
    if (id < 0 || id >= getInputPortCount())
        return;
    
    midi_in->open_port(getInputPorts()[id]);
}

std::vector<libremidi::input_port> MidiReceiver::getInputPorts()
{
    return getMidiObserver().get_input_ports();
}

size_t MidiReceiver::getInputPortCount()
{
    return getMidiObserver().get_input_ports().size();
}