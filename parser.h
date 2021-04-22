//
// Created by 양현서 on 2021/04/22.
//

#ifndef KCOMPILERINC_PARSER_H
#define KCOMPILERINC_PARSER_H


#include <utility>
#include <vector>
#include <memory>
#include <ostream>
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
        LETV,
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

    friend ostream &operator<<(ostream &os, const Node &node) {
        os << "type: " << node.type;
        return os;
    }
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

    friend ostream &operator<<(ostream &os, const Sequence &sequence) {
        os << static_cast<const Node &>(sequence) << " e1: " << sequence.e1 << " e2: " << sequence.e2;
        return os;
    }
};


class LetV : public Node {
public:
    LetV(shared_ptr<ID> to, shared_ptr<Node> what, shared_ptr<Node> then) : Node(Node::LETV), to(to), what(what),
                                                                            then(then) {}

    shared_ptr<ID> to;

    friend ostream &operator<<(ostream &os, const LetV &v) {
        os << static_cast<const Node &>(v) << " to: " << v.to << " what: " << v.what << " then: " << v.then;
        return os;
    }

    shared_ptr<Node> what;
    shared_ptr<Node> then;
};


class Num : public Node {
public:
    explicit Num(int value) : Node(Node::NUM), value(value) {}

    int value;
};

class Write : public Node {
public:
    explicit Write(shared_ptr<Node> v) : Node(Node::WRITE), v(v) {}

    shared_ptr<Node> v;
};

class Add : public Node {
public:
    Add(shared_ptr<Node> v1, shared_ptr<Node> v2) : Node(Node::ADD), v1(v1), v2(v2) {}

    shared_ptr<Node> v1, v2;
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

    int parse_comment(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode);

    int parse_let(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode);

    int parse_number(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode);

    int parse_write(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode);

    int parse_add(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Add> pNode);
};


#endif //KCOMPILERINC_PARSER_H
