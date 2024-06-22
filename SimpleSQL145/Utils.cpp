#include "Utils.h"

void SSUtils::clearWhiteSpaces(std::stringstream& ss)
{
	while (ss.peek() == ' ')
	{
		ss.ignore();
	}
}

Table& TableUtils::findTable(Vector<Table>& tables, const String& tblName)
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (tables[i].getName() == tblName)
		{
			return tables[i];
		}
	}
}

const Table& TableUtils::findTable(const Vector<Table>& tables, const String& tblName)
{
	for (size_t i = 0; i < tables.getSize(); i++)
	{
		if (tables[i].getName() == tblName)
		{
			return tables[i];
		}
	}
}
