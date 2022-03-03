#include <iostream>
#include "searchFromFile.h"
#include "searchFromString.h"

void printUsage();

int main(int argc, char *argv[])
{
    cout << "\n";

    // Program is only runnable with either 1, 3 or 4 arguments
    switch (argc)
    {
        case 1:
            searchFromString();
            break;
        case 3:
            if (!searchFromFile("", argv[1], argv[2]))
            {
                printUsage();
                return EXIT_FAILURE;
            }
            break;
        case 4:
            if (!searchFromFile(argv[1], argv[2], argv[3]))
            {
                printUsage();
                return EXIT_FAILURE;
            }
            break;
        default:
            printUsage();
            return EXIT_FAILURE;
    }

    cout << endl;
    return EXIT_SUCCESS;
}

void printUsage()
{
    // Options encased in square brackets are optional
    cout << "Usage: ./myGrep [[options] [keyword fileName]]\n\n";
    cout << "Available options (access with -o)\n l - Print line number\n o - Print occurrences\n r - Reverse search\n i - Ignore "
            "case\n\n";
}
