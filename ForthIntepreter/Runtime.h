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
    Do,
    Loop,
    I,
    Begin,
    While,
    Repeat,
    CallFunction,
    FunctionBegin,
    FunctionEnd,
};


// I could use a union but it is considered bad practice
// should be replaced with some polymorphic thing
struct ExtraInfo
{
    size_t stringLocation = -1;
    size_t startLocation = -1;
    size_t endLocation = -1;
    size_t elseLocation = -1;
    size_t whileLocation = -1;
    int loopStartingValue = 0;
    int loopEndValue = 0;
    int loopIteration = 0;
};

struct Node
{
    virtual ~Node() {};
    OperationType special;
    std::shared_ptr<ExtraInfo> info;
    bool validated = false;
};

struct StackVariable : Node
{
    bool isString = false;
};

struct StackString : public StackVariable
{
    explicit StackString(std::string const& _string) : string(_string)
    {
        special = OperationType::string;
        isString = true;
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

class Function
{
public:
    std::string functionName;
    std::vector<std::shared_ptr<Node>> orders;
    size_t currentOrder = 0;

    Function(const std::string& functionName, const std::vector<std::shared_ptr<Node>>& orders)
        : functionName(functionName), orders(orders)
    {

    }
};

class RuntimeStorage
{
public:
    std::unordered_map<std::string, std::shared_ptr<Function>> functions;
    //variables
};

class UserInterface;

//Holds information about the stack, variables, loops and I/O
class Runtime
{
public:
    void AddOrder(std::shared_ptr<Node> node);
    std::stack<StackNumber> stack;
    std::shared_ptr<UserInterface> userInterface;
    std::stack<std::shared_ptr<Function>> callStack;
    RuntimeStorage storage;

    std::shared_ptr<Function> currentFunction();
    size_t& currentOrder();
    std::vector<std::shared_ptr<Node>>& orders();

    void addMaintoCallStack();
    void addFunctionToCallStack(std::shared_ptr<Function>);
    void popFunctionFromCallStack();
    void Evaluate();
private:
    void RunOrders();
    void ValidateOrders();
    void addDefinitions();
};



struct Operation
{
    size_t numberOfInput;
    size_t numberOfOutput;
    std::function<std::vector<StackNumber>(std::vector<StackNumber>&, Runtime& runtime)> function;
    OperationType special;
    bool insideDefinition = false;

    //normal operation
    Operation(const size_t& numberOfInput, const size_t& numberOfOutput, const std::function<std::vector<StackNumber>(std::vector<StackNumber>&, Runtime& runtime)>& function, OperationType special)
        : numberOfInput(numberOfInput), numberOfOutput(numberOfOutput), function(function), special(special)
    {
    }
};

struct Operator : Node
{
    explicit Operator(const Operation& _operator) : op(_operator)
    {
        special = op.special;
    }
    Operation op;
};



