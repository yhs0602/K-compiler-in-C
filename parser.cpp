//
// Created by 양현서 on 2021/04/22.
//

#include "parser.h"

using namespace std;

shared_ptr<Node> Parser::parse() {
    shared_ptr<Node> node;
    parse_expression(_tokens.begin(), _tokens.end(), node);
    return node;
}

int Parser::parse_expression(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> &pNode) {
    int tmp;
    do {
        tmp = parse_unit(begin, end, pNode);
        if (tmp > 0) {
            begin += tmp;
        }
    } while (tmp > 0);

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
    return -1;
}

