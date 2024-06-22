#pragma once
#include "SQLResponse.h"
#include "SQLEngine.h"

class SQLCommand
{
private:
public:
	virtual ~SQLCommand() = default;

	virtual SQLResponse execute() = 0;
};

