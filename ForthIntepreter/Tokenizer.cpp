#include "Tokenizer.h"
#include "Operations.h"
#include <string_view>
#include <format>
#include <sstream>

class Operators
{
public:
    const static inline std::unordered_map <std::string, Operation> reservedOperations = {
        //Basic Arithmetic
        {"+", Operation(2, 1, Operations::Add, OperationType::normal)},
        {"-", Operation(2, 1, Operations::Subtract, OperationType::normal)},
        {"*", Operation(2, 1, Operations::Multiply, OperationType::normal)},
        {"/", Operation(2, 1, Operations::Divide, OperationType::normal)},

        //Boolean Logic
        {"=", Operation(2, 1, Operations::Equal, OperationType::normal)},
        {"<", Operation(2, 1, Operations::LessThan, OperationType::normal)},
        {">", Operation(2, 1, Operations::LargerThan, OperationType::normal)},
        {"AND", Operation(2, 1, Operations::And, OperationType::normal)},
        {"OR", Operation(2, 1, Operations::Or, OperationType::normal)},
        {"NOT", Operation(1, 1, Operations::Not, OperationType::normal)},

        //Stack Manipulation

        {"DUP", Operation(1, 2, Operations::Duplicate, OperationType::normal)},
        {"DROP", Operation(1, 0, Operations::Drop, OperationType::normal)},
        {"SWAP", Operation(2, 2, Operations::Swap, OperationType::normal)},
        {"OVER", Operation(2, 3, Operations::Over, OperationType::normal)},
        {"ROT", Operation(3, 3, Operations::Rotate, OperationType::normal)},

        {".", Operation(1, 0, Operations::PrintStackNumber, OperationType::normal)},
        {"EMIT", Operation(1, 0, Operations::PrintAscii, OperationType::normal)},
        {"CR", Operation(0, 0, Operations::PrintCarriageReturn, OperationType::normal)},
        {".\"", Operation(0, 0, Operations::PrintString, OperationType::printString)},

        //Conditional Operations
        {"IF", Operation(1, 0, Operations::If, OperationType::If)},
        {"THEN", Operation(0, 0, Operations::NOP, OperationType::Then)},
        {"ELSE", Operation(0, 0, Operations::Else, OperationType::Else)},


        {"DO", Operation(2, 0, Operations::Do, OperationType::Do)},
        //?DO
        {"?DO", Operation(2, 0, Operations::qDo, OperationType::Do)},
        {"LOOP", Operation(0, 0, Operations::Loop, OperationType::Loop)},
        {"I", Operation(0, 1, Operations::I, OperationType::I)},

        {"BEGIN", Operation(0, 0, Operations::Begin, OperationType::Begin)},
        {"WHILE", Operation(1, 0, Operations::While, OperationType::While)},
        {"REPEAT", Operation(0, 0, Operations::Repeat, OperationType::Repeat)},

        {";", Operation(0, 0, Operations::NOP, OperationType::FunctionEnd)},

        //{"CallFunction", 

    };

    const static inline auto FunctionDefinition = Operation(0, 0, Operations::BeginDefinition, OperationType::FunctionBegin);
    const static inline auto CallFunction = Operation(0, 0, Operations::CallFunction, OperationType::CallFunction);
};

enum class TokenTypes
{
    Normal,
    String,
    FunctionDefinition
};

struct Token
{
    std::string token;
    TokenTypes type;
};

void Tokenize(std::string_view& input, std::vector<Token>& tokens)
{
    std::stringstream line(input.data());
    std::string token;

    while (std::getline(line, token, ' '))
    {
        //if the token is a string
        if (token == ".\"")
        {
            std::getline(line, token, '\"');
            tokens.emplace_back(token, TokenTypes::String);
        }
        else if (token == ":")
        {
            std::getline(line, token, ' ');
            tokens.emplace_back(token, TokenTypes::FunctionDefinition);
        }
        else
        {
            tokens.emplace_back(token, TokenTypes::Normal);
        }
    }
}

//Returns a function with name main
Function Tokenizer::parseInput(std::string_view input)
{
    std::vector<std::shared_ptr<Node>> orders;

    std::vector<Token> tokens;

    std::vector<std::string> justTokenizedFunctions;

    Tokenize(input, tokens);

    for (const auto& token : tokens)
    {
        if (token.token.empty())
        {
            continue;
        }

        switch (token.type)
        {
        case TokenTypes::String:
            orders.emplace_back(std::make_shared<Operator>(Operators::reservedOperations.at(".\"")));
            orders.emplace_back(std::make_shared<StackString>(token.token));
            break;
        case TokenTypes::FunctionDefinition:
            orders.emplace_back(std::make_shared<Operator>(Operators::FunctionDefinition));
            orders.emplace_back(std::make_shared<StackString>(token.token));
            justTokenizedFunctions.emplace_back(token.token);
            break;

        case TokenTypes::Normal:
            //first assume there is a valid operation
            bool tokenParsed = false;
            for (const auto& operation : Operators::reservedOperations)
            {
                if (operation.first == token.token)
                {
                    orders.emplace_back(std::make_shared<Operator>(operation.second));
                    tokenParsed = true;
                }
            }
            if (tokenParsed)
            {
                break;
            }



            //then if operation not found assume it is a function

            bool found = std::ranges::find(justTokenizedFunctions, token.token) != justTokenizedFunctions.end();
            found |= runtime.storage.functions.contains(token.token);
            if (found)
            {
                orders.emplace_back(std::make_shared<Operator>(Operators::CallFunction));
                orders.emplace_back(std::make_shared<StackString>(token.token));
                break;
            }


            //if not a function try a variable


            //try converting to a number
            try
            {
                int number = std::stoi(token.token);
                tokenParsed = true;
                orders.emplace_back(std::make_shared<StackNumber>(number));
            }
            //If all fails error
            catch (const std::invalid_argument& error)
            {
                auto position = input.find(token.token);
                throw ParseError(token.token, position, position + token.token.length());
            }
            break;
        }
    }

    // TODO: insert return statement here

    return Function{ "main", orders };
}
