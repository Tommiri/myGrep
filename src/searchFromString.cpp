#include <iostream>
#include <iomanip>
#include <string>
#include "../include/searchFromString.h"

void searchFromString()
{
    string userLine{}, search{};

    cout << "Give a string from which to search for: ";
    getline(cin, userLine);
    cout << "Give search string: ";
    getline(cin, search);

    size_t found = userLine.find(search);

    // If string::find returns string::npos, given argument was not found in string
    if (found == string::npos)
    {
        cout << quoted(search) << " NOT found in " << quoted(userLine)
             << "." << endl;
        return;
    }

    cout << quoted(search) << " found in " << quoted(userLine)
         << " at position " << found << "." << endl;
}
