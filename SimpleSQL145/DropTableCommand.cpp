#include "DropTableCommand.h"

DropTableCommand::DropTableCommand(Vector<Table>& tables, const String& tableName)
	:	DatabaseCommand(tables), tableName(tableName)
{
}

SQLResponse DropTableCommand::execute()
{
	int dropTblIdx = -1;
	for (int i = 0; i < tables.getSize(); i++)
	{
		if (tables[i].getName() == tableName)
		{
			dropTblIdx = i;
		}
	}

	tables.popAt(dropTblIdx);
	return SQLResponse();
	//TODO implement SQLResponse return
}
