#include "UpdateCommand.h"

#include "Utils.h"

UpdateCommand::UpdateCommand(Table& table, const String& columnName, const String& value)
	: TableCommand(table), columnName(columnName), value(value), whereExpression(nullptr)
{
}

UpdateCommand::UpdateCommand(Table& table, const String& columnName, const String& value, const String& whereExpression)
	: TableCommand(table), columnName(columnName), value(value), whereExpression(whereExpression)
{
}

SQLResponse UpdateCommand::execute()
{
	Vector<Row> tableRows = table.getRows();

	int affectedRows = 0;
	if (whereExpression == "")
	{
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			table.setCellVal(i, columnName, value);
			affectedRows++;
		}
	}
	else
	{
		WhereExpressionHandler handler(whereExpression);
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			if (handler.evaluate(table, i))
			{
				table.setCellVal(i, columnName, value);
				affectedRows++;
			}
		}

	}

	return SQLResponse("Query OK, " + DataUtils::intToString(affectedRows) + " rows affected");
}
