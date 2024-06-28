#include <iostream>
#define CIN_MESSAGE "ss145> "

#include "DatabaseLibrary.h"
#include "FilePath.h"

int main()
{
	/*Database db("viktor/viktor.db");
	db.executeQuery("create table table1.ss145 (field1 int, field2 text, field3 real)");
	db.executeQuery("insert into table1.ss145 (field1, field2, field3) values (1, viktor, 6.0), (2, desi, 6.0), (3, marti, 4.5)");
	db.executeQuery("alter table table1.ss145 add field4 int");
	db.executeQuery("alter table table1.ss145 rename column field4 to field5");
	db.executeQuery("alter table table1.ss145 drop column field5");
	db.executeQuery("update table1.ss145 set field1=1"); 
	db.executeQuery("select * from table1.ss145");
	db.executeQuery("select field1, field3 from table1.ss145");
	db.executeQuery("delete from table1.ss145 where (((field1)>(2))&((field1)<(4)))");
	db.executeQuery("drop table table1.ss145");*/


	/*
	* test/test.db
	* create table table1 (field1 int, field2 text, field3 real)
	* insert into table1 (field1, field2) values (1, viktor), (2, deschi)
	* update table1 set field3=3.0 where ((field1)=(1))
	*/

	std::cout << "Enter path to database" << std::endl;
	String pathToDB;
	std::cout << CIN_MESSAGE;
	std::cin >> pathToDB;

	Database db(pathToDB);

	String query;
	std::cout << CIN_MESSAGE;
	std::cin >> query;
	while (query != "disconnect")
	{
		SQLResponse result = db.executeQuery(query);
		std::cout << result.getMessage() << std::endl;

		std::cout << CIN_MESSAGE;
		std::cin >> query;
	}
}