#include "SelectCommand.h"

SelectCommand::SelectCommand(Table& table, const Vector<String>& columnNames)
	: TableCommand(table), columnNames(columnNames), whereExpression(""), joinColumnNames(), joinTable(nullptr)
{
}

SelectCommand::SelectCommand(Table& table, const Vector<String>& columnNames, const String& whereExpression)
	: TableCommand(table), columnNames(columnNames), whereExpression(whereExpression), joinColumnNames(), joinTable(nullptr)
{
}

SelectCommand::SelectCommand(Table& table, const Vector<String>& columnNames, const Vector<String>& joinColumnNames, const Table* joinTable)
	: TableCommand(table), columnNames(columnNames), whereExpression(""), joinColumnNames(joinColumnNames), joinTable(joinTable)
{
}

SQLResponse SelectCommand::execute()
{
	Table newTable;

	for (size_t i = 0; i < columnNames.getSize(); i++)
	{
		int idx = table.getColumnIndex(columnNames[i]);
		if (idx != -1)
		{
			newTable.insertColumn(table.getColumn(idx));
		}
		else if (joinTable != nullptr)
		{
			idx = joinTable->getColumnIndex(columnNames[i]);
			newTable.insertColumn(joinTable->getColumn(idx));
		}
	}

	Vector<Row> tableRows = table.getRows();
	Vector<Column> tableColumns = table.getColumns();

	if (whereExpression != "")
	{
		WhereExpressionHandler handler(whereExpression);
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
	else if (joinColumnNames.getSize() != 0 && joinTable != nullptr)
	{
		size_t tblColIdx = table.getColumnIndex(joinColumnNames[0]);
		size_t joinTblColIdx = joinTable->getColumnIndex(joinColumnNames[1]);

		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			Row curr;
			if (table.getCellVal(i, tblColIdx) != joinTable->getCellVal(i, joinTblColIdx))
			{
				continue;
			}

			for (size_t j = 0; j < columnNames.getSize(); j++)
			{
				int idx = table.getColumnIndex(columnNames[j]);
				if (idx != -1)
				{
					curr.pushCell(table.getCellVal(i, idx));
				}
				else
				{
					idx = joinTable->getColumnIndex(columnNames[j]);
					curr.pushCell(joinTable->getCellVal(i, idx));
				}
			}
			newTable.insertRow(curr);
		}
	}
	else
	{
		for (size_t i = 0; i < tableRows.getSize(); i++)
		{
			Row curr;
			for (size_t j = 0; j < columnNames.getSize(); j++)
			{
				int idx = table.getColumnIndex(columnNames[j]);
				if (idx != -1)
				{
					curr.pushCell(table.getCellVal(i, idx));
				}
			}
			newTable.insertRow(curr);
		}
	}
	return SQLResponse(newTable);
}
