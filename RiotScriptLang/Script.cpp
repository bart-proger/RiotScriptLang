#include "Script.h"
#include <fstream>
#include "string_utils.h"
#include <iostream>


std::vector<CommandTemplate> Script::templates;

bool Script::loadFromFile(string fileName)
{
	commands_.clear();

	std::ifstream f(fileName);
	string line;
	int num = 0;
	while (std::getline(f, line))
	{
		Command cmd(line, num);
		commands_.push_back(cmd);
		++num;
	}

	return true;
}

void Script::run()
{
	for (auto cmd : commands_)
	{
		cmd.execute();
	}
}

bool Script::loadCommandTemplates(string fileName)
{
	templates.clear();

	std::ifstream f(fileName);
	string line;
	for (long ln = 1; std::getline(f, line); ++ln)
	{
		string_trim(line, " ");
		if (line.empty())
			continue;
std::cout << ln << ": " << line << ";\n";
		CommandTemplate tmp(line);
std::cin.get();
 		if (!tmp.bad())
 			templates.push_back(tmp);
	}

	return true;
}

void Script::freeCommandTemplates()
{
	templates.clear();
}
