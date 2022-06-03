#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <map>

class NumericExpression {
public:
    virtual ~NumericExpression() {}

    virtual std::string format() const = 0;

    virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const = 0;

    virtual std::string getType() const = 0; // Used to get type of expression

    virtual std::string getName() const = 0; // Used to get name of variable (only for variable expressions)

    virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const = 0; // Used to get index of array variable expression

    virtual NumericExpression* getLeftExpression() const = 0; // Function to get left expression of division for error output

    virtual NumericExpression* getRightExpression() const = 0; // Function to get right expression of division for error output
};

class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();

    virtual std::string format() const;

    virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

    virtual std::string getType() const;

    virtual std::string getName() const;

    virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

    virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

class SubtractionExpression : public NumericExpression {
public:
	SubtractionExpression(NumericExpression* left, NumericExpression* right);
	~SubtractionExpression();

	virtual std::string format() const;

	virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual std::string getType() const;

	virtual std::string getName() const;

	virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

class DivisionExpression : public NumericExpression {
public:
	DivisionExpression(NumericExpression* left, NumericExpression* right);
	~DivisionExpression();

	virtual std::string format() const;

	virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual std::string getType() const;

	virtual std::string getName() const;

	virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

class MultiplicationExpression : public NumericExpression {
public:
	MultiplicationExpression(NumericExpression* left, NumericExpression* right);
	~MultiplicationExpression();

	virtual std::string format() const;

	virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual std::string getType() const;

	virtual std::string getName() const;

	virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
	NumericExpression* left;
	NumericExpression* right;
};

class ConstantExpression : public NumericExpression {
public:
	ConstantExpression(int val);
	~ConstantExpression();

	virtual std::string format() const;

	virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual std::string getType() const;

	virtual std::string getName() const;

	virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
	int value;
};

class VariableExpression : public NumericExpression {
public:
	// Index parameter will be null when it's an int
	// variable
	VariableExpression(std::string varName, bool intVar, NumericExpression* index);
	~VariableExpression();

	virtual std::string format() const;

	virtual int getValue (std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual std::string getType() const;

	virtual std::string getName() const;

	virtual int getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const;

	virtual NumericExpression* getLeftExpression() const;

    virtual NumericExpression* getRightExpression() const;

private:
	std::string name;
	bool intVar; // To check if it is an int variable or not
	NumericExpression* arrayIndex;
};

#endif