#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


// https://stackoverflow.com/a/38799667/8614565
istringstream test_data(R"~(

(* Public test case 1 *)

let x := 1 in
let y := 2 in
write x + y

(* Output : prints out "3\n" *)

)~");


__dead2 void usage(char *name) {
    printf("Usage: %s filename\n", name);
    exit(-2);
}

__dead2 void error(char *str) {
    cout << str << endl;
    exit(-1);
}

vector<Token> tokens;

void onNewToken(Token token) {
    std::cout << "token: " << token << std::endl;
    tokens.push_back(token);
}


int main(int argc, char **argv) {
    std::string filename = argv[1] ? argv[1] : "";

//    if (argc < 2)
//        usage(argv[0]);
    std::ifstream ifs;
    // try to open a file if we have a filename
    if (!filename.empty())
        ifs.open(filename);

    // This will ONLY fail if we tried to open a file
    // because the filename was not empty
    if (!ifs) {
        std::cerr << "Error opening file: " << filename << '\n';
        return EXIT_FAILURE;
    }

    // if we have an open file bind to it else bind to test_data
    std::istream &is = ifs.is_open() ? static_cast<std::istream &>(ifs) : test_data;
    Lexer lexer(is);
    lexer.lex(onNewToken);
    Parser parser(tokens);
    shared_ptr<Node> parsed = parser.parse();
    cout << endl << "End" << endl;
    cout << parsed << endl;

//    // use is here
//    for (std::string word; is >> word;) {
//        std::reverse(word.begin(), word.end());
//        std::cout << word << '\n';
//    }

    return 0;
}