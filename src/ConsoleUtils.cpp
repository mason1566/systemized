#include "ConsoleUtils.h"

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

int ConsoleInput::getSelectionFromUser(const std::vector<std::string>& options)
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

    return 0;
}
