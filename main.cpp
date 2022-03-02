#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

bool searchFromFile(const string &, string, const string &);

void printLine(const bool &, const int &, const string &);

bool checkCmdLineArgs(const string &, bool &, bool &, bool &, bool &);

void searchFromString();

void printUsage();

bool openFile(ifstream &, const string &);


int main(int argc, char *argv[])
{
    cout << "\n";

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


bool searchFromFile(const string &arg, string search, const string &fileName)
{
    bool getLineNumber, getOccurrence, getReverse, ignoreCase;
    int counter{}, found{};
    string line, tempLine, tempSearch;
    ifstream file;

    if (!openFile(file, fileName))
    {
        return false;
    }

    if (!arg.empty())
    {
        if (!checkCmdLineArgs(arg, getLineNumber, getOccurrence, getReverse, ignoreCase))
        {
            file.close();
            return false;
        }
    }

    while (getline(file, line))
    {
        counter++;

        tempLine = line;
        tempSearch = search;

        if (ignoreCase)
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            transform(search.begin(), search.end(), search.begin(), ::tolower);
        }

        if (getReverse)
        {
            if (line.find(search) == string::npos)
            {
                printLine(getLineNumber, counter, tempLine);
                found++;
            }
        }
        else if (line.find(search) != string::npos)
        {
            printLine(getLineNumber, counter, tempLine);
            found++;
        }

        search = tempSearch;
    }


    if (!found)
    {
        cout << quoted(search) << " is not included in file." << endl;
    }
    else if (getOccurrence)
    {
        cout << "\nOccurrences of lines";
        cout << (getReverse ? " NOT" : "") << " containing " << quoted(search) << ": " << found << endl;
    }


    file.close();

    return true;
}


void printLine(const bool &getLineNumber, const int &counter, const string &line)
{
    if (getLineNumber)
    {
        cout << counter << ": ";
    }
    cout << line << endl;
}


bool checkCmdLineArgs(const string &arg, bool &getLineNumber, bool &getOccurrence, bool &getReverse, bool &ignoreCase)
{
    bool lFlag{}, oFlag{}, rFlag{}, iFlag{};

    if (arg.length() > 2 && arg[0] == '-' && arg[1] == 'o')
    {
        for (int i = 2; i < arg.length(); i++)
        {
            switch (arg[i])
            {
                case 'l':
                    if (lFlag)
                    {
                        return false;
                    }
                    lFlag = true;
                    getLineNumber = true;
                    break;
                case 'o':
                    if (oFlag)
                    {
                        return false;
                    }
                    oFlag = true;
                    getOccurrence = true;
                    break;
                case 'r':
                    if (rFlag)
                    {
                        return false;
                    }
                    rFlag = true;
                    getReverse = true;
                    break;
                case 'i':
                    if (iFlag)
                    {
                        return false;
                    }
                    iFlag = true;
                    ignoreCase = true;
                    break;
            }
        }
        return true;
    }

    return false;
}


void searchFromString()
{
    string userLine{}, search{};

    cout << "Give a string from which to search for: ";
    getline(cin, userLine);
    cout << "Give search string: ";
    getline(cin, search);

    size_t found = userLine.find(search);

    if (found == string::npos)
    {
        cout << quoted(search) << " NOT found in " << quoted(userLine)
             << "." << endl;
        return;
    }

    cout << quoted(search) << " found in " << quoted(userLine)
         << " at position " << found << "." << endl;
}


bool openFile(ifstream &file, const string &fileName)
{
    file.open(fileName);

    if (!file.good())
    {
        cerr << "ERROR: Couldn't open file\n" << endl;
        return false;
    }

    return true;
}


void printUsage()
{
    cout << "Usage: ./myGrep [[options] [keyword fileName]]\n\n";
    cout << "Available options (access with -o)\n l - Print line number\n o - Print occurrences\n r - Reverse search\n i - Ignore "
            "case\n\n";
}