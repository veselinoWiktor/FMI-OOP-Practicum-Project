#include "DeleteCommand.h"

#include "Utils.h"

DeleteCommand::DeleteCommand(Table& table, const String& whereExpression)
	: TableCommand(table), whereExpression(whereExpression)
{
}

SQLResponse DeleteCommand::execute()
{
	Vector<Row> tableRows = table.getRows();
	WhereExpressionHandler handler(whereExpression);

	int affectedRows = 0;
	for (size_t i = 0; i < tableRows.getSize(); i++)
	{
		if (handler.evaluate(table, i))
		{
			table.removeRowAt(i);
			affectedRows++;
		}
	}

	return SQLResponse("Query OK, " + DataUtils::intToString(affectedRows) + " rows affected");
}
