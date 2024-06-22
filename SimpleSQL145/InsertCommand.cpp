#include "InsertCommand.h"

InsertCommand::InsertCommand(Table& table, const Vector<Row>& rows)
	: TableCommand(table), rows(rows)
{
}

SQLResponse InsertCommand::execute()
{
	int colsCount = table.getColumnsCount();
	if (rows[0].getCellsCount() > colsCount)
	{
		//TODO can't have this;
	}

	for (size_t i = 0; i < rows.getSize(); i++)
	{
		table.insertRow(std::move(rows[i])); //HACK will be faster
	}

	return SQLResponse(); //TODO add appropriate SQLResponse
}
