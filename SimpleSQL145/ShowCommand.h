#pragma once
#include "DatabaseCommand.h"
#include "Table.h"
#include "String.h"

class ShowCommand : public DatabaseCommand
{
private:
	String databaseName;
public:
	ShowCommand(Vector<Table>& tables, const String& databaseName);
	SQLResponse execute() override;
};

