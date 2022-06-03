#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "arithmetic.h"
#include "command.h"
#include "boolexpression.h"

#include <iostream>
#include <vector>
#include <stack>
#include <map>

class Interpreter {
public:
    Interpreter(std::istream& in);
    ~Interpreter();

    void write(std::ostream& out);

    void execute(std::ostream& out); // Function that will execute the program after
                                     // it has been parsed

private:
	std::vector<Command*> commandArray; // To store all the commands

	std::map<std::string, int> intVariablesMap; // Map to store values of integer variables
	std::map<std::string, std::map<int, int>> arrayVariablesMap; // Map to store arrays of array variables

    void parse(std::istream& in);

    int findIndex(int lineNumber); // To find index of command on lineNumber line

    NumericExpression* parse_numeric_expression(std::string line, int& position); // Parses numeric expressions
    std::string parse_variable_name(std::string line, int position); // Parse variable names
    int parse_constant(std::string line, int position); // Parse constants
    BoolExpression* parse_boolean_expression(std::string line, int& position); // Parse boolean expression
};

#endif
