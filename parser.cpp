//
// Created by 양현서 on 2021/04/22.
//

#include "parser.h"

using namespace std;

shared_ptr<Node> Parser::parse() {
    shared_ptr<Node> node;
    parse_sequence(_tokens.begin(), _tokens.end(), node);
    return node;
}

int Parser::parse_sequence(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> &pNode) {
    int tmp;

    shared_ptr<Node> child;
    shared_ptr<Node> child2;
    tmp = parse_expression(begin, end, child);
    if (begin + tmp >= end) {
        pNode = child;
        return tmp;
    }
    if ((begin + tmp)->get_type() == Token::SEMICOLON) {
        int tmp2 = parse_sequence(begin + tmp + 1, end, child2);
        pNode = make_shared<Sequence>(child, child2);
        return tmp + 1 + tmp2;
    }
    return -1;
}


int Parser::parse_expression(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> &pNode) {
    int tmp;
    shared_ptr<Node> tmpNode;
    tmp = parse_unit(begin, end, tmpNode);
    if (tmp > 0) {
        pNode = tmpNode;
        return tmp;
    }
    tmp = parse_assign(begin, end, tmpNode);
    if (tmp > 0) {
        pNode = tmpNode;
        return tmp;
    }
    tmp = parse_id(begin, end, pNode);


    return 0;
}

int Parser::parse_unit(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, shared_ptr<Node> &pNode) {
    if (begin->get_type() == Token::ID) {
        string raw = begin->get_raw();
        if (raw == "unit") {
            pNode = make_shared<Unit>();
            return 1;
        }
    }
    return 0;
}

int Parser::parse_assign(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode) {
    int tmp;
    shared_ptr<ID> tmpNode;
    tmp = parse_id(begin, end, tmpNode);
    if (tmp <= 0) {
        return 0;
    }
    if ((begin + tmp)->get_type() == Token::ASSIGN) {
        shared_ptr<Node> tmpNode2;
        int tmp2 = parse_expression(begin + tmp + 1, end, tmpNode2);
        if (tmp2 > 0) {
            pNode = make_shared<Assign>(tmpNode, tmpNode2);
            return tmp + tmp2 + 1;
        }
    }
    return 0;
}

int Parser::parse_id(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<ID> pNode) {
    if (begin->get_type() == Token::ID) {
        pNode = make_shared<ID>(begin->get_raw());
        return 1;
    }
    return 0;
}

