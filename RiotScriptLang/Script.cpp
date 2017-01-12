#include "Script.h"
#include <fstream>

// Script::Script()
// {
// }
// 
// Script::~Script()
// {
// }

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
