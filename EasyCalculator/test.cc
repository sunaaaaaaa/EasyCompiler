#include "lexer/lexer.h"
#include "parser/parser.h"
#include <string>
#include <unistd.h>

void test(){
    easy_cal::Lexer lexer;
    std::string code = "int a = 45;";
    std::string code2 = "int a = 45; int b = 6; a + b; if (a + b = 5) else();";
    lexer.lexer(code);
    lexer.dump();
    lexer.lexer(code2);
    lexer.dump();
}

void test2(){
    easy_cal::Parser parser;
    std::string code = "int age = 45+2; age= 20; age+10*2;";
    easy_cal::ASTNode::ptr p = parser.parse(code);
    parser.getLexer().dump();
    easy_cal::ASTNode::PrintAST(*p.get());

    std::string code2 = "2+3*5;";
    easy_cal::ASTNode::ptr p1 = parser.parse(code2);
    parser.getLexer().dump();
    easy_cal::ASTNode::PrintAST(*p1.get());

    std::string code3 = "2+3*;";
    easy_cal::ASTNode::ptr p2 = parser.parse(code3);
    parser.getLexer().dump();
    easy_cal::ASTNode::PrintAST(*p2.get());
}

int main(){
    test2();
}