#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void searchFromString();

void printOptions();

bool checkCmdLineArgs(string, bool &, bool &, bool &, bool &);

int main(int argc, char *argv[])
{
    cout << "\n";
    bool getLineNumber{}, getOccurrence{}, getReverse{}, ignoreCase{};
    int counter{}, found{};
    string search, fileName, line, tempLine, tempSearch, arg;
    ifstream file;

    if (argc < 2)
    {
        searchFromString();
        return EXIT_SUCCESS;
    }
    else if (argc == 3)
    {
        search = argv[1];
        fileName = argv[2];
    }
    else
    {
        arg = string(argv[1]);
        search = argv[2];
        fileName = argv[3];
    }


    file.open(fileName);

    if (file.good())
    {
        if (checkCmdLineArgs(arg, getLineNumber, getOccurrence, getReverse, ignoreCase))
        {
            while (getline(file, line))
            {
                counter++;

                if (ignoreCase)
                {
                    tempSearch = search;
                    tempLine = line;
                    transform(search.begin(), search.end(), search.begin(), ::tolower);
                    transform(line.begin(), line.end(), line.begin(), ::tolower);
                }

                if (getReverse)
                {
                    if (line.find(search) == string::npos)
                    {
                        if (getLineNumber)
                        {
                            cout << counter << ": ";
                        }
                        cout << line << endl;
                        found++;
                    }
                }

                else if (line.find(search) != string::npos)
                {
                    if (getLineNumber)
                    {
                        cout << counter << ": ";
                    }
                    cout << line << endl;
                    found++;
                }
            }

            if (getOccurrence)
            {
                cout << "\nOccurrences of lines ";
                if (getReverse)
                {
                    cout << "NOT ";
                }
                cout << "containing " << quoted(search) << ": " << found << endl;
            }

            if (!found)
            {
                cout << quoted(search) << " is not included in file." << endl;
            }
        }

        else
        {
            printOptions();
            return EXIT_FAILURE;
        }
    }

    else
    {
        cerr << "ERROR: Couldn't open file" << endl;
        return EXIT_FAILURE;
    }

    file.close();

    cout << endl;
    return EXIT_SUCCESS;
}

void searchFromString()
{
    string mainString{}, searchString{};

    cout << "Give a string from which to search for: ";
    getline(cin, mainString);
    cout << "Give search string: ";
    getline(cin, searchString);

    size_t found = mainString.find(searchString);

    if (found != string::npos)
    {
        cout << quoted(searchString) << " found in " << quoted(mainString)
             << " at position " << found << "." << endl;
    }
    else
    {
        cout << quoted(searchString) << " NOT found in " << quoted(mainString)
             << "." << endl;
    }
}

bool checkCmdLineArgs(string arg, bool &getLineNumber, bool &getOccurrence, bool &getReverse, bool &ignoreCase)
{
    bool lFlag{}, oFlag{}, rFlag{}, iFlag{};

    if (arg.length() > 2 && arg[0] == '-' && arg[1] == 'o')
    {
        try
        {
            for (int i = 2; i < arg.length(); i++)
            {
                switch (arg[i])
                {
                    case 'l':
                        if (lFlag)
                        {
                            throw;
                        }
                        lFlag = true;
                        getLineNumber = true;
                        break;
                    case 'o':
                        if (oFlag)
                        {
                            throw;
                        }
                        oFlag = true;
                        getOccurrence = true;
                        break;
                    case 'r':
                        if (rFlag)
                        {
                            throw;
                        }
                        rFlag = true;
                        getReverse = true;
                        break;
                    case 'i':
                        if (iFlag)
                        {
                            throw 6;
                        }
                        iFlag = true;
                        ignoreCase = true;
                        break;
                }
            }
        }


        return true;
    }

    return false;
}

void printOptions()
{
    cout << "Available options (access with -o)\n l - Print line number\n o - Print occurrences\n r - Reverse search\n i - Ignore "
            "case\n\n";
}

