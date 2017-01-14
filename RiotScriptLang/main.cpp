#include <iostream>
#include "Script.h"
#include <locale>
#include <conio.h>
#include <sstream>

Script script;

int main(int argc, char *argv[])
{
// 	string s;
// 	std::cin >> s;
// 	std::stringstream ss(s);
// 
// 	if (std::getline(ss, s, '['))
// 		std::cout << "1='" << s << "'\n";
// 	else
// 		std::cout << "'[' not fount\n";
// 	if (!ss.eof())
// 	{
// 		std::getline(ss, s);
// 		std::cout << "2='" << s << "'\n";
// 	}
// 	else
// 		std::cout << "2 eof\n";

	setlocale(LC_ALL, "Russian");
	std::cout << "Run script file>: ";
	std::cout << "script.txt";

	Script::loadCommandTemplates("commands.txt");

// 	while (_getch() == 13)
// 	{
// 		std::cout << "\n\n";
// 
// 		if (script.loadFromFile("script.txt"))
// 		{
// 			script.run();
// 		}
// 		std::cout << "Run again? [enter]";
// 	}

	system("pause");
	return 0;
}