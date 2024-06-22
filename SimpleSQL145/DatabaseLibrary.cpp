#include "DatabaseLibrary.h"

Database::Database(const FilePath& relativePath)
{
	if (relativePath.getExtension() != ".db")
	{
		throw std::logic_error("Database::Database(); File was not with extension .db");
	}

}

SQLResponse Database::executeQuery(const String& query)
{
	return SQLResponse();
}
