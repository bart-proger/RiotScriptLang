#pragma once
#include <string>
using std::string;
#include <vector>
#include <sstream>

std::vector<string> string_split(const string& s, char delim);
void string_trimRight(std::string& str, const std::string& trimChars);
void string_trimLeft(std::string& str, const std::string& trimChars);
void string_trim(std::string& str, const std::string& trimChars);