#include "parser.h"

namespace easy_cal{
Parser::Parser(){}
ASTNode Parser::parse(std::string& code){
    m_lexer.lexer(code);
    return parseProgram();
}

ASTNode Parser::parseProgram(){
   ASTNode node(ASTNode::ASTNodeType::Program,"pwc");
   while(m_lexer.m_reader.peek().getType != Token::DEFAULT){
        ASTNode child = parseIntDeclare();
        if(child.getType == ASTNode::DEFAULT){
            child = parseExpressionStat();
        }
        if(child.getType == ASTNode::DEFAULT){
            child = parseAssignmentStat();
        }

        if(child.getType != ASTNode::DEFAULT){
            node.addChildNode(child);
        }else{
            throw std::logic_error("unknow statment");
        }
   }
   return node;
}
ASTNode Parser::parseExpressionStat(){

}
ASTNode Parser::parseAssignmentStat(){

}
ASTNode Parser::parseIntDeclare(){

}
ASTNode Parser::parsePlusStat(){

}
ASTNode Parser::parseMulStat(){

}
ASTNode Parser::parsePrimary(){

}  
}