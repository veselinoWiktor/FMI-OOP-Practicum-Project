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

void Row::pushCell(const String& field)
{
	fields.pushBack(Field{ field });
}

void Row::pushCell(String&& field)
{
	fields.pushBack(Field{ std::move(field) });
}


void Row::setCellAt(size_t fieldIdx, const String& field)
{
	fields[fieldIdx].data = field;
}

void Row::setCellAt(size_t fieldIdx, String&& field)
{
	fields[fieldIdx].data = std::move(field);
}

const String& Row::getCell(size_t fieldIdx) const
{
	return fields[fieldIdx].data;
}

void Row::removeCellAt(size_t fieldIdx)
{
	fields.popAt(fieldIdx);
}