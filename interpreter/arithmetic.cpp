#include "arithmetic.h"
#include <sstream>

using namespace std;

// Addition class

AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

AdditionExpression::~AdditionExpression() {
	// Delete relevant data
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

int AdditionExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap) + right->getValue(intVariablesMap, arrayVariablesMap));
}

std::string AdditionExpression::getType() const {
	return "ADD";
}

std::string AdditionExpression::getName() const {
	return "";
}

int AdditionExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return -1;
}

NumericExpression* AdditionExpression::getLeftExpression() const {
	return nullptr;
}

NumericExpression* AdditionExpression::getRightExpression() const {
	return nullptr;
}

// Subtraction class

SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

SubtractionExpression::~SubtractionExpression() {
	// Delete relevant data
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}

int SubtractionExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap) - right->getValue(intVariablesMap, arrayVariablesMap));
}

std::string SubtractionExpression::getType() const {
	return "SUBTRACT";
}

std::string SubtractionExpression::getName() const {
	return "";
}

int SubtractionExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return -1;
}

NumericExpression* SubtractionExpression::getLeftExpression() const {
	return nullptr;
}

NumericExpression* SubtractionExpression::getRightExpression() const {
	return nullptr;
}

// Division

DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

DivisionExpression::~DivisionExpression() {
	// Delete relevant data
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}

int DivisionExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {

	if (right->getValue(intVariablesMap, arrayVariablesMap) == 0) {
		throw runtime_error("Division by 0");
	}

	return (left->getValue(intVariablesMap, arrayVariablesMap) / right->getValue(intVariablesMap, arrayVariablesMap));
}

std::string DivisionExpression::getType() const {
	return "DIVIDE";
}

std::string DivisionExpression::getName() const {
	return "";
}

int DivisionExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return -1;
}

NumericExpression* DivisionExpression::getLeftExpression() const {
	return left;
}

NumericExpression* DivisionExpression::getRightExpression() const {
	return right;
}

// Multiplication

MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

MultiplicationExpression::~MultiplicationExpression() {
	// Delete relevant data
    delete this->left;
    delete this->right;
}

string MultiplicationExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}

int MultiplicationExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap) * right->getValue(intVariablesMap, arrayVariablesMap));
}

std::string MultiplicationExpression::getType() const {
	return "MULTIPLY";
}

std::string MultiplicationExpression::getName() const {
	return "";
}

int MultiplicationExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return -1;
}

NumericExpression* MultiplicationExpression::getLeftExpression() const {
	return nullptr;
}

NumericExpression* MultiplicationExpression::getRightExpression() const {
	return nullptr;
}

// Constants

ConstantExpression::ConstantExpression(int val) : value(val) {

}

ConstantExpression::~ConstantExpression() {

}

string ConstantExpression::format() const {
	stringstream ss;
	ss << this->value;

	return ss.str();
}

int ConstantExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {
	return value;
}

std::string ConstantExpression::getType() const {
	return "CONSTANT";
}

std::string ConstantExpression::getName() const {
	return "";
}

int ConstantExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return -1;
}

NumericExpression* ConstantExpression::getLeftExpression() const {
	return nullptr;
}

NumericExpression* ConstantExpression::getRightExpression() const {
	return nullptr;
}

// Variables

VariableExpression::VariableExpression(string varName, bool intVar, NumericExpression* index) : name(varName), intVar(intVar), arrayIndex(index){
	
}

VariableExpression::~VariableExpression() {
	// Delete relevant data
	if (!intVar) {
		delete this->arrayIndex;
	}
}

string VariableExpression::format() const {
	if (!intVar) { // If it's an array variable
		stringstream ss;
		ss << this->name << "[";
		ss << this->arrayIndex->format();
		ss << "]";
		return ss.str();
	} else { // If it's an int variable
		stringstream ss;
		ss << this->name;
		return ss.str();
	}
}

int VariableExpression::getValue(map<string, int>& intVariablesMap, 
    	map<string, map<int, int>>& arrayVariablesMap) const {
	if (intVar) { // If it is an integer variable
		return intVariablesMap[name];
	} 

	else { // If it is an array variable
		// Get value of index expression
		int index = arrayIndex->getValue(intVariablesMap, arrayVariablesMap);

		return arrayVariablesMap[name][index];
	}
}

std::string VariableExpression::getType() const {
	if (intVar) {
		return "INT";
	}

	else {
		return "ARRAY";
	}
}

std::string VariableExpression::getName() const {
	return name;
}

int VariableExpression::getIndex(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	int index = arrayIndex->getValue(intVariablesMap, arrayVariablesMap);

	return index;
}

NumericExpression* VariableExpression::getLeftExpression() const {
	return nullptr;
}

NumericExpression* VariableExpression::getRightExpression() const {
	return nullptr;
}