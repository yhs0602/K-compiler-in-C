//
// Created by 양현서 on 2021/04/12.
//

#ifndef K_COMPILER_IN_C_LEXER_H
#define K_COMPILER_IN_C_LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <utility>

class Token {
public:
    enum Type {
        ID,
        NUM,
        OP
    };

    Token(std::string raw, Type type) : raw(std::move(raw)), type(type) {}

    std::string get_raw();

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
    Type type;
    std::string raw;
};

typedef void (*token_receiver)(Token token);

class Lexer {
public:
    explicit Lexer(std::istream &buf) : _buf(buf) {}

    void lex(token_receiver receiver);

private:
    std::istream &_buf;
    token_receiver receiver;

    bool is_id_start_char(char i);

    bool is_id_mid_char(char i);

    bool is_num_char(char i);

    bool is_op_char(char i);

    bool is_white_char(char i);

//    void emit_token(Token token);

    Token::Type TokenTypeOf(char state);
};


#endif //K_COMPILER_IN_C_LEXER_H
