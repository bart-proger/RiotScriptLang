#include "Command.h"
#include <iostream>
#include <sstream>

Command::Command(string scriptLine, long lineNumber):
	func_(nullptr),
	lineNumber_(lineNumber)
{
	string token;
	std::stringstream ss(scriptLine);

	if (std::getline(ss, token, ' '))
	{
		//TODO: сравнение по шаблону
		if (token == "print")
		{
			func_ = func_Print;
			FuncArg a;
			a.type = FuncArg::ArgType::TEXT;
			//TODO: разбор выражений текстовых, численных, логических
			if (std::getline(ss, token))
				a.value = token;

			args_.push_back(a);
		}
		else
		{
			std::cout << "Undefined command \"" << token << "\" at line " << lineNumber_ << "\n";
		}

	}
}

void Command::execute()
{
	if (func_ != nullptr)
		func_(args_);
}

void Command::func_Print(std::vector<FuncArg> &args)
{
	std::cout << args[0].value << std::endl;
}
