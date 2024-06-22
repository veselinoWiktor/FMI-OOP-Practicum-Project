#pragma once

#include <iostream>

#include "String.h"
#include "sstream"

#include "Vector.hpp"


struct Field
{
	String data = "NULL";
};

class Row
{
private:
	Vector<Field> fields;

public:
	size_t getCellsCount() const;

	void addField(const String& field);
	void addField(String&& field);

	//friend std::ofstream& operator<<(std::ofstream& ofs, const Row& row);
	friend std::ifstream& operator>>(std::ifstream& ifs, Row& row);
};
