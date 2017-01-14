#include "CommandTemplate.h"
#include <sstream>
#include "string_utils.h"
#include <iostream>


const char* STD_TYPE_NAMES[] = { "NONE", "BOOL", "INT", "FLOAT", "TEXT", "ENUM" };
string error;


CommandTemplate::CommandTemplate(string line):
	bad_(false)
{	
	std::stringstream ss(line);

	if (!parseCmdTemplate(ss))
	{
		std::cerr << "[Error] Неверный формат шаблона команды! " << error << std::endl;
		bad_ = true;
	}
	else
	{
		std::cout << "\n---tokens:\n";
		for (auto tok: tokens_)
		{
			std::cout << tok << "\n";
		}
		std::cout << "---types:\n";
		for (auto typ : argsTypes_)
		{
			std::cout << STD_TYPE_NAMES[typ.type];
			if (typ.bounded)
				std::cout << " (" << typ.intMin << "..." << typ.intMax << ")";
			std::cout << std::endl;
		}
	}
}

bool CommandTemplate::parseCmdTemplate(std::stringstream& ss)
{
	char c;
	string token = "";
	for (;;)
	{
		c = ss.get();
		if (ss.eof())
		{
			tokens_.push_back(token); //FIX: дублирование последнего токена
			break;
		}
		
		if (isalpha(c) || c == ' ')
		{
			token += c;
		}
		else if (c == '[')
		{
			tokens_.push_back(token);
			if (!parseArgType(ss))
				return false;
			if (ss.get() != ']')
			{
				error = "Не найден символ ']'.";
				return false;
			}
		}
		else
		{
			error = "Недопустимый символ '" + string{c} + "'.";
			return false;
		}
	}
	return true;
}

bool CommandTemplate::parseArgType(std::stringstream& ss)
{
	char c;
	string typeName;
	for (;;)
	{
		c = ss.get();
		if (isalpha(c))
		{
			typeName += c;
		}
		else 
		{
			bool unknown = true;
			int type;
			for (type = StdType::NONE; type <= StdType::ENUM; ++type)
			{
				if (typeName == STD_TYPE_NAMES[type])
				{
					unknown = false;
					break;
				}
			}
			if (unknown)
			{
				error = "Неизвестный тип \"" + typeName + "\".";
				return false;
			}
			if (c == '=')
			{
				switch (type)
				{
					case StdType::INT:
						if (!parseIntRange(ss))
							return false;
						else
							return true;
						break;
					default:
						error = "Тип \"" + typeName + "\" не имеет дополнительных свойств.";
						return false;
						break;
				}
			}
			else 
			{
				ss.putback(c);
				ArgType at;
				at.type = INT;
				at.bounded = false;
				argsTypes_.push_back(at);
				return true;
			}
		}

	}
	return true;
}

bool CommandTemplate::parseIntRange(std::stringstream& ss)
{
	int min, max;
	if ((ss >> min) && ss.get() == ':' && (ss >> max))
	{
		ArgType at;
		at.type = INT;
		at.bounded = true;
		at.intMin = min;
		at.intMax = max;
		argsTypes_.push_back(at);
		return true;
	}
	return false;
}
