#pragma once

#include <sstream>

#include "Vector.hpp"

#include "Column.h"
#include "Row.h"
#include "FilePath.h"

class Table
{
private:
	Vector<Column> columns;
	Vector<Row> rows;

	void loadTable(std::ifstream& ifs);
public:
	Table() = default;
	Table(const FilePath& path);
	
	/*void insertRow(const Row& row);
	void insertRow(Row&& row);
	void insertColumn(const Column& column);
	void insertColumn(Column&& column);*/
};

