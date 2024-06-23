#include "SQLResponse.h"

#include "TableParser.h"

SQLResponse::SQLResponse(const String& message)
	: message(message)
{
}

SQLResponse::SQLResponse(const Table& table)
{
	message = TableParser::parseTable(table);
}

const String& SQLResponse::getMessage()
{
	return message;
}
