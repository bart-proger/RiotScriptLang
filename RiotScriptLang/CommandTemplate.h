#pragma once
#include <vector>
#include <string>
using std::string;


enum StdType { NONE = 0, BOOL, INT, FLOAT, TEXT, ENUM };
const char* STD_TYPE_NAMES[];


struct ArgType
{
	StdType type;
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
	bool bad() { return bad_; }
public:
	CommandTemplate(string line);
	bool parseCmdTemplate(std::stringstream& ss);
	bool parseArgType(std::stringstream& ss);
	bool parseIntRange(std::stringstream& ss);
private:
	std::vector<string> tokens_;
	std::vector<ArgType> argsTypes_;
	bool bad_;
};
