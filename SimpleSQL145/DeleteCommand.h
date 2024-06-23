#pragma once	
#include "TableCommand.h"
#include "WhereExpressionCalculator.h"

class DeleteCommand : public TableCommand
{
private:
	String whereExpression;
public:
	DeleteCommand(Table& table, const String& whereExpression);
	SQLResponse execute() override;
};

