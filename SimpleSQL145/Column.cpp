#include "Column.h"
#include <iostream>

Column::Column(const String& name, const ColumnType& type) : name(name), type(type)
{
}

std::ifstream& operator>>(std::ifstream& ifs, Column& column)
{
	char buff[1024];
	ifs.getline(buff, 1024, ';');
	column.name = buff;

	int columnType = 0;
	ifs >> columnType;
	column.type = (ColumnType)columnType;

	ifs.ignore();
	return ifs;
}
