#include <iostream>
#define CIN_MESSAGE "ss145> "

#include "DatabaseLibrary.h"
#include "FilePath.h"

int main()
{
	Table t((String)"table1.ss145");

	/*std::cout << "Enter path to database" << std::endl;
	String pathToDB;
	std::cout << CIN_MESSAGE;
	std::cin >> pathToDB;

	Database db(pathToDB);

	String command;
	std::cout << CIN_MESSAGE;
	std::cin >> command;
	while (command != "disconnect")
	{
		try
		{
			if (command == "show tables;")
			{
				db.showTables();
			}
		}
		catch (const std::logic_error& e)
		{
			std::cout << e.what() << std::endl;
		}
		catch (const std::exception&)
		{
		}

		std::cout << CIN_MESSAGE;
		std::cin >> command;
	}*/
}