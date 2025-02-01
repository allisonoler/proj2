#include <iostream>
#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream in;
    in.open(argv[1]);
    stringstream ss;
    ss << in.rdbuf();
    string input = ss.str();
    in.close();
    Scanner s = Scanner(input);
    vector<Token> t = s.scanAll();

    Parser p = Parser(t);
    p.parseProgram();
}
