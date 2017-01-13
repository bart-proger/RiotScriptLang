#pragma once
#include <vector>
#include <string>
using std::string;

class Command
{
public:
	struct FuncArg
	{
		enum ArgType { NONE = 0, BOOL, INT, FLOAT, TEXT, ENUM }; //LIST - список аргументов
		ArgType type;
		string value;
		union
		{
			int intValue;
			float floatValue;
			bool boolValue;
			long enumValueNum;
		};

		FuncArg() : type(NONE), value(""), intValue(0) 
		{}
	};
	typedef void (*Function)(std::vector<FuncArg> &args);

 	Command(string scriptLine, long lineNumber);
	void execute();

private:
	static void func_Print(std::vector<FuncArg> &args);

	Function func_;
	std::vector<FuncArg> args_;
	long lineNumber_;
};
