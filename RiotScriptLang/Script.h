#pragma once
#include <vector>
#include <string>
#include "Command.h"


class Script
{
public:
	bool loadFromFile(string fileName);
	void run();
private:
	std::vector<Command> commands_;
};

