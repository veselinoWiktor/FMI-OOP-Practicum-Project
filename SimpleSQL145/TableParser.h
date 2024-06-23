#pragma once
#include "Table.h"
#include "Utils.h"

class TableParser
{
private:
	static String parseColumnOutline(const Vector<Column>& columns);
	static String parseColumn(const Vector<Column>& columns, Vector<int>& colsLengths);
	static String parseRow(const Row& row, const Vector<int>& colsLengthss);
public:
	static String parseTable(const Table& table);
};

