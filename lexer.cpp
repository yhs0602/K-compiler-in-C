//
// Created by 양현서 on 2021/04/12.
//

#include "lexer.h"
#include <iostream>
#include <cctype>
#include <cstring>

const int STATE_NO = 0;
const int STATE_ID = 1;
const int STATE_NU = 2;
const int STATE_OP = 3;
const int STATE_X = -1;

const int EVENT_NO = 3;
const int EVENT_ID = 0;
const int EVENT_NU = 1;
const int EVENT_OP = 2;
const int EVENT_X = -1;

char transitions[4][4] = {
        {STATE_ID, STATE_NU, STATE_OP, STATE_NO}, // NO
        {STATE_ID, STATE_ID, STATE_OP, STATE_NO}, // id
        {STATE_X,  STATE_NU, STATE_OP, STATE_NO}, // nu
        {STATE_ID, STATE_NU, STATE_OP, STATE_NO}, // op
};

void Lexer::lex(token_receiver receiver) {
    typedef std::istreambuf_iterator<char> buf_iter;
    std::string token;
    char state = 0;
    for (buf_iter i(_buf), e; i != e; ++i) {
        char event = STATE_NO;
        if (is_id_start_char(*i)) {
            event = EVENT_ID;
        } else if (is_num_char(*i)) {
            event = EVENT_NU;
        } else if (is_op_char(*i)) {
            event = EVENT_OP;
        } else if (is_white_char(*i)) {
            event = EVENT_NO;
        } else {
            event = EVENT_X;
            // lexer error
            std::cout << "Invalid character: " << *i << std::endl;
            return;
        }
        char newstate = transitions[state][event];
        if (newstate == STATE_X) {
            // lexer error
            std::cout << "Lexer error at " << *i << std::endl;
            return;
        }
//        std::cout << "New state for " << *i << " is : " << std::to_string(newstate) << std::endl;
        if (state == newstate) {
            token += *i;
        } else {
            if (state != STATE_NO)
                receiver(Token(token, TokenTypeOf(state)));
            state = newstate;
            token = *i;
        }
    }
}

bool Lexer::is_id_mid_char(char i) {
    if (isalnum(i)) {
        return true;
    }
    return false;
}

bool Lexer::is_id_start_char(char i) {
    if (isalpha(i))
        return true;
    return false;
}

bool Lexer::is_num_char(char i) {
    return isdigit(i);
}

bool Lexer::is_op_char(char i) {
    return strchr(":+=.()[]*/-\"\\\'", i) != nullptr;
//    return i == ':' || i == '+' || i == '=' || i == '.';
}

bool Lexer::is_white_char(char i) {
    return isspace(i);
}

//void Lexer::emit_token(Token token) {
//    receiver(token);
//}

Token::Type Lexer::TokenTypeOf(char state) {
    switch (state) {
        case STATE_ID:
            return Token::ID;
        case STATE_NU:
            return Token::NUM;
        case STATE_OP:
            return Token::OP;
    }
}

std::string Token::get_raw() {
    return raw;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "type: " << token.type << " raw: " << token.raw;
    return os;
}
