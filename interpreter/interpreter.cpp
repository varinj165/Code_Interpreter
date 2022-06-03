#include "interpreter.h"
#include <sstream>

using namespace std;

Interpreter::Interpreter(std::istream& in) {
    this->parse(in);
}

Interpreter::~Interpreter() {
	// Delete all allocated memory
	for (unsigned int i = 0; i < commandArray.size(); ++i) {
		delete commandArray[i];
	}
}

void Interpreter::parse(std::istream& in) {
    string line;
    while (getline(in, line)) {
    	int positionOfStream = 0;

        size_t line_number;
        stringstream stream(line);
        stream >> line_number;

        positionOfStream = line.find_first_not_of(to_string(line_number), positionOfStream); // Skip line number
        positionOfStream = line.find_first_not_of(" \n\r\t", positionOfStream); // Skip Whitespace

        string commandName;

        stream >> commandName;

        positionOfStream = line.find_first_not_of(commandName, positionOfStream); // Skip command name

        if (commandName == "PRINT") {
        	// Create substring of line cutting out line number and command name
        	string remainingLine = stream.str().substr(positionOfStream);
        	int pos = remainingLine.find_first_not_of(" \n\r\t"); // position skips all whitespace

        	NumericExpression* nexp1 = parse_numeric_expression(remainingLine, pos); // Parse numeric expression with the remaining line
        	                                                               // and store it
        	Command* newCommand = new PrintCommand(line_number, nexp1); // Create print command object

        	commandArray.push_back(newCommand); // Add command to parse tree
        } 

        else if (commandName == "LET") {
        	// Create substring of line cutting out line number and command name
        	string remainingLine = stream.str().substr(positionOfStream);
        	int pos = remainingLine.find_first_not_of(" \n\r\t"); // Position skips all whitespace

        	NumericExpression* variable = parse_numeric_expression(remainingLine, pos);

        	pos = remainingLine.find_first_not_of(" \n\r\t", pos); // Position skips all whitespace

        	NumericExpression* nexp2 = parse_numeric_expression(remainingLine, pos);

        	Command* newCommand = new LetCommand(line_number, variable, nexp2); // Create let command object

        	commandArray.push_back(newCommand);
        } 

        else if (commandName == "GOTO") {
        	// Create substring of line cutting out line number and command name
        	string remainingLine = stream.str().substr(positionOfStream);

        	stringstream ss(remainingLine); // Create stringstream from remaining line

        	int jLineVal; // To store value of jline

        	ss >> jLineVal; // Take in jline from command line

        	NumericExpression* jLine = new ConstantExpression(jLineVal); // Create constant expression for jLine

        	Command* newCommand = new GoToCommand(line_number, jLine);

        	commandArray.push_back(newCommand); // Add command to parse tree
        }

        else if (commandName == "IF") {
        	// Create substring of line cutting out line number and command name
        	string remainingLine = stream.str().substr(positionOfStream);
        	int pos = remainingLine.find_first_not_of(" \n\r\t"); // Position skips all whitespace

        	// Parse boolean expression
        	BoolExpression* bexp = parse_boolean_expression(remainingLine, pos); 

        	pos = remainingLine.find_first_not_of("THEN", pos); // Skip over THEN

        	pos = remainingLine.find_first_not_of(" \n\r\t", pos); // Position skips all whitespace

        	// Parse jLine
        	NumericExpression* jLine = parse_numeric_expression(remainingLine, pos);

        	Command* newCommand = new IfCommand(line_number, bexp, jLine);

        	commandArray.push_back(newCommand); // Add command to parse tree
        }

        else if (commandName == "GOSUB") {
        	// Create substring of line cutting out line number and command name
        	string remainingLine = stream.str().substr(positionOfStream);

        	stringstream ss(remainingLine); // Create stringstream from remaining line

        	int jLineVal; // To store value of jline

        	ss >> jLineVal; // Take in jline from command line

        	NumericExpression* jLine = new ConstantExpression(jLineVal); // Create constant expression for jLine

        	Command* newCommand = new GoSubCommand(line_number, jLine);

        	commandArray.push_back(newCommand); // Add command to parse tree
        }

        else if (commandName == "RETURN") {
        	Command* newCommand = new ReturnCommand(line_number); // Create Return command
        	commandArray.push_back(newCommand); // Add command to parse tree
        }

        else { // END
        	Command* newCommand = new EndCommand(line_number); // Create End command
        	commandArray.push_back(newCommand); // Add command to parse tree
        }
    }
}

