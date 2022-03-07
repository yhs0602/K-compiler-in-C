//
// Created by 양현서 on 2021/04/12.
//

#ifndef K_COMPILER_IN_C_LEXER_H
#define K_COMPILER_IN_C_LEXER_H

#include <string>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

class Token {
public:
    enum Type {
        ID,
        NUM,
        OP,
        LPAR,
        RPAR,
        SEMICOLON,
        ASSIGN,
        GT,
        LT,
        CLPAR,
        CRPAR,
        COMMA,
        PLUS,
        MINUS,
        STAR,
        SLASH,
        DOT,
        EQ,
        UNIT,
        IF,
        THEN,
        ELSE,
        WHILE,
        DO,
        READ,
        WRITE,
        LET,
        IN,
        PROC,
        BTRUE,
        BFALSE,
        NOT,
        LCOMMENT,
        RCOMMENT
    };

    Token(std::string raw, Type type);

    string get_raw();

    Type get_type();

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

    static bool is_id_start_char(char i);

    static bool is_id_mid_char(char i);

    static bool is_num_char(char i);

    static bool is_op_char(char i);

    static bool is_white_char(char i);

//    void emit_token(Token token);

    static Token::Type TokenTypeOf(char state);
};


#endif //K_COMPILER_IN_C_LEXER_H
