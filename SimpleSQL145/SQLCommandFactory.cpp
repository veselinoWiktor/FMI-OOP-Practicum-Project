#include "SQLCommandFactory.h"

SQLCommandType SQLCommandFactory::getCommandType(const StringView& query)
{
	int count = 0;
	//can be more complex to get first word of the query
	for (size_t i = 0; i < query.length(); i++)
	{
		if (query[i] != ' ')
			count++;
		else
			break;
	}

	StringView command = query.substr(0, count);

	if (command == "create")
	{
		return SQLCommandType::CreateTable;
	}
	else if (command == "drop")
	{
		return SQLCommandType::DropTable;
	}
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

SQLCommand* SQLCommandFactory::createCommand(Vector<Table>& tables, const String& query)
{
	SQLCommandType commandType = getCommandType(query);

	
	switch (commandType)
	{
	case SQLCommandType::CreateTable:
		return handleCreateTableCommand(tables, query);
		break;
	case SQLCommandType::DropTable:
		return handleDropTableCommand(tables, query);
		break;
	case SQLCommandType::AlterTable:
		break;
	case SQLCommandType::ShowTables:
		break;
	case SQLCommandType::Insert:
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
