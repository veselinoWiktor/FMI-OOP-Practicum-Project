#include "InsertCommand.h"

#include "Utils.h"

InsertCommand::InsertCommand(Table& table, const Vector<Row>& rows)
	: TableCommand(table), rows(rows)
{
}

SQLResponse InsertCommand::execute()
{
	int affectedRows = 0;
	for (size_t i = 0; i < rows.getSize(); i++)
	{
		table.insertRow(std::move(rows[i]));
		affectedRows++;
	}

	
	return SQLResponse("Query OK, " + DataUtils::intToString(affectedRows) + " rows affected");
}
