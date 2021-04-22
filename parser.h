//
// Created by 양현서 on 2021/04/22.
//

#ifndef KCOMPILERINC_PARSER_H
#define KCOMPILERINC_PARSER_H


#include <utility>
#include <vector>
#include "lexer.h"

class Parser {
public:
    Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {}

    void parse();

private:
    std::vector<Token> _tokens;
};


#endif //KCOMPILERINC_PARSER_H
