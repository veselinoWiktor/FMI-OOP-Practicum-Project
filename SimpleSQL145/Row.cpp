#include "Row.h"

std::ifstream& operator>>(std::ifstream& ifs, Row& row)
{
	char buff[1024];
	ifs.getline(buff, 1024);

	std::stringstream ss(buff);
	while (!ss.eof())
	{
		ss.getline(buff, 1024, ';');
		Field curr;
		curr.data = (String)buff;
		row.fields.pushBack(curr);
	}

	return ifs;
}

size_t Row::getCellsCount() const
{
	return fields.getSize();
}
