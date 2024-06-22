#pragma once
#include "SQLResponse.h"
#include "SQLEngine.h"

enum class SQLCommandType
{
	CreateTable,
	DropTable,
	AlterTable,
	ShowTables,
	Insert,
	Update,
	Delete,
	Select
};

class SQLCommand
{
private:
public:
	virtual ~SQLCommand() = default;

	virtual SQLResponse execute() = 0;
};

