#pragma once

#include "SQLCommand.h"
#include "StringView.h"
#include "CreateTableCommand.h"


class SQLCommandFactory
{
	SQLCommandType getCommandType(const StringView& query);

	SQLCommand* handleCreateTableCommand(Vector<Table>& tables, const String& query);
public:
	SQLCommand* createCommand(Vector<Table>& tables, const String& query);
};

