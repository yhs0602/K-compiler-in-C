//
// Created by 양현서 on 2021/04/22.
//

#ifndef KCOMPILERINC_PARSER_H
#define KCOMPILERINC_PARSER_H


#include <utility>
#include <vector>
#include <memory>
#include "lexer.h"

using namespace std;

class Node {
public:
    enum Type {
        BASE,
        UNIT,
        ASSIGN,
        SEQ,
        IF,
        WHILE,
        READ,
        WRITE,
        LETIN,
        LETPROC,
        CALL,
        CALLR,
        NUM,
        BOOL,
        RECORD,
        RECORDLOOKUP,
        RECORDASSIGN,
        ID,
        ADD,
        SUB,
        MUL,
        DIV,
        GT,
        EQ,
        NOT
    };

    Node(Type type) : type(type) {}

    Type type;
};


class Unit : public Node {
public:
    Unit() : Node(Node::UNIT) {}
};


class ID;

class Assign : Node {
public:
    Assign(class ID *to, Node *value) : Node(Node::ASSIGN), to(to), value(value) {}

    class ID *to;

    Node *value;
};

class Sequence : Node {
public:
    Sequence(Node *e1, Node *e2) : Node(Node::SEQ), e1(e1), e2(e2) {}

    Node *e1, *e2;
};


class Parser {
public:
    Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {}

    shared_ptr<Node> parse();

private:
    std::vector<Token> _tokens;

    int parse_unit(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, shared_ptr<Node> &pNode);

    int parse_expression(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, std::shared_ptr<Node> &pNode);
};


#endif //KCOMPILERINC_PARSER_H
