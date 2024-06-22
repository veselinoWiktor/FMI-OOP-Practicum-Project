#pragma once

#include "TableCommand.h"

class InsertCommand : public TableCommand
{
private:
	Vector<Row> rows;
public:
	InsertCommand(Table& table, const Vector<Row>& rows);
	SQLResponse execute() override;
};

