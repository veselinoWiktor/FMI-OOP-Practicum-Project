#include "Table.h"
#include <iostream>

void Table::loadTable(std::ifstream& ifs)
{
	int columnsCount = 0;
	ifs >> columnsCount;
	ifs.ignore();

	for (size_t i = 0; i < columnsCount; i++)
	{
		Column curr;
		ifs >> curr;
		columns.pushBack(curr);
	}

	while (!ifs.eof())
	{
		Row curr;
		ifs >> curr;
		rows.pushBack(curr);
	}
}

Table::Table(const String& tableName) : name(tableName)
{
}

Table::Table(const FilePath& path)
{
	if (path.getExtension() != ".ss145")
	{
		//TODO: throw exception
	}

	String filePath = path.getName().c_str();
	filePath += path.getExtension().c_str();
	std::ifstream ifs(filePath.c_str());
	if (!ifs.is_open())
	{
		//TODO: throw exception
	}
	loadTable(ifs);
}

void Table::insertColumn(const Column& column)
{
	columns.pushBack(column);
}

void Table::insertColumn(Column&& column)
{
	columns.pushBack(std::move(column));
}
