#include "ShowCommand.h"

ShowCommand::ShowCommand(Vector<Table>& tables, const String& databaseName)
	: DatabaseCommand(tables), databaseName(databaseName)
{
}

SQLResponse ShowCommand::execute()
{
	Table result;
	
	Column column(databaseName, ColumnType::Text);
	result.insertColumn(column);

	for (size_t i = 0; i < tables.getSize(); i++)
	{
		Row row;
		row.pushCell(tables[i].getName());
		result.insertRow(row);
	}

	return SQLResponse(result);
}
