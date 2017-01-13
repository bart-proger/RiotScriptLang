#pragma once
#include <vector>
#include <string>
using std::string;

struct ArgType
{
	enum VarType { NONE = 0, BOOL, INT, FLOAT, TEXT, ENUM }; //LIST - список из нескольких аргументов
	VarType type;
	bool bounded;
	union
	{
		int intMin;
		float floatMin;
	};
	union
	{
		int intMax;
		float floatMax;
	};
	std::vector<string> enumValues;

	ArgType() : type(NONE), bounded(false), intMin(0), intMax(0) {}
};

class CommandTemplate
{
public:
	CommandTemplate(string line);
private:
	std::vector<string> tokens_;
	std::vector<ArgType> argsTypes_;
};

