#include "WhereExpressionCalculator.h"

ComparisonOperation::ComparisonOperation(const String& columnName, int value)
	: columnName(columnName), value(value)
{
}

LessThan::LessThan(const String& columnName, int value)
	: ComparisonOperation(columnName, value)
{
}

bool LessThan::eval(Table& table, size_t rowIdx) const
{
	Column currCol = table.getColumn(columnName);
	
	if (currCol.type == ColumnType::Integer)
	{
		int fieldValue = DataUtils::intParse(table.getCellVal(rowIdx, columnName));
		if (fieldValue < value)
		{
			return true;
		}
	}
	else if(currCol.type == ColumnType::Real)
	{
		double fieldValue = std::stod(table.getCellVal(rowIdx, columnName).c_str()); // no time to make double converter
		if (fieldValue < value)
		{
			return true;
		}
	}

	return false;
}

BooleanExpression* LessThan::clone() const
{
	return new LessThan(this->columnName, this->value);
}

GreaterThan::GreaterThan(const String& columnName, int value)
	: ComparisonOperation(columnName, value)
{
}

bool GreaterThan::eval(Table& table, size_t rowIdx) const
{
	Column currCol = table.getColumn(columnName);

	if (currCol.type == ColumnType::Integer)
	{
		int fieldValue = DataUtils::intParse(table.getCellVal(rowIdx, columnName));
		if (fieldValue > value)
		{
			return true;
		}
	}
	else if (currCol.type == ColumnType::Real)
	{
		double fieldValue = std::stod(table.getCellVal(rowIdx, columnName).c_str()); // no time to make double converter
		if (fieldValue > value)
		{
			return true;
		}
	}

	return false;
}

BooleanExpression* GreaterThan::clone() const
{
	return new GreaterThan(this->columnName, this->value);
}

Equals::Equals(const String& columnName, int value)
	: ComparisonOperation(columnName, value)
{
}

bool Equals::eval(Table& table, size_t rowIdx) const
{
	Column currCol = table.getColumn(columnName);

	if (currCol.type == ColumnType::Integer)
	{
		int fieldValue = DataUtils::intParse(table.getCellVal(rowIdx, columnName));
		if (fieldValue == value)
		{
			return true;
		}
	}
	else if (currCol.type == ColumnType::Real)
	{
		double fieldValue = std::stod(table.getCellVal(rowIdx, columnName).c_str()); // no time to make double converter
		if (fieldValue - value <= 0.0000001)
		{
			return true;
		}
	}

	return false;
}

BooleanExpression* Equals::clone() const
{
	return new Equals(this->columnName, this->value);
}

LogicalOperation::LogicalOperation(BooleanExpression* left, BooleanExpression* right)
	: left(left), right(right)
{
}

LogicalOperation::~LogicalOperation()
{
	delete left;
	delete right;
}

Conjunction::Conjunction(BooleanExpression* left, BooleanExpression* right)
	: LogicalOperation(left, right)
{
}

bool Conjunction::eval(Table& table, size_t rowIdx) const
{

	return left->eval(table, rowIdx) && right->eval(table, rowIdx);
}

BooleanExpression* Conjunction::clone() const
{
	return new Conjunction(this->left->clone(), this->right->clone());
}

Disjunction::Disjunction(BooleanExpression* left, BooleanExpression* right)
	: LogicalOperation(left, right)
{
}

bool Disjunction::eval(Table& table, size_t rowIdx) const
{
	return left->eval(table, rowIdx) || right->eval(table, rowIdx);
}

BooleanExpression* Disjunction::clone() const
{
	return new Disjunction(this->left->clone(), this->right->clone());
}

void WhereExpressionHandler::copyFrom(const WhereExpressionHandler& other)
{
	expr = other.expr->clone();
}

void WhereExpressionHandler::moveFrom(WhereExpressionHandler&& other)
{
	expr = other.expr;
	other.expr = nullptr;
}

void WhereExpressionHandler::free()
{
	delete expr;
}

WhereExpressionHandler::WhereExpressionHandler(const String& str)
{
	expr = expressionFactory(str);
}

WhereExpressionHandler::WhereExpressionHandler(const WhereExpressionHandler& other)
{
	copyFrom(other);
}

WhereExpressionHandler& WhereExpressionHandler::operator=(const WhereExpressionHandler& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

WhereExpressionHandler::WhereExpressionHandler(WhereExpressionHandler&& other) noexcept
{
	moveFrom(std::move(other));
}

WhereExpressionHandler& WhereExpressionHandler::operator=(WhereExpressionHandler&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

WhereExpressionHandler::~WhereExpressionHandler()
{
	free();
}

//where ((field1)>(2))
//where (((field1)>(2))&((field1)<(4)))
//where ((field1)>(2))
//where ((field1)=(2))
BooleanExpression* expressionFactory(StringView str)
{
	str = str.substr(1, str.length() - 2); //remove the first and the last brackets

	unsigned count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
		else if (count == 0)
		{
			String colName;
			int value = 0;
			switch (str[i])
			{
			case '&': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			case '|': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			case '<':
				parseComparisonArgs(colName, value, str, i);
				return new LessThan(colName, value); break;

			case '>':
				parseComparisonArgs(colName, value, str, i);
				return new GreaterThan(colName, value); break;
			case '=':
				parseComparisonArgs(colName, value, str, i);
				return new Equals(colName, value); break;
			}
		}
	}
}

void parseComparisonArgs(String& colName, int& value, StringView& str, int strIdx)
{
	for (size_t j = 1; j < strIdx - 1; j++)
	{
		colName += str[j];
	}
	String valueStr;
	for (size_t j = strIdx + 2; j < str.length() - 1; j++)
	{
		valueStr += str[j];
	}
	value = DataUtils::intParse(valueStr.c_str());
}

