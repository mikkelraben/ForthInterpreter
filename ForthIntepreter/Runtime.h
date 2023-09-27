#pragma once
#include "standardLibraries.h"
#include <cassert>

struct Node
{
	virtual ~Node() {};
};

struct StackVariable : Node
{
	bool isString = false;
};

struct StackString : public Node
{
	explicit StackString(std::string _string) : string(_string) {}
	std::string string;
};

struct StackNumber : public StackVariable
{
	explicit StackNumber(int _variable) : variable(_variable) {}
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
	void Evaluate();
};

struct Operation
{
	size_t numberOfInput;
	size_t numberOfOutput;
	std::function<std::vector<StackNumber> (std::vector<StackNumber>&, Runtime& runtime)> function;
	std::function<std::vector<StackNumber> (StackString, Runtime& runtime)> stringFunction;
	bool string;

	//normal operation
	Operation(const size_t& numberOfInput, const size_t& numberOfOutput, const std::function<std::vector<StackNumber>(std::vector<StackNumber>&, Runtime& runtime)>& function, bool string)
		: numberOfInput(numberOfInput), numberOfOutput(numberOfOutput), function(function), string(string)
	{
	}

	//for compatibility with strings
	Operation(const size_t& numberOfInput, const size_t& numberOfOutput, const std::function<std::vector<StackNumber>(StackString, Runtime& runtime)>& stringFunction, bool string)
		: numberOfInput(numberOfInput), numberOfOutput(numberOfOutput), stringFunction(stringFunction), string(string)
	{
	}
};

struct Operator : Node
{
	explicit Operator(Operation _operator) : op(_operator) {}
	Operation op;
};



