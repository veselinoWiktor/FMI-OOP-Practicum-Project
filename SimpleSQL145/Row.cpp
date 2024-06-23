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

void Row::addField(const String& field)
{
	fields.pushBack(Field{field});
}

void Row::addField(String&& field)
{
	fields.pushBack(Field{ std::move(field) });
}

void Row::removeFieldAt(size_t fieldIdx)
{
	fields.popAt(fieldIdx);
}

const String& Row::getField(size_t fieldIdx) const
{
	return fields[fieldIdx].data;
}
