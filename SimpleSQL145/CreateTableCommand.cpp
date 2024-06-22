#include "CreateTableCommand.h"

CreateTableCommand::CreateTableCommand(Vector<Table>& tables, const Vector<Column>& columns, const String& tableName) 
	: DatabaseCommand(tables), columns(columns), tableName(tableName)
{
}

SQLResponse CreateTableCommand::execute()
{
	Table newTable(tableName);
	for (size_t i = 0; i < columns.getSize(); i++)
	{
		newTable.insertColumn(columns[i]);
	}

	tables.pushBack(newTable);

	return SQLResponse();
	//TODO add SQLResponse
}
