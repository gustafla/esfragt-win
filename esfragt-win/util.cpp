#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "text.h"

using namespace std;

bool isdigits(std::string &s)
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

bool isfloat(std::string &s)
{
    return s.find_first_not_of("0123456789.") == std::string::npos;
}

void checkValueParam(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        cout << ARGERR;
        char e;
        std::cin >> e;
        exit(20);
    }

    string tmps = argv[n];

    if (!isdigits(tmps))
    {
        cout << ARGERR;
        char e;
        std::cin >> e;
        exit(30);
    }
}

bool loadFile(std::string inFileName, std::string& outString, int linesize)
{
    std::ifstream inFile(inFileName.c_str());
    if (!inFile.is_open())
    {
        std::cout << inFileName << ": No such file\n";
        return false;
    }

    char* tmp = new char[linesize];

    while (!inFile.eof())
    {
        inFile.getline(tmp, linesize);
        outString += tmp;
        outString += "\n";
    }
    delete tmp;
    return true;
}

void checkValueParamf(int n, int argc, char* argv[])
{
    if (n==argc)
    {
        cout << ARGERR;
        char e;
        std::cin >> e;
        exit(21);
    }

    string tmps = argv[n];

    if (!isfloat(tmps))
    {
        cout << ARGERR;
        char e;
        std::cin >> e;
        exit(31);
    }
}