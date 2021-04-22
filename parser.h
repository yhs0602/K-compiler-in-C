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
        TYPE_ID,
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


class ID : public Node {
public:
    ID(string value) : Node(Node::TYPE_ID), value(std::move(value)) {}

    string value;
};

class Assign : public Node {
public:
    Assign(shared_ptr<ID> to, shared_ptr<Node> value) : Node(Node::ASSIGN), to(to), value(value) {}

    shared_ptr<ID> to;

    shared_ptr<Node> value;
};

class Sequence : public Node {
public:
    Sequence(shared_ptr<Node> e1, shared_ptr<Node> e2) : Node(Node::SEQ), e1(e1), e2(e2) {}

    shared_ptr<Node> e1, e2;
};


class Parser {
public:
    Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {}

    shared_ptr<Node> parse();

private:
    std::vector<Token> _tokens;

    int parse_unit(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, shared_ptr<Node> &pNode);

    int parse_sequence(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> &pNode);

    int parse_expression(std::vector<Token>::iterator begin, std::vector<Token>::iterator end,
                         std::shared_ptr<Node> &pNode);

    int parse_assign(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode);

    int parse_id(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<ID> pNode);
};


#endif //KCOMPILERINC_PARSER_H
