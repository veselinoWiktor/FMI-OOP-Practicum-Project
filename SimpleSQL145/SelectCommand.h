#pragma once
#include "TableCommand.h"
#include "WhereExpressionCalculator.h"

class SelectCommand : public TableCommand
{
private:
	Vector<String> columnNames;
	String whereExpression;
public:
	SelectCommand(Table& table, const Vector<String>& columnNames);
	SelectCommand(Table& table, const Vector<String>& columnNames, const String& whereExpression);
	SQLResponse execute() override;
};

