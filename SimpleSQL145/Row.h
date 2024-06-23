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

	void pushCell(const String& field);
	void pushCell(String&& field);

	void setCellAt(size_t fieldIdx, const String& field);
	void setCellAt(size_t fieldIdx, String&& field);

	const String& getCell(size_t fieldIdx) const;

	void removeCellAt(size_t fieldIdx);

	//friend std::ofstream& operator<<(std::ofstream& ofs, const Row& row);
	friend std::ifstream& operator>>(std::ifstream& ifs, Row& row);
};