void Interpreter::execute(std::ostream& out) {
	// Stack to remember line number for GOSUB
	stack <int> goSubStack;

	int index = 0; // To iterate through commandArray

	// Will break loop when execution finishes
	// or the program needs to be terminated
	while (true) {
		// If there is no end command terminate program
		// after last line executes
		if (index >= (int) commandArray.size()) {
			break; // Terminate program
		}

		string commandName = (commandArray[index])->getCommandName();

		if (commandName == "PRINT") {
			// Execute print command
			int errorVal = commandArray[index]->executeCommand(intVariablesMap, arrayVariablesMap, out);

			// If division by 0 error has occured 
			if (errorVal == 0) {
				break; // Terminate program
			}

			++index; // Go to next command
		}

		else if (commandName == "LET") {
			// Execute let command
			int errorVal = commandArray[index]->executeCommand(intVariablesMap, arrayVariablesMap, out);

			// If division by 0 error has occured 
			if (errorVal == 0) {
				break; // Terminate program
			}

			++index; // Go to next command
		}

		else if (commandName == "GOTO") {
			Command* currCommand = commandArray[index];

			// Store line number to jump to
			int lineToJumpTo = currCommand->executeCommand(intVariablesMap, arrayVariablesMap, out);

			// Find index of line to jump to and update index
			index = findIndex(lineToJumpTo);

			// If line does not exist
			if (index == -1) {
				// Output error
				out << "Error in line " << currCommand->getLineNum() << 
				": GOTO to non-existent line " << lineToJumpTo << "." << endl;

				break; // Terminate program
			}

		}

		else if (commandName == "IF") {
			Command* currCommand = commandArray[index];

			int lineToJumpTo = currCommand->executeCommand(intVariablesMap, arrayVariablesMap, out);

			// If bool exp has evaluated to true
			if (lineToJumpTo != -1) {
				// Find and update index of command with line number lineToJumpTo
				index = findIndex(lineToJumpTo);

				// If line does not exist
				if (index == -1) {
					out << "Error in line " << currCommand->getLineNum() <<
					": IF jump to non-existent line " << lineToJumpTo << "." << endl;

					break; // Terminate program;
				}

				// If execution reaches here, it automatically jumps to line jLine
			}

			else {
				++index; // Go to next command
			}
		}

		else if (commandName == "GOSUB") {
			Command* currCommand = commandArray[index];

			// Get line to jump to
			int lineToJumpTo = currCommand->executeCommand(intVariablesMap, arrayVariablesMap, out);

			// Remembers where the command is jumping from
			goSubStack.push(index + 1); // Store index of line after GoSub command on stack

			// Find and update index for lineToJumpTo
			index = findIndex(lineToJumpTo);

			// If line does not exist
			if (index == -1) {
				out << "Error in line " << currCommand->getLineNum() <<
					": GOSUB to non-existent line " << lineToJumpTo << "." << endl;

				break; // Terminate program
			}

			// If execution reaches here, it automatically jumps to line jLine
		}

		else if (commandName == "RETURN") {
			Command* currCommand = commandArray[index];

			// If there is no matching GOSUB call
			if (goSubStack.empty()) {
				out << "Error in Line " << currCommand->getLineNum() << 
				": No matching GOSUB for RETURN." << endl;

				break; // Terminate program
			}

			else {
				// Get index of line to jump back to
				index = goSubStack.top();

				goSubStack.pop(); // Remove line from stack

				// If program is over after return
				if (index >= (int) commandArray.size()) {
					break; // Terminate program
				}
			}
		}

		else if (commandName == "END") {
			break; // Terminate program
		}
	}
}

