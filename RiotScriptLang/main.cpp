#include <iostream>
#include "Script.h"
#include <locale>
#include <conio.h>

Script script;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Run script file>: ";
	std::cout << "script.txt";

	Script::loadCommandTemplates("commands.txt");

	while (_getch() == 13)
	{
		std::cout << "\n\n";

		if (script.loadFromFile("script.txt"))
		{
			script.run();
		}
		std::cout << "Run again? [enter]";
	}

	system("pause");
	return 0;
}