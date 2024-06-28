#include "SQLCommandFactory.h"

SQLCommandType SQLCommandFactory::getCommandType(const String& command)
{
	if (command == "create")
	{
		return SQLCommandType::CreateTable;
	}
	else if (command == "drop")
	{
		return SQLCommandType::DropTable;
	}
	else if (command == "alter")
	{
		return SQLCommandType::AlterTable;
	}
	else if (command == "show")
	{
		return SQLCommandType::ShowTables;
	}
	else if (command == "insert")
	{
		return SQLCommandType::Insert;
	}
	else if (command == "update")
	{
		return SQLCommandType::Update;
	}
	else if (command == "delete")
	{
		return SQLCommandType::Delete;
	}
	else
	{
		return SQLCommandType::Select;
	}
}

SQLCommand* SQLCommandFactory::handleCreateTableCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	//create table table1.ss145 (field1 int, field2 text, field3 real);
	SSUtils::clearWhiteSpaces(ssQuery);
	char buff[1024];
	ssQuery.getline(buff, 1024, ' '); // skips "table"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name;
	String tblName(buff);

	ssQuery.getline(buff, 1024, '('); // clears everything before and including "("
	ssQuery.getline(buff, 1024, ')'); // gets columns data in brackets
	String columnData(buff);

	ssQuery.clear();
	ssQuery.str(columnData.c_str());
	Vector<Column> columns;
	while (!ssQuery.eof())
	{
		Column curr;
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' ');
		curr.name = buff; // gets column name

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ','); // gets column type
		curr.type = parseColumnType(buff);

		columns.pushBack(curr);
	}

	return new CreateTableCommand(tables, columns, tblName);
}

SQLCommand* SQLCommandFactory::handleDropTableCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	SSUtils::clearWhiteSpaces(ssQuery);
	char buff[1024];
	ssQuery.getline(buff, 1024, ' '); // skips "table"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name;
	String tblName(buff);
	Table& tbl = TableUtils::findTable(tables, tblName);

	return new DropTableCommand(tables, tblName);
}

SQLCommand* SQLCommandFactory::handleShowTablesCommand(Vector<Table>& tables, const String& databaseName)
{
	return new ShowCommand(tables, databaseName);
}

SQLCommand* SQLCommandFactory::handleAlterTableCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	SSUtils::clearWhiteSpaces(ssQuery);
	char buff[1024];
	ssQuery.getline(buff, 1024, ' '); // skips "table"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name;
	String tblName(buff);
	Table& tbl = TableUtils::findTable(tables, tblName);

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' ');
	String operation(buff);

	if (operation == "add")
	{
		Column newColumn;

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' ');
		newColumn.name = buff;

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' ');
		newColumn.type = parseColumnType(buff);

		return new AlterAddCommand(tbl, newColumn);
	}
	else if (operation == "rename")
	{
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // skips "column"

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // gets column name
		String columnName(buff);

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // skips "to"

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // gets new column name
		String newColumnName(buff);

		return new AlterRenameCommand(tbl, columnName, newColumnName);
	}
	else
	{
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // skips "column"

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // gets column name
		String columnName(buff);

		return new AlterDropCommand(tbl, columnName);
	}
}

SQLCommand* SQLCommandFactory::handleInsertCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	SSUtils::clearWhiteSpaces(ssQuery);
	char buff[1024];
	ssQuery.getline(buff, 1024, ' '); //skips "into"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); //gets table name;
	String tblName(buff); 
	Table& tbl = TableUtils::findTable(tables, tblName);

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.get(); //gets '('

	ssQuery.getline(buff, 1024, ')'); //gets selected columns for insertion
	String columnsData(buff);
	
	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // skips "values"
	SSUtils::clearWhiteSpaces(ssQuery);

	ssQuery.getline(buff, 1024); //gets values for insertion
	String rowsData(buff);

	Vector<String> columnNames;
	ssQuery.clear();
	ssQuery.str(columnsData.c_str());
	while (!ssQuery.eof())
	{
		ssQuery.getline(buff, 1024, ',');
		SSUtils::clearWhiteSpaces(ssQuery);
		columnNames.pushBack(buff);
	}

	Vector<String> records; // used to store record (..., ..., ...) <- one of this
	ssQuery.clear();
	ssQuery.str(rowsData.c_str());
	while (!ssQuery.eof())
	{
		ssQuery.get(); // Skips "("
		ssQuery.getline(buff, 1024, ')');
		records.pushBack(buff);
		ssQuery.get(); // Skips ","
		SSUtils::clearWhiteSpaces(ssQuery);
	}

	Vector<Column> tblColumns = tbl.getColumns();
	Vector<Row> rows; //makes the final rows;
	for (size_t i = 0; i < records.getSize(); i++)
	{
		Row currRow;
		ssQuery.clear();
		ssQuery.str(records[i].c_str());
		
		for (size_t i = 0; i < tblColumns.getSize(); i++)
		{
			if (columnNames.contains(tblColumns[i].name))
			{
				ssQuery.getline(buff, 1024, ',');
				currRow.pushCell(buff);
				SSUtils::clearWhiteSpaces(ssQuery);
			}
			else
			{
				currRow.pushCell("NULL");
			}
		}
		rows.pushBack(currRow);
	}
	
	return new InsertCommand(tbl, rows);
}

