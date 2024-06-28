#pragma once

#include "SQLCommand.h"
#include "StringView.h"

#include "CreateTableCommand.h"
#include "DropTableCommand.h"
#include "AlterTableCommands.h"
#include "ShowCommand.h"
#include "InsertCommand.h"
#include "UpdateCommand.h"
#include "DeleteCommand.h"
#include "SelectCommand.h"

#include "Utils.h"


class SQLCommandFactory
{
	SQLCommandType getCommandType(const String& command);

	SQLCommand* handleCreateTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleDropTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleShowTablesCommand(Vector<Table>& tables, const String& databaseName);
	SQLCommand* handleAlterTableCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleInsertCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleUpdateCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleDeleteCommand(Vector<Table>& tables, std::stringstream& ssQuery);
	SQLCommand* handleSelectCommand(Vector<Table>& tables, std::stringstream& ssQuery);
public:
	SQLCommand* createCommand(Vector<Table>& tables, const String& query, const String& databaseName);
};

