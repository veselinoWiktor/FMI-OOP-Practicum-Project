#pragma once

#include "SQLCommand.h"
#include "StringView.h"

#include "CreateTableCommand.h"
#include "DropTableCommand.h"
#include "AlterTableCommands.h"
#include "InsertCommand.h"
#include "DeleteCommand.h"

#include "Utils.h"


class SQLCommandFactory
{
	SQLCommandType getCommandType(const String& command);

	SQLCommand* handleCreateTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleDropTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);

	SQLCommand* handleAlterTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleInsertCommand(Vector<Table>& tables, std::stringstream& ssQuery);

	SQLCommand* handleDeleteCommand(Vector<Table>& tables, std::stringstream& ssQuery);
public:
	SQLCommand* createCommand(Vector<Table>& tables, const String& query);
};

