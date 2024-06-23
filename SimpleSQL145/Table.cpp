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

	String filePath = (path.getName() + path.getExtension());
	std::ifstream ifs(filePath.c_str());
	if (!ifs.is_open())
	{
		//TODO: throw exception
	}
	loadTable(ifs);
}

const String& Table::getName() const
{
	return name;
}

size_t Table::getColumnsCount() const
{
	return columns.getSize();
}

const Vector<Column>& Table::getColumns() const
{
	return columns;
}

const Column& Table::getColumn(const String& colName)
{
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (columns[i].name == colName)
		{
			return columns[i];
		}
	}
}

const Column& Table::getColumn(size_t idx)
{
	return columns[idx];
}

size_t Table::getColumnIndex(const String& colName) const
{
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (columns[i].name == colName)
		{
			return i;
		}
	}
}

size_t Table::getRowsCount() const
{
	return rows.getSize();
}

const Vector<Row>& Table::getRows() const
{
	return rows;
}

const String& Table::getCellVal(size_t rowIdx, const String& colName) const
{
	size_t colIdx = getColumnIndex(colName);
	return getCellVal(rowIdx, colIdx);
}

const String& Table::getCellVal(size_t rowIdx, size_t colIdx) const
{
	return rows[rowIdx].getCell(colIdx);
}

void Table::setCellVal(size_t rowIdx, const String& colName, const String& newVal)
{
	size_t colIdx = getColumnIndex(colName); // TODO validate data
	rows[rowIdx].setCellAt(colIdx, newVal);
}

void Table::setCellVal(size_t rowIdx, const String& colName, String&& newVal)
{
	size_t colIdx = getColumnIndex(colName); // TODO Validate data
	rows[rowIdx].setCellAt(colIdx, std::move(newVal));
}

void Table::insertRow(const Row& row)
{
	rows.pushBack(row);
}

void Table::insertRow(Row&& row)
{
	rows.pushBack(std::move(row));
}

void Table::removeRowAt(size_t idx)
{
	rows.popAt(idx);
}

void Table::insertColumn(const Column& column)
{
	columns.pushBack(column);
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		rows[i].pushCell("NULL");
	}
}

void Table::insertColumn(Column&& column)
{
	columns.pushBack(std::move(column));
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		rows[i].pushCell("NULL");
	}
}

void Table::removeColumnAt(size_t colIdx)
{
	columns.popAt(colIdx);

	for (size_t i = 0; i < rows.getSize(); i++)
	{
		rows[i].removeCellAt(colIdx);
	}
}

void Table::removeColumnByName(const String& columnName)
{
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (columns[i].name == columnName)
		{
			return removeColumnAt(i);
		}
	}

	throw std::invalid_argument(("Column \"" + columnName + "\" was not found").c_str());
}

void Table::renameColumn(const String& columnName, const String& columnNewName)
{
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		if (columns[i].name == columnName)
		{
			columns[i].name = columnNewName;
			return;
		}
	}

	throw std::invalid_argument(("Column \"" + columnName + "\" was not found").c_str());
}
