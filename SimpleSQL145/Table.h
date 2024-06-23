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
	const Vector<Column>& getColumns() const;
	const Column& getColumn(const String& colName);
	const Column& getColumn(size_t idx);
	size_t getColumnIndex(const String& colName) const;

	size_t getRowsCount() const;
	const Vector<Row>& getRows() const;

	const String& getCellVal(size_t rowIdx, const String& colName) const;
	void setCellVal(size_t rowIdx, const String& colName, const String& newVal);
	void setCellVal(size_t rowIdx, const String& colName, String&& newVal);

	void insertRow(const Row& row);
	void insertRow(Row&& row);

	void removeRowAt(size_t idx);

	void insertColumn(const Column& column);
	void insertColumn(Column&& column);

	void removeColumnAt(size_t colIdx);
	void removeColumnByName(const String& columnName);

	void renameColumn(const String& columnName, const String& columnNewName);
};

