#pragma once
#include "String.h"

enum class ColumnType
{
	Integer,
	Real,
	Text
};

static ColumnType parseColumnType(const String& str)
{
	if (str == "int")
	{
		return ColumnType::Integer;
	}
	else if (str == "real")
	{
		return ColumnType::Real;
	}
	else 
	{
		return ColumnType::Text;
	}
}

struct Column
{
	String name = "";
	ColumnType type = ColumnType::Text;

	Column() = default;
	Column(const String& name, const ColumnType& type);

	friend std::ifstream& operator>>(std::ifstream& ifs, Column& column);
};

