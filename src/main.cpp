#include <iostream>
#include "ConsoleUtils.h"

int main() 
{
    TerminalRawMode rawMode;

    ConsoleInput::clearConsole();

    char input;
    while (true)
    {
        std::cout << "Enter a character: ";
        input = ConsoleInput::getLetterOrDigitFromUser();
        std::cout << input << "\n";
    }
    return 0;
}