#include "boolexpression.h"
#include <sstream>

using namespace std;

EqualityExpression::EqualityExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

EqualityExpression::~EqualityExpression() {
	delete this->left;
	delete this->right;
}

string EqualityExpression::format() const {
	return "[" + this->left->format() + " = " + this->right->format() + "]";
}

bool EqualityExpression::getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap)) == (right->getValue(intVariablesMap, arrayVariablesMap));
}



LessThanExpression::LessThanExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

LessThanExpression::~LessThanExpression() {
	delete this->left;
	delete this->right;
}

string LessThanExpression::format() const {
	return "[" + this->left->format() + " < " + this->right->format() + "]";
}

bool LessThanExpression::getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap)) < (right->getValue(intVariablesMap, arrayVariablesMap));
}



GreaterThanExpression::GreaterThanExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

GreaterThanExpression::~GreaterThanExpression() {
	delete this->left;
	delete this->right;
}

string GreaterThanExpression::format() const {
	return "[" + this->right->format() + " < " + this->left->format() + "]";
}

bool GreaterThanExpression::getValue(std::map<std::string, int>& intVariablesMap, 
    	std::map<std::string, std::map<int, int>>& arrayVariablesMap) const {
	return (left->getValue(intVariablesMap, arrayVariablesMap)) > (right->getValue(intVariablesMap, arrayVariablesMap));
}