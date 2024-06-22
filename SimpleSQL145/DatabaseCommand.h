#pragma once
#include "SQLCommand.h"
#include "Vector.hpp"
#include "Table.h"

class DatabaseCommand : public SQLCommand
{
protected:
	Vector<Table>& tables;
public:
	DatabaseCommand(Vector<Table>& tables);
	~DatabaseCommand() = default;
};

