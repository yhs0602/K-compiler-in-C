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
    cout << "Parse_sequence" << endl;
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
    cout << "Parse_expression" << endl;
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

    tmp = parse_comment(begin, end, tmpNode);
    if (tmp > 0) {
        shared_ptr<Node> tmpNode2;
        int tmp2 = parse_expression(begin + tmp, end, tmpNode2);
        if (tmp2 > 0) {
            pNode = tmpNode2;
            return tmp + tmp2;
        }
    }

    tmp = parse_number(begin, end, tmpNode);
    if (tmp > 0) {
        pNode = tmpNode;
        return tmp;
    }

    tmp = parse_write(begin, end, tmpNode);
    if (tmp > 0) {
        pNode = tmpNode;
        return tmp;
    }

    shared_ptr<ID> tmpIdNode;
    tmp = parse_id(begin, end, tmpIdNode);
    if (tmp > 0) {
        pNode = tmpIdNode;
        return tmp;
    }

    shared_ptr<Add> addNode;
    tmp = parse_add(begin, end, addNode);
    if (tmp > 0) {
        pNode = addNode;
        return tmp;
    }
    tmp = parse_let(begin, end, tmpNode);
    if (tmp > 0) {
        pNode = tmpNode;
        return tmp;
    }

    return 0;
}

int Parser::parse_unit(std::vector<Token>::iterator begin, std::vector<Token>::iterator end, shared_ptr<Node> &pNode) {
    cout << "Parse_unit" << endl;
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
    cout << "Parse_assign" << endl;
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
    cout << "parse_id" << endl;
    if (begin->get_type() == Token::ID) {
        pNode = make_shared<ID>(begin->get_raw());
        return 1;
    }
    return 0;
}

int Parser::parse_comment(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode) {
    cout << "parse_comment" << endl;
    int cnt = 1;
    if (begin->get_type() == Token::LCOMMENT) {
        while ((begin + cnt)->get_type() != Token::RCOMMENT) {
            cout << "Comment: " << (begin + cnt)->get_raw() << ";;";
            cnt++;
        }
        cout << endl;
        return cnt + 1;
    }
    return 0;
}

int Parser::parse_let(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode) {
    cout << "Parse let" << endl;
    if (begin->get_type() == Token::LET) {
        cout << "is let" << endl;
        shared_ptr<ID> tmp_id_node;
        int tmp = parse_id(begin + 1, end, tmp_id_node);
        if (tmp > 0) {
            cout << "success get id" << endl;
            if ((begin + 1 + tmp)->get_type() == Token::ASSIGN) {
                cout << "assign is right" << endl;
                shared_ptr<Node> valueNode;
                int tmp2 = parse_expression(begin + 1 + tmp + 1, end, valueNode);
                if (tmp2 > 0) {
                    if ((begin + 1 + tmp + 1 + tmp2)->get_type() == Token::IN) {
                        shared_ptr<Node> thenNode;
                        int tmp3 = parse_expression(begin + 1 + tmp + 1 + tmp2 + 1, end, thenNode);
                        if (tmp3 > 0) {
                            pNode = make_shared<LetV>(tmp_id_node, valueNode, thenNode);
                            return 1 + tmp + 1 + tmp2 + 1 + tmp3;
                        }
                    }
                }
            } else {
                cout << " Not assingg " << endl;
            }
        } else if ((begin + 1)->get_type() == Token::PROC) {

        }
    } else {
        cout << "Not let" << endl;
    }
    return 0;
}

int Parser::parse_number(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode) {
    cout << "parse_number" << endl;
    if (begin->get_type() == Token::NUM) {
        string r = begin->get_raw();
        int val = stoi(r);
        pNode = make_shared<Num>(val);
        return 1;
    }
    return 0;
}

int Parser::parse_write(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Node> pNode) {
    if (begin->get_type() == Token::WRITE) {
        shared_ptr<Node> tmpNode;
        int tmp = parse_expression(begin + 1, end, tmpNode);
        if (tmp > 0) {
            pNode = make_shared<Write>(tmpNode);
            return 1 + tmp;
        }
    }
    return 0;
}

int Parser::parse_add(vector<Token>::iterator begin, vector<Token>::iterator end, shared_ptr<Add> pNode) {
    shared_ptr<Node> tmpNode1;
    int tmp = parse_expression(begin, end, tmpNode1);
    if (tmp > 0) {
        if ((begin + tmp)->get_type() == Token::PLUS) {
            shared_ptr<Node> tmpNode2;
            int tmp2 = parse_expression(begin + tmp + 1, end, tmpNode2);
            if (tmp2 > 0) {
                pNode = make_shared<Add>(tmpNode1, tmpNode2);
                return tmp + 1 + tmp2;
            }
        }
    }
    return 0;
}

