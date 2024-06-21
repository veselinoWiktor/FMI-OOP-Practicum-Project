#pragma once

#include "String.h"
#include "Table.h"
#include "SQLResponse.h"

class Database
{
private:
	String pathToDB;
	Table* tables;
	size_t tablesCount;

public:
	Database(const String& pathToDB);
	SQLResponse executeQuery(const String& query);
};

