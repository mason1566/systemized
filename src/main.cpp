#include <iostream>
#include <format>
#include "ConsoleUtils.h"
#include "MidiReceiver.h"
#include "MidiSender.h"

int main() 
{
    TerminalRawMode rawMode;

    ConsoleInput::clearConsole();

    // char input;
    // while (true)
    // {
    //     std::cout << "Enter a character: ";
    //     input = ConsoleInput::getLetterOrDigitFromUser();
    //     std::cout << input << "\n";
    // }

    MidiReceiver midiReceive;
    MidiSender midiSend;

    if (MidiReceiver::getInputPortCount() == 0)
    {
        std::cout << "No MIDI Input Ports Available.\n";
    }
    else
    {
        std::cout << "INPUT PORTS:\n";
        std::vector<libremidi::input_port> inputPorts { MidiReceiver::getInputPorts() };
        for (int i = 0; i < inputPorts.size(); i++)
        {
            // std::cout << std::format("  [{}] {} {}\n", i + 1, inputPorts[i].manufacturer, inputPorts[i].display_name);
            std::cout << "[" << i+1 << "] " << MidiReceiver::getPortInformation(inputPorts[i]);
        }

        midiReceive.openPort(0);
    }

    std::cout << "\n";

    if (MidiSender::getOutputPortCount() == 0)
    {
        std::cout << "No MIDI Output Ports Available.\n";
    }
    else
    {
        std::cout << "OUTPUT PORTS:\n";
        std::vector<libremidi::output_port> outputPorts { MidiSender::getOutputPorts() };
        for (int i = 0; i < outputPorts.size(); i++)
        {
            // std::cout << std::format("  [{}] {} {}\n", i + 1, outputPorts[i].manufacturer, outputPorts[i].display_name);
            std::cout  << "[" << i+1 << "] " << MidiSender::getPortInformation(outputPorts[i]);
        }

        midiSend.openPort(0);
    }

    std::cin.get();

    return 0;
}