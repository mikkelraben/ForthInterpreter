#pragma once
#include "Runtime.h"

class Tokenizer
{
    Runtime& runtime;
public:
    Function parseInput(std::string_view input);

    explicit Tokenizer(Runtime& _runtime)
        : runtime(_runtime)
    {
    }
};

