#pragma once
#include "TableCommand.h"
#include "WhereExpressionCalculator.h"

class SelectCommand : public TableCommand
{
private:
	Vector<String> columnNames;
	String whereExpression;
	Vector<String> joinColumnNames;
	const Table* joinTable;
public:
	SelectCommand(Table& table, const Vector<String>& columnNames);
	SelectCommand(Table& table, const Vector<String>& columnNames, const String& whereExpression);
	SelectCommand(Table& table, const Vector<String>& columnNames, const Vector<String>& joinColumnNames, const Table* joinTable);
	SQLResponse execute() override;
};

