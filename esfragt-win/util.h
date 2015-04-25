#ifndef UTIL_H
#define UTIL_H

#include <string>

bool isdigits(std::string &s);
bool isfloat(std::string &s);
void checkValueParam(int n, int argc, char* argv[]);
void checkValueParamf(int n, int argc, char* argv[]);
bool loadFile(std::string inFileName, std::string& outString, int linesize=4096);

#endif
