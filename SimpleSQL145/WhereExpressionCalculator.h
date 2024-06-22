#pragma once
#include "Utils.h"
#include "String.h"
#include "StringView.h"
#include "Table.h"
#include <sstream>

struct BooleanExpression
{
	BooleanExpression() = default;
	BooleanExpression(const BooleanExpression&) = delete; // deletes move ctor
	BooleanExpression& operator=(const BooleanExpression&) = delete; // deletes move op=

	virtual bool eval(Table& table, size_t rowIdx) const = 0;
	virtual ~BooleanExpression() = default;
	virtual BooleanExpression* clone() const = 0;
};

struct ComparisonOperation : public BooleanExpression
{
protected:
	String columnName;
	int value;
public:
	ComparisonOperation(const String& columnName, int value);
};

struct LessThan : public ComparisonOperation
{
	LessThan(const String& columnName, int value);

	bool eval(Table& table, size_t rowIdx) const override;
	BooleanExpression* clone() const override;
};

struct GreaterThan : public ComparisonOperation
{
	GreaterThan(const String& columnName, int value);

	bool eval(Table& table, size_t rowIdx) const override;
	BooleanExpression* clone() const override;
};

struct Equals : public ComparisonOperation
{
	Equals(const String& columnName, int value);

	bool eval(Table& table, size_t rowIdx) const override;
	BooleanExpression* clone() const override;
};

struct LogicalOperation : public BooleanExpression
{
protected:
	BooleanExpression* left;
	BooleanExpression* right;
public:
	LogicalOperation(BooleanExpression* left, BooleanExpression* right);
	~LogicalOperation();
};

struct Conjunction : public LogicalOperation
{
	Conjunction(BooleanExpression* left, BooleanExpression* right);

	bool eval(Table& table, size_t rowIdx) const override;
	BooleanExpression* clone() const override;
};

struct Disjunction : public LogicalOperation
{
	Disjunction(BooleanExpression* left, BooleanExpression* right);

	bool eval(Table& table, size_t rowIdx) const override;
	BooleanExpression* clone() const override;
};


//where (field1 > 2);
//where ((field1 > 2) and (field1 < 4));
//where (field1 > 2);
//where (field1 = 2);
BooleanExpression* expressionFactory(StringView str)
{
}

class WhereExpressionHandler
{
private:
	BooleanExpression* expr = nullptr;

	void copyFrom(const WhereExpressionHandler& other);
	void moveFrom(WhereExpressionHandler&& other);
	void free();

public:
	WhereExpressionHandler(const String& str);
	WhereExpressionHandler(const WhereExpressionHandler& other);
	WhereExpressionHandler& operator=(const WhereExpressionHandler& other);
	WhereExpressionHandler(WhereExpressionHandler&& other) noexcept;
	WhereExpressionHandler& operator=(WhereExpressionHandler&& other) noexcept;
	~WhereExpressionHandler();

	bool evaluate(Table& table, size_t rowIdx) const
	{
		return expr->eval(table, rowIdx);
	}
};

