#ifndef BOOLEXPRESSION_HPP
#define BOOLEXPRESSION_HPP

#include "arithmetic.h"
#include <string>

class BoolExpression {
public:
	virtual ~BoolExpression() {}
    virtual std::string format() const = 0;
    virtual bool getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const = 0;
};

class EqualityExpression : public BoolExpression {
public:
	EqualityExpression(NumericExpression* left, NumericExpression* right);
	~EqualityExpression();

	virtual std::string format() const;

	virtual bool getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

class LessThanExpression : public BoolExpression {
public:
	LessThanExpression(NumericExpression* left, NumericExpression* right);
	~LessThanExpression();

	virtual std::string format() const;

	virtual bool getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

class GreaterThanExpression : public BoolExpression {
public:
	GreaterThanExpression(NumericExpression* left, NumericExpression* right);
	~GreaterThanExpression();

	virtual std::string format() const;

	virtual bool getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

#endif 
