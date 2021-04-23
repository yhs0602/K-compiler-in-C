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

class Expression {
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

    Expression(Type type) : type(type) {}

    Type type;

    friend ostream &operator<<(ostream &os, const Expression &node) {
        os << "type: " << node.type;
        return os;
    }
};

class LeftTerm : public Expression {

};

class Add : public LeftTerm {

};

class Unit : public Expression {
public:
    Unit() : Expression(Expression::UNIT) {}
};


class ID : public Expression {
public:
    ID(string value) : Expression(Expression::TYPE_ID), value(std::move(value)) {}

    string value;
};

class Assign : public Expression {
public:
    Assign(shared_ptr<ID> to, shared_ptr<Expression> value) : Expression(Expression::ASSIGN), to(to), value(value) {}

    shared_ptr<ID> to;

    shared_ptr<Expression> value;
};

class Sequence : public Expression {
public:
    Sequence(shared_ptr<Expression> e1, shared_ptr<Expression> e2) : Expression(Expression::SEQ), e1(e1), e2(e2) {}

    shared_ptr<Expression> e1, e2;

    friend ostream &operator<<(ostream &os, const Sequence &sequence) {
        os << static_cast<const Expression &>(sequence) << " e1: " << sequence.e1 << " e2: " << sequence.e2;
        return os;
    }
};


class LetV : public Expression {
public:
    LetV(shared_ptr<ID> to, shared_ptr<Expression> what, shared_ptr<Expression> then) : Expression(Expression::LETV),
                                                                                        to(to), what(what),
                                                                                        then(then) {}

    shared_ptr<ID> to;

    friend ostream &operator<<(ostream &os, const LetV &v) {
        os << static_cast<const Expression &>(v) << " to: " << v.to << " what: " << v.what << " then: " << v.then;
        return os;
    }

    shared_ptr<Expression> what;
    shared_ptr<Expression> then;
};


class Num : public Expression {
public:
    explicit Num(int value) : Expression(Expression::NUM), value(value) {}

    int value;
};

class Write : public Expression {
public:
    explicit Write(shared_ptr<Expression> v) : Expression(Expression::WRITE), v(v) {}

    shared_ptr<Expression> v;
};

class Parser {
public:
    Parser(std::vector<Token> tokens) : _tokens(std::move(tokens)) {}

    shared_ptr<Expression> parse();

private:
    std::vector<Token> _tokens;

    int parse_unit(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, shared_ptr<Expression> &pNode);

    int parse_sequence(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> &pNode);

    int parse_expression(std::vector<Token>::iterator begin, std::vector<Token>::iterator end,
                         std::shared_ptr<Expression> &pNode);

    int parse_assign(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> pNode);

    int parse_id(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<ID> pNode);

    int parse_comment(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> pNode);

    int parse_let(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> pNode);

    int parse_number(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> pNode);

    int parse_write(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Expression> pNode);

    int parse_add(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Add> pNode);
};


#endif //KCOMPILERINC_PARSER_H
