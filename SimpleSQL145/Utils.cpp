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

int DataUtils::intParse(const String& str)
{
	int res = 0;
	int n = str.getLength();

	for (size_t i = 0; i < n; i++)
	{
		res = res * 10 + (int(str.c_str()[i]) - 48);
	}

	return res;
}