int Interpreter::findIndex(int lineNumber) {
	int index = -1; // Returns -1 if index is not found
	for (unsigned int i = 0; i < commandArray.size(); ++i) {
		if (commandArray[i]->getLineNum() == lineNumber) {
			// Once index is found break out of loop
			index = i;
			break;
		}
	}

	return index;
}

void Interpreter::write(std::ostream& out) {
	// Call all command's format functions and print
	for (unsigned int i = 0; i < commandArray.size(); ++i) {
		out << commandArray[i]->format();
		out << endl;
	}
}

NumericExpression* Interpreter::parse_numeric_expression(string line, int& position) {
	if (line[position] == '-' || isdigit(line[position])) { // If the nexp is a constant
		bool isNegative = false; // To check if value is negative or not

		if (line[position] == '-') { // If it is a negative int
			++position; // Skip over '-'
			isNegative = true;
		}

		int value = parse_constant(line, position);

		position = line.find_first_not_of(to_string(value), position); // Update position

		if (isNegative) {
			value = value - (value * 2); // Make the value negative
		}

		return new ConstantExpression(value);
	}

	else if (isalpha(line[position])) { // If the first character is a letter
		string name = parse_variable_name(line, position);

		position = line.find_first_not_of(name, position); // Update pos to index after the name

		position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

		if (line[position] != '[') { // If it is just an int variable
			return new VariableExpression(name, true, nullptr);
		} 

		else { // If it is an array variable
			++position; // Skip over '['
			position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

			NumericExpression* index = parse_numeric_expression(line, position);

			position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

			++position; // Skip over ']'

			return new VariableExpression(name, false, index);
		}
	}

	else if (line[position] == '(') { // Binary operator
		++position; // Skip over '('
		position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

		NumericExpression* left = parse_numeric_expression(line, position);

		position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

		char binaryOperator = line[position]; // Store the operator

		++position; // Skip over binary operator

		position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

		NumericExpression* right = parse_numeric_expression(line, position);

		position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

		++position; // Skip over ')'

		// Check which operator it is and return object
		// of that type
		if (binaryOperator == '+') {
			return new AdditionExpression(left, right);
		}

		else if (binaryOperator == '-') {
			return new SubtractionExpression(left, right);
		}

		else if (binaryOperator == '/') {
			return new DivisionExpression(left, right);
		}

		else if (binaryOperator == '*') {
			return new MultiplicationExpression(left, right);
		}
	}

	else { 
		return nullptr; // To remove warning (control reaches
		                // end of non void function)
	}
}

string Interpreter::parse_variable_name(string line, int position) {
	string remainingLine = line.substr(position, line.size()); // Store remaining line with variable name in the start

	stringstream ss(remainingLine);

	string name;

	ss >> name;

	int badInputIndex = -1; // To store starting index of any extra input taking into name

	for (size_t i = 0; i < name.size(); ++i) {
		if (!isalpha(name[i])) { // If there is an operator consumed into name
			badInputIndex = i;
			break;
		}
	}

	if (badInputIndex != -1) { // If there is extra input in name
		name = name.substr(0, badInputIndex); // Cut it out

		return name;
	} 

	else {
		return name; // Return name of variable
	}
}

int Interpreter::parse_constant(string line, int position) {
	string remainingLine = line.substr(position, line.size()); // Store remaining line with variable name in the start
	stringstream ss(remainingLine);

	int value;

	ss >> value;

	return value; // Return name of variable
}

BoolExpression* Interpreter::parse_boolean_expression(string line, int& position) {
	NumericExpression* left = parse_numeric_expression(line, position); // Parse the left numeric expression

	position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

	char compareOperator = line[position]; // Store the operator

	++position; // Skip over operator

	position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

	NumericExpression* right = parse_numeric_expression(line, position); // Parse the right numeric expression

	position = line.find_first_not_of(" \n\r\t", position); // Trim whitespace

	if (compareOperator == '=') {
		return new EqualityExpression(left, right);
	}

	else if (compareOperator == '>') {
		return new GreaterThanExpression(left, right);
	}

	else { // Less than ('<')
		return new LessThanExpression(left, right);
	}
}