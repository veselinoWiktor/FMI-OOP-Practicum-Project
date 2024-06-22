#pragma once
#include "String.h"

enum class ColumnType
{
	Integer,
	Real,
	Text
};

struct Column
{
	String name = "";
	ColumnType type = ColumnType::Text;

	Column() = default;
	Column(const String& name, const ColumnType& type);

	friend std::ifstream& operator>>(std::ifstream& ifs, Column& column);
};

