#include <iostream>
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

    if (MidiSender::getOutputPortCount() == 0)
    {
        std::cout << "No MIDI Output Ports Available.\n";
    }

    return 0;
}