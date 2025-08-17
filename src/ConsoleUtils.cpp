#include "ConsoleUtils.h"

// From chatgpt
// struct TerminalRawMode 
// {
//     termios origTermios;

//     TerminalRawMode() {
//         tcgetattr(STDIN_FILENO, &origTermios);
//         termios raw = origTermios;
//         raw.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
//         tcsetattr(STDIN_FILENO, TCSANOW, &raw);
//     }

//     ~TerminalRawMode() {
//         tcsetattr(STDIN_FILENO, TCSANOW, &origTermios); // restore on exit
//     }
// };

// struct ConsoleIO
// {
//     // returns the amount of characters ready to be read
//     static int getInputBufferCharCount()
//     {
//         return std::cin.rdbuf()->in_avail();
//     }

//     static void clearInputBuffer()
//     {
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//     }

//     // Blocking
//     static char getDigitFromUser()
//     {
//         char ch;
//         do {
//             ch = std::cin.get();
//         } while (!std::isdigit(ch));
//         return ch;
//     }

//     // Blocking
//     static char getLetterFromUser()
//     {
//         char ch;
//         do {
//             ch = std::cin.get();
//         } while (!std::isalpha(ch));
//         return ch;
//     }

//     // Blocking
//     static char getLetterOrDigitFromUser()
//     {
//         char ch;
//         do {
//             ch = std::cin.get();
//         } while (!isalnum(ch));
//         return ch;
//     }    

//     static void clearConsole() 
//     {
//         std::cout << "\033[2J\033[H"; // clear screen and move cursor to home. (ANSI Escape Codes)
//     }
// };

// ---------------- TerminalRawMode ----------------
TerminalRawMode::TerminalRawMode() {
    tcgetattr(STDIN_FILENO, &origTermios);
    termios raw = origTermios;
    raw.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

TerminalRawMode::~TerminalRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &origTermios); // restore on exit
}

// ---------------- ConsoleInput ----------------
int ConsoleInput::getInputBufferCharCount() {
    return std::cin.rdbuf()->in_avail();
}

void ConsoleInput::clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char ConsoleInput::getDigitFromUser() {
    char ch;
    do { ch = std::cin.get(); } while (!std::isdigit(ch));
    return ch;
}

char ConsoleInput::getLetterFromUser() {
    char ch;
    do { ch = std::cin.get(); } while (!std::isalpha(ch));
    return ch;
}

char ConsoleInput::getLetterOrDigitFromUser() {
    char ch;
    do { ch = std::cin.get(); } while (!std::isalnum(ch));
    return ch;
}

void ConsoleInput::clearConsole() {
    std::cout << "\033[2J\033[H";
}