//update test_table set field2=2.0 where (((field1)>(2))&((field1)<(4)));
SQLCommand* SQLCommandFactory::handleUpdateCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	char buff[1024];
	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name
	String tblName(buff);
	Table& tbl = TableUtils::findTable(tables, tblName);

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // skips "set"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, '='); // gets column name
	String columnName(buff);

	ssQuery.getline(buff, 1024, ' '); // gets update value
	String value(buff);

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // skips if there is where

	if ((String)buff == "where")
	{
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ';'); // gets where expression
		String whereExpression(buff);

		return new UpdateCommand(tbl, columnName, value, whereExpression);
	}
	else
	{
		return new UpdateCommand(tbl, columnName, value);
	}
}

SQLCommand* SQLCommandFactory::handleDeleteCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	char buff[1024];
	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // skips "from"

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name
	String tblName(buff);
	Table& tbl = TableUtils::findTable(tables, tblName);

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // skips "where" !!! it is required in delete command

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ';'); // gets where expression
	String whereExpression(buff);

	return new DeleteCommand(tbl, whereExpression);
}

// select * from test_table;
// select field1 from test_table;
// select field1 from test_table where field1=2;
// select * from join1 where (((field1_1)>(1))&((field1_1)<(3)));
// select * from join1 join join2 on field1_1=field1_2
// select field1_1, field1_2, field2_2 from join1 join join2 on field1_1=field1_2
SQLCommand* SQLCommandFactory::handleSelectCommand(Vector<Table>& tables, std::stringstream& ssQuery)
{
	char buff[1024];
	Vector<String> columnNames;

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' ');
	while ((String)buff != "from")
	{
		size_t buffLen = strlen(buff);
		if (buff[buffLen - 1] == ',')
		{
			buff[buffLen - 1] = '\0';
		}
		columnNames.pushBack(buff);
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // that would skip "from" automatically
	}

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets table name
	String tblName = buff;
	Table& tbl = TableUtils::findTable(tables, tblName);

	Vector<Column> columns = tbl.getColumns();
	int asteriksIdx = -1;
	for (size_t i = 0; i < columnNames.getSize(); i++)
	{
		if (columnNames[i] == "*")
		{
			for (size_t j = 0; j < columns.getSize(); j++)
			{
				if (columnNames.getSize() == 0)
					columnNames.pushBack(columns[j].name);
				else
					columnNames.pushAt(columns[j].name, i);
				i++;
			}
			asteriksIdx = i;
		}
	}

	SSUtils::clearWhiteSpaces(ssQuery);
	ssQuery.getline(buff, 1024, ' '); // gets if there is join or where;
	
	if((String)buff == "join")
	{
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // gets table name
		String joinTblName = buff;
		Table& joinTbl = TableUtils::findTable(tables, joinTblName);
		Vector<Column> joinTblColumns = joinTbl.getColumns();

		if (asteriksIdx != -1)
		{
			for (size_t i = 0; i < joinTblColumns.getSize(); i++)
			{
				columnNames.pushAt(joinTblColumns[i].name, asteriksIdx);
				asteriksIdx++;
				columnNames.popAt(asteriksIdx);
			}
		}

		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // skips "on"

		Vector<String> joinColumnNames;
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, '='); // gets join expression
		joinColumnNames.pushBack(buff);
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ' '); // gets join expression
		joinColumnNames.pushBack(buff);

		return new SelectCommand(tbl, columnNames, joinColumnNames, &joinTbl);
	}
	else if ((String)buff == "where")
	{
		SSUtils::clearWhiteSpaces(ssQuery);
		ssQuery.getline(buff, 1024, ';'); // gets where expression
		String whereExpression(buff);
		
		if (asteriksIdx != -1)
		{
			columnNames.popAt(asteriksIdx);
		}

		return new SelectCommand(tbl, columnNames, whereExpression);
	}
	else
	{
		if (asteriksIdx != -1)
		{
			columnNames.popAt(asteriksIdx);
		}

		return new SelectCommand(tbl, columnNames);
	}
}

SQLCommand* SQLCommandFactory::createCommand(Vector<Table>& tables, const String& query, const String& databaseName)
{
	std::stringstream ssQuery(query.c_str());
	SSUtils::clearWhiteSpaces(ssQuery);
	char command[1024];
	ssQuery.getline(command, 1024, ' ');
	SQLCommandType commandType = getCommandType(command);

	
	switch (commandType)
	{
	case SQLCommandType::CreateTable:
		return handleCreateTableCommand(tables, ssQuery);
		break;
	case SQLCommandType::DropTable:
		return handleDropTableCommand(tables, ssQuery);
		break;
	case SQLCommandType::AlterTable:
		return handleAlterTableCommand(tables, ssQuery);
		break;
	case SQLCommandType::ShowTables:
		return handleShowTablesCommand(tables, databaseName);
		break;
	case SQLCommandType::Insert:
		return handleInsertCommand(tables, ssQuery);
		break;
	case SQLCommandType::Update:
		return handleUpdateCommand(tables, ssQuery);
		break;
	case SQLCommandType::Delete:
		return handleDeleteCommand(tables, ssQuery);
		break;
	case SQLCommandType::Select:
		return handleSelectCommand(tables, ssQuery);
		break;
	}
}
