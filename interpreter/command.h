#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "arithmetic.h"
#include "boolexpression.h"
#include <string>
#include <iostream>
#include <stdexcept>

class Command {
public:
	virtual ~Command() {}
    virtual std::string format() const = 0;

    virtual int getLineNum() const = 0;

    virtual std::string getCommandName() const = 0;

    virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const = 0;
    // The int return type is to return line numbers for goto and gosub

protected:
	int lineNum; // To store line number of command
};

class PrintCommand : public Command {
public:
	PrintCommand(int line, NumericExpression* toPrint);
	~PrintCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;

private:
	NumericExpression* toPrint; // Numeric Expression which needs to be printed 
};

class LetCommand : public Command {
public:
	LetCommand(int line, NumericExpression* var, NumericExpression* toStore);
	~LetCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;

private:
	NumericExpression* variable; // Variable to store into
	NumericExpression* valStore; // Value to store
};

class GoToCommand : public Command {
public:
	GoToCommand(int line, NumericExpression* jLine);
	~GoToCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;

private:
	NumericExpression* jLine; // Line to go to
};

class IfCommand : public Command {
public:
	IfCommand(int line, BoolExpression* boolExp, NumericExpression* jLine);
	~IfCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;

private:
	BoolExpression* boolExp;
	NumericExpression* jLine; // Line to go to
};

class GoSubCommand : public Command {
public:
	GoSubCommand(int line, NumericExpression* jLine);
	~GoSubCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;

private:
	NumericExpression* jLine; // Line to go to
};

class ReturnCommand : public Command {
public:
	ReturnCommand(int line);
	~ReturnCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;
};

class EndCommand : public Command {
public:
	EndCommand(int line);
	~EndCommand();

	virtual std::string format() const;

	virtual int getLineNum() const;

	virtual std::string getCommandName() const;

	virtual int executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const;
};

#endif
