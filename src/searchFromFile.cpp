#include <iostream>
#include <iomanip>
#include <algorithm>
#include "../include/searchFromFile.h"

// Function parameters are const references when possible to avoid unnecessary copying of variables
bool searchFromFile(const string &arg, string search, const string &fileName)
{
    bool getLineNumber, getOccurrence, getReverse, ignoreCase;
    int counter{}, found{};
    string line, tempLine, tempSearch;
    ifstream file;

    // Using guard clauses to clean up unnecessary if-else structures
    if (!openFile(file, fileName))
    {
        return false;
    }

    if (!arg.empty())
    {
        if (!checkCmdLineArgs(arg, getLineNumber, getOccurrence, getReverse, ignoreCase))
        {
            cerr << "ERROR: Invalid options\n\n";
            file.close();
            return false;
        }
    }

    // Main loop of the program, getting a line from the text file per loop
    while (getline(file, line))
    {
        counter++;

        tempLine = line;
        tempSearch = search;

        if (ignoreCase)
        {
            // Transforming search variables to lowercase for case-insensitive matching
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

        // Assigning the original user-given value back to search for printing (in case of ignoreCase)
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

    /* Checking that user accesses program options with -o
    *  Using flag variables to check for duplicate option inputs */
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

