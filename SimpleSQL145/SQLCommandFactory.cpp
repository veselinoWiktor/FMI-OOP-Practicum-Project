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
	else if (command == "insert")
	{
		return SQLCommandType::Insert;
	}

	return SQLCommandType::Select;
}

SQLCommand* SQLCommandFactory::handleCreateTableCommand(Vector<Table>& tables, const String& query)
{
	int tblNameLen = 0;
	StringView sv(query.c_str() + 13, query.c_str() + query.getLength());
	for (size_t i = 0; i < sv.length(); i++)
	{
		if (sv[i] != ' ')
		{
			tblNameLen++;
		}
		else
		{
			break;
		}
	}

	String tblName = query.substr(13, tblNameLen);
	String columnData = query.substr(13 + tblNameLen + 2, query.getLength() - 1 - (13 + tblNameLen + 2));
	std::stringstream ss(columnData.c_str());

	char buff[1024];
	Vector<Column> columns;
	while (!ss.eof())
	{
		Column curr;
		ss.getline(buff, 1024, ' ');
		curr.name = buff;
		ss.getline(buff, 1024, ',');
		curr.type = parseColumnType(buff);
		columns.pushBack(curr);

		ss.ignore();
	}

	return new CreateTableCommand(tables, columns, tblName);
}

SQLCommand* SQLCommandFactory::handleDropTableCommand(Vector<Table>& tables, const String& query)
{
	String tblName = query.substr(11, query.getLength() - 11);

	return new DropTableCommand(tables, tblName);
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
				currRow.addField(buff);
				SSUtils::clearWhiteSpaces(ssQuery);
			}
			else
			{
				currRow.addField("NULL");
			}
		}
		rows.pushBack(currRow);
	}
	
	return new InsertCommand(tbl, rows);
}

SQLCommand* SQLCommandFactory::createCommand(Vector<Table>& tables, const String& query)
{
	std::stringstream ssQuery(query.c_str());
	SSUtils::clearWhiteSpaces(ssQuery);
	char command[1024];
	ssQuery.getline(command, 1024, ' ');
	SQLCommandType commandType = getCommandType(command);

	
	switch (commandType)
	{
	case SQLCommandType::CreateTable:
		return handleCreateTableCommand(tables, query);
		break;
	case SQLCommandType::DropTable:
		return handleDropTableCommand(tables, query);
		break;
	case SQLCommandType::AlterTable:
		return handleAlterTableCommand(tables, ssQuery);
		break;
	case SQLCommandType::ShowTables:
		break;
	case SQLCommandType::Insert:
		return handleInsertCommand(tables, ssQuery);
		break;
	case SQLCommandType::Update:
		break;
	case SQLCommandType::Delete:
		break;
	case SQLCommandType::Select:
		break;
	default:
		break;
	}

	return nullptr;
}
