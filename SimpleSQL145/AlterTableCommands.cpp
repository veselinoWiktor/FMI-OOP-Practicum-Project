#include "AlterTableCommands.h"

AlterAddCommand::AlterAddCommand(Table& table, const Column& column)
	: TableCommand(table), column(column)
{
}

SQLResponse AlterAddCommand::execute()
{
	table.insertColumn(std::move(column));

	return SQLResponse(); // TODO fix SQLResponse();
}

AlterRenameCommand::AlterRenameCommand(Table& table, const String& colName, const String& newColName)
	: TableCommand(table), colName(colName), newColName(newColName)
{
}

SQLResponse AlterRenameCommand::execute()
{
	table.renameColumn(colName, newColName);

	return SQLResponse();
}

AlterDropCommand::AlterDropCommand(Table& table, const String& colName)
	: TableCommand(table), colName(colName)
{
}

SQLResponse AlterDropCommand::execute()
{
	table.removeColumnByName(colName);
	return SQLResponse();
}
