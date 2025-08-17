#include "MidiSender.h"

#include <iostream>

MidiSender::MidiSender() {
    // midi_out.open_port(getMidiObserver().get_output_ports()[0]);
}

void MidiSender::openPort(int id)
{
    if (id < 0 || id >= getOutputPortCount())
        return;
    
    midi_out.open_port(getOutputPorts()[id]);
}

std::vector<libremidi::output_port> MidiSender::getOutputPorts()
{
    return getMidiObserver().get_output_ports();
}

size_t MidiSender::getOutputPortCount()
{
    return getMidiObserver().get_output_ports().size();
}

// void MidiSender::setPadRGB(int padNumber, RGB colour) {
//     // Midi sysex message format for controlling drumpad LED values is as follows:
//     // { 
//     //      msg_start, mfg_id, dev_id, model_id, msg_type, data_length, data_length_2, 
//     //      PAD_NUM, RED_VALUE (0-127), GREEN_VALUE (0-127), BLUE_VALUE (0-127), msg_end 
//     // }
//     // We are only interested in modifying the PAD_NUM, RED_VALUE, GREEN_VALUE, and BLUE_VALUE.
    
//     // Convert colour values into unsigned char. This is because midi_out.send_message expects unsigned char values

//     unsigned char padNum = static_cast<unsigned char>(padNumber);
//     unsigned char red = static_cast<unsigned char>(colour.getRed());
//     unsigned char green = static_cast<unsigned char>(colour.getGreen());
//     unsigned char blue = static_cast<unsigned char>(colour.getBlue());

//     unsigned char bytes[12] = { 
//         0xF0, 0x47, 0x47, 0x4A, 0x65, 0x00, 0x04, 
//         padNum, red, green, blue, 0xF7 
//     };
//     midi_out.send_message(bytes, sizeof(bytes));
// }