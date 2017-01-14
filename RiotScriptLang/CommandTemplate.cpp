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
		std::cerr << "[Error] " << error << std::endl;
		bad_ = true;
	}
#ifdef _DEBUG
	else
	{
		std::cout << "\n---template:\n  \"" << template_ << "\"\n";
		std::cout << "---types:\n";
		for (auto typ : argsTypes_)
		{
			std::cout << STD_TYPE_NAMES[typ.type];
			if (typ.bounded)
			{
				if (typ.type == INT)
					std::cout << " (" << typ.intMin << " to " << typ.intMax << ")";
				else if (typ.type == FLOAT)
					std::cout << " (" << typ.floatMin << " to " << typ.floatMax << ")";
			}

			if (typ.type == ENUM)
			{
				std::cout << " = ";
				for (const auto& ev : typ.enumValues)
				{
					std::cout << "'" << ev << "'";
				}
				std::cout << ";";
			}

			std::cout << std::endl;
		}
	}
#endif
}

bool CommandTemplate::parseCmdTemplate(std::stringstream& ss)
{
	char c;
	for (;;)
	{
		c = ss.get();
		if (ss.eof())
			break;
		
		if (isalpha((unsigned char)c) || c == ' ')
		{
			template_ += c;
		}
		else if (c == '[')
		{
			if (!parseArgType(ss))
				return false;
			else
				template_ += '*';
			c = ss.get();
			if (ss.eof())
			{
				error = "Неожиданный конец шаблона!";
				return false;
			}
			if (c != ']')
			{
				error = "Ожидается символ ']'.";
				return false;
			}
		}
		else
		{
			error = "Недопустимый символ '" + string{c} + "' в имени команды.";
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
		if (ss.eof())
		{
			error = "Неожиданный конец шаблона!";
			return false;
		}
		if (isalpha((unsigned char)c))
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
						return parseIntRange(ss);
						break;
					case StdType::FLOAT:
						return parseFloatRange(ss);
						break;
					case StdType::ENUM:
						return parseEnumValues(ss);
						break;
					default:
						error = "Тип \"" + typeName + "\" не имеет дополнительных свойств.";
						return false;
						break;
				}
			}
			else 
			{
				if (type == StdType::ENUM)
				{
					error = "Тип ENUM должен содержать значения.";
					return false;
				}
				ss.putback(c);
				ArgType at;
				at.type = static_cast<StdType>(type);
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
		at.type = StdType::INT;
		at.bounded = true;
		at.intMin = min;
		at.intMax = max;
		argsTypes_.push_back(at);
		return true;
	}
	error = "Некорректный диапазон INT значений.";
	return false;
}

bool CommandTemplate::parseFloatRange(std::stringstream& ss)
{
	float min, max;
	if ((ss >> min) && ss.get() == ':' && (ss >> max))
	{
		ArgType at;
		at.type = StdType::FLOAT;
		at.bounded = true;
		at.floatMin = min;
		at.floatMax = max;
		argsTypes_.push_back(at);
		return true;
	}
	error = "Некорректный диапазон FLOAT значений.";
	return false;
}

bool CommandTemplate::parseEnumValues(std::stringstream& ss)
{
	char c;
	string value = "";

	ArgType at;
	at.type = StdType::ENUM;

	for (;;)
	{
		c = ss.get();
		if (ss.eof())
		{
			error = "Неожиданный конец шаблона!";
			return false;
		}
		if (isalnum((unsigned char)c))
		{
			value += c;
		}
		else
		{
			if (value != "")
			{
				at.enumValues.push_back(value);
				value = "";
			}
			else
			{
				error = "Пропущено значение ENUM.";
				return false;
			}
			if (c != ',')
			{
				ss.putback(c);
				break;
			}
		}
	}
	argsTypes_.push_back(at);
	return true;
}