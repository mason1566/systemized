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

int ConsoleInput::getSelectionFromUser(std::vector<std::string>& options)
{
    const int MIN_DIGIT { 0 };
    const int MAX_DIGIT { 9 };
    const int OPTIONS_SIZE { (int) options.size() };

    int offset = 0;

    auto goNextPage = [&offset, &MAX_DIGIT, &OPTIONS_SIZE]()
    {
        if (offset == 0) // we are on page 1
        {
            offset += MAX_DIGIT - 1; // account for next-page option
        }
        else
        {
            offset += MAX_DIGIT - 2; // account for previous-page and next-page options
        }

        offset = (offset >= OPTIONS_SIZE) ? OPTIONS_SIZE - 1 : offset; // fix overshooting
    };

    auto goPrevPage = [&offset, &MAX_DIGIT, &OPTIONS_SIZE]()
    {
        if (offset)
        {
            offset -= MAX_DIGIT - 1; // account for previous and next page options
        }

        offset = (offset < 0) ? 0 : offset;
    };

    // Input loop. Repeat until valid input
    while (true)
    {
        clearConsole();

        // CASE 1: options fit on one page
        if (options.size() <= MAX_DIGIT + 1)
        {
            std::cout << "Select from the following:\n";
            for (int i = 0; i < options.size(); i++)
            {
                std::cout << "  [" << i << "] " << options[i] << "\n";
            }
            
            std::cout << "Selection: ";
            int userOption = getDigitFromUser() - '0'; // getDigitFromUser() returns a character
            
            if (userOption >= options.size())
                continue;
            else
                return userOption;
        }
        // CASE 2: options do not fit on one page and its the first page (requires next-page option)
        else if (offset == 0)
        {
            std::cout << "Select from the following:\n";
            int nextPageOptionIndex = MAX_DIGIT;

            for (int i = 0; i < nextPageOptionIndex; i++)
            {
                std::cout << "  [" << i << "] " << options[i] << "\n";
            }
            
            std::cout << "  [" << nextPageOptionIndex << "] NEXT PAGE\n";

            std::cout << "Selection: ";
            int userOption = getDigitFromUser() - '0';
            
            if (userOption == nextPageOptionIndex)
            {
                goNextPage();
                continue;
            }
            else
                return userOption;
        }
        // CASE 3: options do not fit on one page and it is NOT the first page (requires prev-page and next-page option)
        else if (offset > 0)
        {
            std::cout << "Select from the following:\n";
            bool hasNextPage { OPTIONS_SIZE - offset > MAX_DIGIT - 1 }; // minus 1 to account for prev-page option

            int prevPageOptionIndex = (hasNextPage) ? MAX_DIGIT - 1 : OPTIONS_SIZE - offset;
            int nextPageOptionIndex = (hasNextPage) ? MAX_DIGIT : (int) NULL;

            for (int i = 0; i < prevPageOptionIndex; i++)
            {
                std::cout << "  [" << i << "] " << options[i + offset] << "\n";
            }
            
            std::cout << "  [" << prevPageOptionIndex << "] PREVIOUS PAGE\n";

            if (hasNextPage)
                std::cout << "  [" << nextPageOptionIndex << "] NEXT PAGE\n";

            std::cout << "Selection: ";
            int userOption = getDigitFromUser() - '0';
            
            if (userOption == prevPageOptionIndex)
            {
                goPrevPage();
                continue;
            }
            else if (hasNextPage && userOption == nextPageOptionIndex)
            {
                goNextPage();
                continue;
            }
            else if (userOption > prevPageOptionIndex)
            {
                continue;
            }
            else
                return userOption + offset;
        }

        break;
    }

    // const int OPTIONS_PER_PAGE = 10;
    // int currentIndex = 0;

    // while (true) 
    // {
    //     clearConsole();

    //     // CASE 1: options fit on one page
    //     if (options.size() <= OPTIONS_PER_PAGE)
    //     {
    //         std::cout << "Select from the following:\n";
    //         for (int i = 0; i < options.size(); i++)
    //         {
    //             std::cout << "  [" << i << "] " << options[i] << "\n";
    //         }
            
    //         std::cout << "Selection: ";
    //         int userOption = getDigitFromUser() - '0'; // getDigitFromUser() returns a character
            
    //         if (userOption >= options.size())
    //             continue;
    //         else
    //             return userOption;
    //     }
    //     // CASE 2: options do not fit on one page (requires previous and next options)
    //     else
    //     {
    //         if (currentIndex) // If this is the first page, show a next page option
    //         {
    //             // TODO: Show a next page option
    //             int optionIndex;
    //             int nextPageOptionIndex = OPTIONS_PER_PAGE - 1;
    //             for (optionIndex = 0; optionIndex < options.size() || optionIndex < nextPageOptionIndex; optionIndex++)
    //             {
    //                 std::cout << "  [" << optionIndex << "] " << options[optionIndex] << "\n";
    //             }
    //             std::cout << "  [" << ++optionIndex << "] NEXT PAGE\n";

    //             std::cout << "Selection: ";
    //             int userOption = getDigitFromUser() - '0';
                
    //             if (userOption >= options.size())
    //                 continue;
    //             else if (userOption == nextPageOptionIndex)
    //             {
    //                 currentIndex += nextPageOptionIndex - 1;
    //                 continue;
    //             }
    //             else
    //                 return userOption;
    //         }
    //         else
    //         {
    //             // Determine if we need to show a nextPage option
    //             if (options.size() - currentIndex > OPTIONS_PER_PAGE)
    //         }
    //     }
    //     return 0;
    // }

    // int selection = -1;
    // do {
    //     std::cout << "Select from the following:\n";

    //     int index = 0;

    //     for (auto& option : options) 
    //     {
    //         std::cout << "  [" << index << "] " << option << "\n";
    //         index++;
    //     }
    // } while (selection == -1);
    return 0;
}


/*

// <= 10 options
Select an Option:
  [0] Option 1
  [1] Option 2
  [2] Option 3
  ...
  [9] Option 9
Selection: 

// > 10 options
// page 1
Select an Option:
  (page 1)
  [0] Option 1
  [1] Option 2
  [2] Option 3
  ...
  [8] Option 8

  [9] Next Page
Selection: 

// page 2
Select an Option:
  (page 3)
  [0] Option 9
  [1] Option 10
  [2] Option 11
  ...
  [7] Option 16

  [8] Previous Page
  [9] Next Page
Selection: 

// last page
Select an Option:
  (page 3)
  [0] Option 1
  [1] Option 2
  [2] Option 3
  [3] Option 4

  [4] Previous Page
Selection: 
*/
