#ifndef CONSOLE_UTILS
#define CONSOLE_UTILS

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <string>

struct TerminalRawMode 
{
    termios origTermios;

    TerminalRawMode();
    ~TerminalRawMode();
};

struct ConsoleInput
{
    static int getInputBufferCharCount();
    static void clearInputBuffer();
    static char getDigitFromUser();
    static char getLetterFromUser();
    static char getLetterOrDigitFromUser();
    static void clearConsole();
    static int getSelectionFromUser(std::vector<std::string>& options);
};

// // From chatgpt
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

#endif