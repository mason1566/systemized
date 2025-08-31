#include <iostream>
#include <format>
#include <vector>
#include "ConsoleUtils.h"
#include "MidiIO.h"
#include "AudioIO.h"

enum class AudioCommand
{

};

struct UserCommand
{
    enum Command : int { Placeholder } test;

    void executeCommand()
    {
        switch (test)
        {
            case Command::Placeholder:
                placeholder();
                break;
            default:
                break;
        }
    }

    std::string toString()
    {
        int commandIndex { static_cast<int>(Command::Placeholder) };
        return getCommandStrings()[commandIndex];
    }

    static const std::vector<std::string>& getCommandStrings()
    {
        static const std::vector<std::string> commandStrings { "Placeholder" };
        return commandStrings;
    }
private:
    static void placeholder()
    {
        std::cout << "Placeholder\n";
    }
};

int main() 
{
    TerminalRawMode rawMode;

    ConsoleInput::clearConsole();

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

        auto callback = [](const libremidi::message& message) 
        {  
            std::cout << message.timestamp << "\n";
        };

        midiReceive.setMidiCallbackFunction(callback);
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

    AudioIO& audio { AudioIO::getInstance() };
    audio.printDevices();

    // std::vector<std::string> strings { "Hello", "Hi", "Howdily Doodily", "1", "2", "3", "4", "5", "6", "7", "8", "9", "i", "need", "more", "entries", "to", "test", "this", "dang", "thing" };
    // int selection = ConsoleInput::getSelectionFromUser(strings);
    // std::cout << strings[selection] << "\n";

    // int selection = ConsoleInput::getSelectionFromUser(UserCommand::getCommandStrings());
    // std::cout << UserCommand::getCommandStrings()[selection] << "\n";
    // UserCommand command;
    // command.test = static_cast<UserCommand::Command>(selection);
    // command.executeCommand();

    std::cin.get();

    return 0;
}