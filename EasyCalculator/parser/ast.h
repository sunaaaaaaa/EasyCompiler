#ifndef __EASY_CAL_AST_H_
#define __EASY_CAL_AST_H_
#include <string>
#include <memory>
#include <vector>

namespace easy_cal{

class ASTNode{
public:
     typedef std::shared_ptr<ASTNode> ptr;
     enum ASTNodeType{
         Program,       //起始节点
         IntDeclartion, //整形变量声明
         ExpressionStat,//表达式
         AssignmentStat,//赋值表达式
         MulStat,//乘法表达式
         PlusStat,//加法表达式
        //  DivStat,//除法表达式
        //  MinusStat,//减法表达式
         Identifier,//标识符
         IntLiteral, //整型字面量
         DEFAULT, //默认状态，当语法解析无法解析时，返回的ASTNode的默认属性，相当于空对象
     };
     ASTNode(ASTNodeType type,std::string text);
     const ASTNodeType getType() const {return m_type;}
     const std::string& getText()const {return m_text;} 
     std::vector<ASTNode::ptr> getChilds();
     ASTNode::ptr getParent();
     void addChildNode(ASTNode& node);
     
     //静态函数，打印当前AST子树
     static void PrintAST(ASTNode& node,uint32_t level = 0);
private:
     ASTNode::ptr m_parent; //父节点
     std::vector<ASTNode::ptr> m_childs;
     ASTNodeType m_type = ASTNodeType::Program;  //当前AST节点的类型
     std::string m_text; //当前AST节点的文本内容
};


}
#endif