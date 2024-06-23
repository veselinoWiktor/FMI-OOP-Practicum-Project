#include "SelectCommand.h"

SelectCommand::SelectCommand(Table& table, const Vector<String>& columnNames)
	: SelectCommand(table, columnNames, nullptr)
{
}

SelectCommand::SelectCommand(Table& table, const Vector<String>& columnNames, const String* whereExpression)
	: TableCommand(table), columnNames(columnNames), whereExpression(whereExpression)
{
}

SQLResponse SelectCommand::execute()
{
	Table newTable;

	for (size_t i = 0; i < columnNames.getSize(); i++)
	{
		newTable.insertColumn(table.getColumn(columnNames[i]));
	}

	Vector<Row> tableRows = table.getRows();
	Vector<Column> tableColumns = table.getColumns();

	if (!whereExpression)
	{
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			Row curr;
			for (size_t j = 0; j < tableColumns.getSize(); j++)
			{
				if (columnNames.contains(tableColumns[j].name))
				{
					curr.pushCell(table.getCellVal(i, j));
				}
			}
			newTable.insertRow(curr);
		}
	}
	else
	{
		WhereExpressionHandler handler(*whereExpression);
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			if (!handler.evaluate(table, i))
			{
				continue;
			}

			Row curr;
			for (size_t j = 0; j < tableColumns.getSize(); j++)
			{
				if (columnNames.contains(tableColumns[j].name))
				{
					curr.pushCell(table.getCellVal(i, j));
				}
			}
			newTable.insertRow(curr);
		}
	}

	return SQLResponse();
}
