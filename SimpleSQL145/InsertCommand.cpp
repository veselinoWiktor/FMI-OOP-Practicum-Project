#include "InsertCommand.h"

#include "Utils.h"

InsertCommand::InsertCommand(Table& table, const Vector<Row>& rows)
	: TableCommand(table), rows(rows)
{
}

SQLResponse InsertCommand::execute()
{
	//int colsCount = table.getColumnsCount();
	//if (rows[0].getCellsCount() > colsCount)
	//{
	//	//TODO can't have this;
	//}
	int affectedRows = 0;
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		table.insertRow(std::move(rows[i])); //HACK will be faster
		affectedRows++;
	}

	
	return SQLResponse("Query OK, " + DataUtils::intToString(affectedRows) + " rows affected");
}
