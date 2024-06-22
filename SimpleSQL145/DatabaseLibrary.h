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
	FilePath pathToDB = (String)"No path"; // TODO: might want to fix this cast
	Vector<Table> tables;

	void loadDatabase(std::ifstream& ifs);
public:
	Database(const FilePath& relativePath);
	SQLResponse executeQuery(const String& query);
};

