#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Table& table, const String& whereExpression)
	: TableCommand(table), whereExpression(whereExpression)
{
}

SQLResponse DeleteCommand::execute()
{
	Vector<Row> tableRows = table.getRows();
	WhereExpressionHandler handler(whereExpression);

	for (size_t i = 0; i < tableRows.getSize(); i++)
	{
		if (handler.evaluate(table, i))
		{
			table.removeRowAt(i);
		}
	}

	return SQLResponse();
}
