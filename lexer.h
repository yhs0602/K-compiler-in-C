//
// Created by 양현서 on 2021/04/12.
//

#ifndef K_COMPILER_IN_C_LEXER_H
#define K_COMPILER_IN_C_LEXER_H

#include <string>

class Lexer {
public:
    Lexer(std::string buf);

private:
    std::string _buf;
};


#endif //K_COMPILER_IN_C_LEXER_H
