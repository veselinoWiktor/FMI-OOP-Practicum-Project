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

	//friend std::ofstream& operator<<(std::ofstream& ofs, const Row& row);
	friend std::ifstream& operator>>(std::ifstream& ifs, Row& row);
};
