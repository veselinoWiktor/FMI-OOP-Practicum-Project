#include "SQLResponse.h"

SQLResponse::SQLResponse(const String& message)
	: message(message)
{
}

SQLResponse::SQLResponse(const Table& table)
{
}

const String& SQLResponse::getMessage()
{
	return message;
}
