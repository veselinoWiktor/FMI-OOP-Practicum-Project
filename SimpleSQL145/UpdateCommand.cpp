#include "UpdateCommand.h"

UpdateCommand::UpdateCommand(Table& table, const String& columnName, const String& value)
	: TableCommand(table), columnName(columnName), value(value), whereExpression(nullptr)
{
}

UpdateCommand::UpdateCommand(Table& table, const String& columnName, const String& value, const String* whereExpression)
	: TableCommand(table), columnName(columnName), value(value), whereExpression(whereExpression)
{
}

SQLResponse UpdateCommand::execute()
{
	Vector<Row> tableRows = table.getRows();

	if (!whereExpression)
	{
		for (size_t i = 0; i < tableRows.getSize(); i++)
			table.setCellVal(i, columnName, value);
	}
	else
	{
		WhereExpressionHandler handler(*whereExpression);
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			if (handler.evaluate(table, i))
			{
				table.setCellVal(i, columnName, value);
			}
		}

	}

	return SQLResponse();
}
