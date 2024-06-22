#pragma once

#include <sstream>

#include "Vector.hpp"

#include "Column.h"
#include "Row.h"
#include "FilePath.h"

class Table
{
private:
	String name;
	Vector<Column> columns;
	Vector<Row> rows;

	void loadTable(std::ifstream& ifs);
public:
	Table() = default;
	Table(const String& tableName);
	Table(const FilePath& path);
	
	const String& getName() const;
	size_t getColumnsCount() const;

	void insertRow(const Row& row);
	void insertRow(Row&& row);
	void insertColumn(const Column& column);
	void insertColumn(Column&& column);
};

