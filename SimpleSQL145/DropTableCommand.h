#pragma once

#include "String.h"
#include "DatabaseCommand.h"

class DropTableCommand : public DatabaseCommand
{
private:
	String tableName;
public:
	DropTableCommand(Vector<Table>& tables, const String& tableName);
	SQLResponse execute() override;
};

