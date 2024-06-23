#pragma once

#include "Vector.hpp"

#include "SQLCommand.h"
#include "SQLCommandFactory.h"
#include "SQLResponse.h"
#include "FilePath.h"
#include "Table.h"

class Database
{
private:
	FilePath dbPath = "No path";
	Vector<Table> tables;

	void loadDatabase(std::ifstream& ifs);
	void saveDatabase();
	void saveTable(const Table& tbl);
public:
	Database(const FilePath& relativePath);
	~Database();
	SQLResponse executeQuery(const String& query);
};

