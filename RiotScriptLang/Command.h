#pragma once
#include <vector>
#include <string>
using std::string;
#include "CommandTemplate.h"

class Command
{
public:
	struct ArgValue
	{
		StdType type;
		string value;
		union
		{
			int intValue;
			float floatValue;
			bool boolValue;
			long enumValueNum;
		};

		ArgValue() : type(NONE), value(""), intValue(0) 
		{}
	};
	typedef void (*Function)(std::vector<ArgValue> &args);

 	Command(string scriptLine, long lineNumber);
	void execute();

private:
	static void func_Print(std::vector<ArgValue> &args);

	Function func_;
	std::vector<ArgValue> args_;
	long lineNumber_;
};
