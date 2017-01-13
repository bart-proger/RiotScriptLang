#pragma once
#include <vector>
#include <string>
#include "Command.h"
#include "CommandTemplate.h"

class Script
{
public:
	bool loadFromFile(string fileName);
	void run();

	static bool loadCommandTemplates(string fileName);
	static void freeCommandTemplates();

	static std::vector<CommandTemplate> templates;

private:
	string name_;
	std::vector<Command> commands_;
};

