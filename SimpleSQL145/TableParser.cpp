#include "TableParser.h"

String TableParser::parseColumnOutline(const Vector<Column>& columns)
{
	size_t colsCount = columns.getSize();

	String result;
	result += "+-";
	for (size_t i = 0; i < colsCount; i++)
	{
		int colNameLen = columns[i].name.getLength();
		result += String('-', colNameLen);
		if (i == colsCount - 1)
			result += "-+";
		else
			result += "-+-";
	}
	result += '\n';
	
	return result;
}

String TableParser::parseColumn(const Vector<Column>& columns, Vector<int>& colsLengths)
{
	size_t colsCount = columns.getSize();

	String result;

	result += parseColumnOutline(columns);

	result += "| ";
	for (size_t i = 0; i < colsCount; i++)
	{
		result += columns[i].name;
		colsLengths.pushBack(columns[i].name.getLength());
		if (i == colsCount - 1)
			result += " |";
		else
			result += " | ";
	}
	result += '\n';

	result += parseColumnOutline(columns);

	return result;
}

String TableParser::parseRow(const Row& row, const Vector<int>& colsLengths)
{
	size_t cellsCount = row.getCellsCount();

	String result;

	result += "| ";
	for (size_t i = 0; i < cellsCount; i++)
	{
		String currCell = row.getCell(i);
		int padding = (colsLengths[i] - currCell.getLength());
		if (padding >= 0)
		{
			result += String(' ', padding);
		}
		result += currCell;

		if (i == cellsCount - 1)
			result += " |";
		else
			result += " | ";
	}
	result += '\n';

	return result;
}

String TableParser::parseTable(const Table& table)
{
	String result;

	if (table.getRowsCount() == 0)
	{
		return "Empty set";
	}

	Vector<Column> cols = table.getColumns();
	Vector<int> colsLengths;
	result += parseColumn(cols, colsLengths);

	Vector<Row> rows = table.getRows();
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		result += parseRow(rows[i], colsLengths);
	}
	result += parseColumnOutline(cols);

	result += DataUtils::intToString(rows.getSize());
	result += " rows in set";

	return result;
}
