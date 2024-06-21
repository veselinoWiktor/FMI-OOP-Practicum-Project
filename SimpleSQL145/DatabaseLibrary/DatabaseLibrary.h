#pragma once

#include "../Utils/String.h"
#include "Models/Table.h"

class Database
{
private:
	String pathToDB;
	Table* tables;
	size_t tablesCount;

public:
	Database(const String& pathToDB);
	void showTables();
};

