#pragma once
#include "standardLibraries.h"
#include <cassert>

enum class OperationType
{
	normal,
	printString,
	string,
	If,
	Then,
	Else,
};

struct Node
{
	virtual ~Node() {};
	OperationType special;
};

struct StackVariable : Node
{
	bool isString = false;
};

struct StackString : public Node
{
	explicit StackString(std::string _string) : string(_string)
	{
		special = OperationType::normal;
	}
	std::string string;
};

struct StackNumber : public StackVariable
{
	explicit StackNumber(int _variable) : variable(_variable) 
	{
		special = OperationType::normal;
	}
	int variable;
};

class UserInterface;

//Holds information about the stack, variables, loops and I/O
class Runtime
{
public:
	void AddOrder(std::shared_ptr<Node> node);
	std::stack<StackNumber> stack;
	std::shared_ptr<UserInterface> userInterface;
	std::vector<std::shared_ptr<Node>> orders;
	size_t currentOrder;
	void Evaluate();
};



struct Operation
{
	size_t numberOfInput;
	size_t numberOfOutput;
	std::function<std::vector<StackNumber> (std::vector<StackNumber>&, Runtime& runtime)> function;
	std::function<std::vector<StackNumber> (StackString, Runtime& runtime)> stringFunction;
	OperationType special;
	bool insideDefinition = false;

	//normal operation
	Operation(const size_t& numberOfInput, const size_t& numberOfOutput, const std::function<std::vector<StackNumber>(std::vector<StackNumber>&, Runtime& runtime)>& function, OperationType special)
		: numberOfInput(numberOfInput), numberOfOutput(numberOfOutput), function(function), special(special)
	{
	}

	//for compatibility with strings
	Operation(const size_t& numberOfInput, const size_t& numberOfOutput, const std::function<std::vector<StackNumber>(StackString, Runtime& runtime)>& stringFunction, OperationType special)
		: numberOfInput(numberOfInput), numberOfOutput(numberOfOutput), stringFunction(stringFunction), special(special)
	{
	}
};

struct Operator : Node
{
	explicit Operator(const Operation& _operator) : op(_operator) { special = op.special; }
	Operation op;
};



