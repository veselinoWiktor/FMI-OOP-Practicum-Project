#include "DatabaseLibrary.h"

void Database::loadDatabase(std::ifstream& ifs)
{
	String currTblPath;
	while (!ifs.eof())
	{
		ifs >> currTblPath;
		Table currTbl((FilePath)currTblPath);
		tables.pushBack(currTbl);
	}
}

Database::Database(const FilePath& relativePath)
{
	if (relativePath.getExtension() != ".db")
	{
		throw std::logic_error("Database::Database(); File was not with extension .db");
	}

	String path = (relativePath.getName() + relativePath.getExtension());
	std::ifstream ifs(path.c_str());
	if (!ifs.is_open())
	{
		throw std::logic_error("Database::Database(); Database file was already open!");
	}

	loadDatabase(ifs);
	ifs.close();
}

SQLResponse Database::executeQuery(const String& query)
{
	SQLCommand* command = 
}
