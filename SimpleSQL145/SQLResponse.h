#pragma once

#include "String.h"
#include "Table.h"	

class SQLResponse
{
private:
	String message;
public:
	SQLResponse() = default;
	SQLResponse(const String& message);
	SQLResponse(const Table& table);

	const String& getMessage();
};

