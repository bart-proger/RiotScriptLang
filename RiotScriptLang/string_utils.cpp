#include "string_utils.h"
#include <sstream>

std::vector<string> string_split(const string& s, char delim)
{
	std::vector<string> items;
	std::stringstream ss(s);
	string item;
	while (std::getline(ss, item, delim))
	{
		items.push_back(item);
	}
	return items;
}

void string_trimRight(std::string& str, const std::string& trimChars)
{
	std::string::size_type pos = str.find_last_not_of(trimChars);
	str.erase(pos + 1);
}


void string_trimLeft(std::string& str, const std::string& trimChars)
{
	std::string::size_type pos = str.find_first_not_of(trimChars);
	str.erase(0, pos);
}


void string_trim(std::string& str, const std::string& trimChars)
{
	string_trimRight(str, trimChars);
	string_trimLeft(str, trimChars);
}