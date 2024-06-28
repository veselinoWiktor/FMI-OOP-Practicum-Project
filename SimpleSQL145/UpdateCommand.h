#pragma once

#include "TableCommand.h"
#include "WhereExpressionCalculator.h"

class UpdateCommand : public TableCommand
{
private:
	String columnName;
	String value;
	String whereExpression; 

public:
	UpdateCommand(Table& table, const String& columnName, const String& value);
	UpdateCommand(Table& table, const String& columnName, const String& value, const String& whereExpression);

	SQLResponse execute() override;
};

