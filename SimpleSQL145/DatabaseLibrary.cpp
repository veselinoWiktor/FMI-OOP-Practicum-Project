#include "DatabaseLibrary.h"

Database::Database(const String& pathToDB) : pathToDB(pathToDB)
{
}

SQLResponse Database::executeQuery(const String& query)
{
	return SQLResponse();
}
