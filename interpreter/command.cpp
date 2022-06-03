#include "command.h"

#include <sstream>

using namespace std;

// PRINT

PrintCommand::PrintCommand(int line, NumericExpression* toPrint) : toPrint(toPrint) {
	this->lineNum = line;
}

PrintCommand::~PrintCommand () {
	delete this->toPrint;
}

string PrintCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " PRINT " << this->toPrint->format();
	return ss.str();
}

int PrintCommand::getLineNum() const {
	return this->lineNum;
}

string PrintCommand::getCommandName() const {
	return "PRINT";
}

int PrintCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	try {
		int value = toPrint->getValue(intVariablesMap, arrayVariablesMap);
		out << value << endl;
	}

	// If exception is caught that means there is division by 0
	catch (exception& error) {
		NumericExpression* left = toPrint->getLeftExpression();
		NumericExpression* right = toPrint->getRightExpression();

		out << "Error in Line " << this->lineNum << ": Division by 0: " << 
		left->format() << " = " << left->getValue(intVariablesMap, arrayVariablesMap) << 
		", " << right->format() << " = " << right->getValue(intVariablesMap, arrayVariablesMap) << "." << endl;

		return 0; // If the function returns 0 then program will terminate
		          // (Handled in interpreter.cpp)
	}

	return -1; // Don't need to use return value for this command
}

// LET

LetCommand::LetCommand(int line, NumericExpression* var, NumericExpression* toStore) : variable(var), valStore(toStore) {
	this->lineNum = line;
}

LetCommand::~LetCommand() {
	delete this->variable;
	delete this->valStore;
}

string LetCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " LET " << this->variable->format() << " " << this->valStore->format();
	return ss.str();
}

int LetCommand::getLineNum() const {
	return this->lineNum;
}

string LetCommand::getCommandName() const {
	return "LET";
}

int LetCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	try {
		int value = valStore->getValue(intVariablesMap, arrayVariablesMap); // Get value to store

		// Get type and name of variable
		string type = variable->getType();

		string name = variable->getName();

		if (type == "INT") {
			// If a key of name does not exist, this creates it,
			// else it replaces the value
			intVariablesMap[name] = value;
		}

		else if (type == "ARRAY") {
			int index = variable->getIndex(intVariablesMap, arrayVariablesMap);

			map<string, map<int, int>>::iterator it; // To store return value of find function

			it = arrayVariablesMap.find(name);

			// If array already exists
			if (it != arrayVariablesMap.end()) {
				(arrayVariablesMap.at(name))[index] = value;
			}

			// If this is a new array being declared
			else {
				map<int, int> myArray; // Create new array for new variable

				myArray[index] = value; // Add value to array at index

				arrayVariablesMap[name] = myArray; // Add array to map
			}
		}
	}

	// If exception is caught that means there is division by 0
	catch (exception& error) {
		NumericExpression* left = valStore->getLeftExpression();
		NumericExpression* right = valStore->getRightExpression();

		out << "Error in Line " << this->lineNum << ": Division by 0: " << 
		left->format() << " = " << left->getValue(intVariablesMap, arrayVariablesMap) << 
		", " << right->format() << " = " << right->getValue(intVariablesMap, arrayVariablesMap) << "." << endl;

		return 0; // If the function returns 0 then program will terminate
		          // (Handled in interpreter.cpp)
	}

	return -1; // Don't need to use return value for this command
}

// GOTO

GoToCommand::GoToCommand(int line, NumericExpression* jLine) : jLine(jLine) {
	this->lineNum = line;
}

GoToCommand::~GoToCommand() {
	delete this->jLine;
}

string GoToCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " GOTO <" << this->jLine->format() << ">";
	return ss.str();
}

int GoToCommand::getLineNum() const {
	return this->lineNum;
}

string GoToCommand::getCommandName() const {
	return "GOTO";
}

int GoToCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	int line = jLine->getValue(intVariablesMap, arrayVariablesMap); // Get line to jump to

	// (Jumping is handled in interpreter.cpp's execute function)
	return line; // Return line to jump to
}

// IF

IfCommand::IfCommand(int line, BoolExpression* boolExp, NumericExpression* jLine) : boolExp(boolExp), jLine(jLine) {
	this->lineNum = line;
}

IfCommand::~IfCommand() {
	delete this->boolExp;
	delete this->jLine;
}

string IfCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " IF " << this->boolExp->format() << " THEN <" << this->jLine->format() << ">";
	return ss.str();
}

int IfCommand::getLineNum() const {
	return this->lineNum;
}

string IfCommand::getCommandName() const {
	return "IF";
}

int IfCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	bool isTrue = boolExp->getValue(intVariablesMap, arrayVariablesMap); // Evaluate boolean expression

	// If bool exp evaluates to true then 
	// jump to line
	if (isTrue) {
		int line = jLine->getValue(intVariablesMap, arrayVariablesMap);

		return line;
	}

	else {
		return -1; // Return -1 if boolExp is false
	}
}

// GOSUB

GoSubCommand::GoSubCommand(int line, NumericExpression* jLine) : jLine(jLine) {
	this->lineNum = line;
}

GoSubCommand::~GoSubCommand() {
	delete this->jLine;
}

string GoSubCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " GOSUB <" << this->jLine->format() << ">";
	return ss.str();
}

int GoSubCommand::getLineNum() const {
	return this->lineNum;
}

string GoSubCommand::getCommandName() const {
	return "GOSUB";
}

int GoSubCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	int line = jLine->getValue(intVariablesMap, arrayVariablesMap); // Get line to jump to

	// (Jumping is handled in interpreter.cpp's execute function)
	return line; // Return line to jump to
}

// RETURN

ReturnCommand::ReturnCommand(int line) {
	this->lineNum = line;
}

ReturnCommand::~ReturnCommand() {

}

string ReturnCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " RETURN";
	return ss.str();
}

int ReturnCommand::getLineNum() const {
	return this->lineNum;
}

string ReturnCommand::getCommandName() const {
	return "RETURN";
}

int ReturnCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	return -1; // Don't need to use return value for this command
}

// END

EndCommand::EndCommand(int line) {
	this->lineNum = line;
}

EndCommand::~EndCommand() {

}

string EndCommand::format() const {
	stringstream ss;
	ss << this->lineNum << " END";
	return ss.str();
}

int EndCommand::getLineNum() const {
	return this->lineNum;
}

string EndCommand::getCommandName() const {
	return "END";
}

int EndCommand::executeCommand(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap, std::ostream& out) const {

	return -1; // Don't need to use return value for this command
}