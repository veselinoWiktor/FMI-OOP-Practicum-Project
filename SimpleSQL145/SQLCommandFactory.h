#pragma once

#include "SQLCommand.h"
#include "StringView.h"

#include "CreateTableCommand.h"
#include "DropTableCommand.h"
#include "InsertCommand.h"

#include "Utils.h"


class SQLCommandFactory
{
	SQLCommandType getCommandType(const String& command);

	SQLCommand* handleCreateTableCommand(Vector<Table>& tables, const String& query);
	SQLCommand* handleDropTableCommand(Vector<Table>& tables, const String& query);

	SQLCommand* handleInsertCommand(Vector<Table>& tables, const String& query, std::stringstream& ssQuery);
public:
	SQLCommand* createCommand(Vector<Table>& tables, const String& query);
};

