#pragma once

#include "SQLCommand.h"
#include "Table.h"
#include "Vector.hpp"

class TableCommand : public SQLCommand
{
protected:
	Table& table;
public:
	TableCommand(Table& table);
	~TableCommand() = default;
};

