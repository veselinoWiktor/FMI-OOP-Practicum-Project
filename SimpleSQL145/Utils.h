#pragma once
#include <sstream>
#include "Table.h"
#include "Vector.hpp"

namespace SSUtils //String stream utils
{
	void clearWhiteSpaces(std::stringstream& ss);
}

namespace TableUtils
{
	Table& findTable(Vector<Table>& tables, const String& tblName);
	const Table& findTable(const Vector<Table>& tables, const String& tblName);
}

namespace DataUtils
{
	int intParse(const String& str);
	String intToString(int num);
}
