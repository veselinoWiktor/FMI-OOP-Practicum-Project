#pragma once
#include "TableCommand.h"

class AlterAddCommand : public TableCommand
{
private:
	Column column;
public:
	AlterAddCommand(Table& table, const Column& column);
	SQLResponse execute() override;
};

class AlterRenameCommand : public TableCommand
{
private:
	String colName;
	String newColName;
public:
	AlterRenameCommand(Table& table, const String& colName, const String& newColName);
	SQLResponse execute() override;
};

class AlterDropCommand : public TableCommand
{
private:
	String colName;
public:
	AlterDropCommand(Table& table, const String& colName);
	SQLResponse execute() override;
};



