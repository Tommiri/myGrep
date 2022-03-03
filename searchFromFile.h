#ifndef MYGREP_SEARCHFROMFILE_H
#define MYGREP_SEARCHFROMFILE_H
using namespace std;

bool searchFromFile(const string &, string, const string &);

void printLine(const bool &, const int &, const string &);

bool checkCmdLineArgs(const string &, bool &, bool &, bool &, bool &);

bool openFile(ifstream &, const string &);

#endif
