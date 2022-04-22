#ifndef __EASY_CALCULATOR_PARSER_H_
#define __EASY_CALCULATOR_PARSER_H_
#include "ast.h"
#include "../lexer/lexer.h"
#include <string>
namespace easy_cal{

/*
 简易语法：解析表达式、整形变量声明、赋值语句
 语法规则：
 Program -> IntDeclartion | expressStat | assignmentStat
 IntDeclartion -> 'int' Id ( = plusStat)? ';'
 expressionStat -> plusStat ';'
 plusStat -> mulStat ((+ | - ) mulStat)*
 mulStat -> Primary ((* | / ) Primary)*
 Primary -> Identifier |keyWords | (plusStat)

*/
class Parser{
public:
    Parser();
    ASTNode parse(std::string& code);
private:
    ASTNode parseProgram();
    ASTNode parseExpressionStat();
    ASTNode parseAssignmentStat();
    ASTNode parseIntDeclare();
    ASTNode parsePlusStat();
    ASTNode parseMulStat();
    ASTNode parsePrimary();    
private:
   Lexer  m_lexer;
};
}

#endif