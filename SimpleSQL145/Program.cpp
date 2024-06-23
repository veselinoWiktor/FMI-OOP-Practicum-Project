#include <iostream>
#define CIN_MESSAGE "ss145> "

#include "DatabaseLibrary.h"
#include "FilePath.h"

int main()
{
	Database db("viktor/viktor.db");
	db.executeQuery("create table table1.ss145 (field1 int, field2 text, field3 real)");
	db.executeQuery("insert into table1.ss145 (field1, field2, field3) values (1, viktor, 6.0), (2, desi, 6.0), (3, marti, 4.5)");
	db.executeQuery("alter table table1.ss145 add field4 int");
	db.executeQuery("alter table table1.ss145 rename column field4 to field5");
	db.executeQuery("alter table table1.ss145 drop column field5");
	db.executeQuery("delete from table1.ss145 where (((field1)>(2))&((field1)<(4)))");
	db.executeQuery("drop table table1.ss145");

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