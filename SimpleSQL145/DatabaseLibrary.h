#pragma once

#include "FilePath.h"
#include "Table.h"
#include "SQLResponse.h"

class Database
{
private:
	FilePath pathToDB = (String)"No path"; // TODO: might want to fix this cast
	Table* tables;
	size_t tablesCount;

public:
	Database(const FilePath& relativePath);
	SQLResponse executeQuery(const String& query);
};

