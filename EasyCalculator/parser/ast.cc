#include "ast.h"
#include <iostream>

namespace easy_cal{

ASTNode::ASTNode(ASTNodeType type,std::string text):m_type(type),m_text(text){}

std::vector<ASTNode::ptr> ASTNode::getChilds(){
    return m_childs;
}
ASTNode::ptr ASTNode::getParent(){
    return m_parent;
}
void ASTNode::addChildNode(ASTNode::ptr node){
    m_childs.push_back(node);
}

void ASTNode::PrintAST(ASTNode& node,uint32_t level){
    for(uint32_t i = 0;i<level;++i){
        std::cout << '\t';
    }
    std::cout << node.m_type << "  " << node.m_text << std::endl;
    ++level;  
    for(auto child: node.m_childs){
        PrintAST(*child.get(), level); 
    }
}

}