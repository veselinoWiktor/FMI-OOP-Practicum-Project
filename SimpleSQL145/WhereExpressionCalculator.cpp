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
	//TODO decide how to effectively eval
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
	//TODO decide how to effectively eval
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
	//TODO decide how to effectively eval
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
