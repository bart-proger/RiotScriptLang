#include "CommandTemplate.h"
#include <sstream>
#include "string_utils.h"
#include <iostream>

CommandTemplate::CommandTemplate(string line):
	bad_(true)
{
	string token;
	std::stringstream ss(line);

	if (!isalpha(line[0]))
	{
		std::cerr << "[Error] Неверный формат шаблона!" << std::endl;
		return;
	}

	if (std::getline(ss, token, '['))
	{
		string_trimRight(token, " ");
	}
	else
	{
		tokens_.push_back(line);
	}

	bad_ = false;
}
