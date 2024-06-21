#include "DatabaseLibrary.h"

Database::Database(const String& pathToDB) : pathToDB(pathToDB)
{
}

void Database::showTables()
{
	if (tablesCount == 0)
	{
		throw std::logic_error("Empty set");
	}
	
	//TODO: If tables more than 0
}
