#pragma once
#include "DatabaseCommand.h"

class CreateTableCommand : public DatabaseCommand
{
private:
	Vector<Column> columns;
	String tableName;
public:
	CreateTableCommand(Vector<Table>& tables, const Vector<Column>& columns, const String& tableName);
	SQLResponse execute() override;
};

