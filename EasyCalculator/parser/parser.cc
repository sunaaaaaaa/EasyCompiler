#include "parser.h"
#include <iostream>
namespace easy_cal{

Parser::Parser(){}

ASTNode::ptr Parser::parse(std::string& code){
    m_lexer.init();
    m_lexer.lexer(code);
    return parseProgram();
}

ASTNode::ptr Parser::parseProgram(){
   ASTNode::ptr node(new ASTNode(ASTNode::ASTNodeType::Program,"pwc"));
   while(m_lexer.m_reader.peek().getType() != Token::DEFAULT){
        ASTNode::ptr child = parseIntDeclare();
        if(child.get()->getType() == ASTNode::DEFAULT){
            child = parseExpressionStat();
        }
        if(child.get()->getType() == ASTNode::DEFAULT){
            child = parseAssignmentStat();
        }

        if(child.get()->getType() != ASTNode::DEFAULT){
            node->addChildNode(child);
        }else{
            throw std::logic_error("unknow statment");
        }
   }
   return node;
}

//解析int变量声明语句
ASTNode::ptr Parser::parseIntDeclare(){
    ASTNode::ptr node(new ASTNode(ASTNode::DEFAULT,""));
    Token token = m_lexer.m_reader.peek();
    if(token.getType() == Token::INT){
        m_lexer.m_reader.readNext();//取出int关键字
        if(m_lexer.m_reader.peek().getType() == Token::IDENTIFIER){
            //取出标识符，插入AST
            token = m_lexer.m_reader.readNext();
            node.reset(new ASTNode(ASTNode::IntDeclartion,token.getText()));
            
            token = m_lexer.m_reader.peek();
            if(token.getType() == Token::ASSIGN){
                //取出等号
                m_lexer.m_reader.readNext();
                ASTNode::ptr child = parsePlusStat();

                if(child.get()->getType() == ASTNode::DEFAULT){
                    //等号后面为空，逻辑错误
                    throw std::logic_error("illegal variable initialization,expecting an expression");
                }else{
                    node.get()->addChildNode(child);
                }
            }
        }
    }
    if(node.get()->getType()!=ASTNode::DEFAULT){
        token = m_lexer.m_reader.peek();
        if(token.getType()==Token::SEMICOLON){
          m_lexer.m_reader.readNext();
        }else{
          throw std::logic_error("invalid statment, expecting ';' ");
        }
    }
    
    return node; 
}
//解析表达式
ASTNode::ptr Parser::parseExpressionStat(){
    uint32_t pos = m_lexer.m_reader.getPosition();
    ASTNode::ptr node = parsePlusStat();
    if(node.get()->getType()!= ASTNode::DEFAULT){
        Token token = m_lexer.m_reader.peek();
        if(token.getType()==Token::SEMICOLON){
            m_lexer.m_reader.readNext();//去除分号
        }else{
            node.reset(new ASTNode(ASTNode::DEFAULT,""));
            m_lexer.m_reader.setPosition(pos);
        }
    }
    return node; 
}
//解析赋值语句
ASTNode::ptr Parser::parseAssignmentStat(){
   ASTNode::ptr node(new ASTNode(ASTNode::DEFAULT,""));
   Token token = m_lexer.m_reader.peek();
   if(token.getType()==Token::IDENTIFIER){
       m_lexer.m_reader.readNext();
       node.reset(new ASTNode(ASTNode::AssignmentStat,token.getText()));

       token = m_lexer.m_reader.peek();
       if(token.getType() == Token::ASSIGN){
           m_lexer.m_reader.readNext();
           ASTNode::ptr child = parsePlusStat();

           if(child.get()->getType() == ASTNode::DEFAULT){
               throw std::logic_error("invalid assignment statment,expecting an expression");
           }else{
               node.get()->addChildNode(child);

               //检查最后是否为分号
               token = m_lexer.m_reader.peek();
               if(token.getType()==Token::SEMICOLON){
                   m_lexer.m_reader.readNext();
               }else{
                   throw std::logic_error("invalid statment,expecting semiclon");
               }
           }
       }else{
           //如果不是等号，则说明不是赋值语句，回退
           m_lexer.m_reader.back();
       } 
   }
   return node;  
}
//解析加法语句
ASTNode::ptr Parser::parsePlusStat(){
   ASTNode::ptr child = parseMulStat();
   ASTNode::ptr node = child;
   if(child.get()->getType() != ASTNode::DEFAULT){
      while(true){
          Token token = m_lexer.m_reader.peek();
          if(token.getType()==Token::PLUS || token.getType()==Token::MINUS){
              token = m_lexer.m_reader.readNext();
              ASTNode::ptr child2 = parseMulStat();
              if(child2.get()->getType()!=ASTNode::DEFAULT){
                  node.reset(new ASTNode(ASTNode::PlusStat,token.getText()));
                  node.get()->addChildNode(child);
                  node.get()->addChildNode(child2);
                  child = node; //自底向上构建，保证最左边加法语句在树的最下面，以保证结合性
              }else{
                  throw std::logic_error("invalid plus expression,expecting the right part");
              }
          }else{
              break;
          }
      }
   }
   return node;
}
//解析乘法语句
ASTNode::ptr Parser::parseMulStat(){
   ASTNode::ptr child = parsePrimary();
   ASTNode::ptr node = child;   
   while(true){
      Token token = m_lexer.m_reader.peek();
      if(token.getType() == Token::MUL || token.getType() == Token::DIV){
          m_lexer.m_reader.readNext();
          ASTNode::ptr child2 = parseMulStat();
          if(child2.get()->getType() != ASTNode::DEFAULT){
              node.reset(new ASTNode(ASTNode::MulStat,token.getText()));
              node.get()->addChildNode(child);
              node.get()->addChildNode(child2);
              child = node;
          }else{
              throw std::logic_error("invalid multiplicative expression,expecting the right part");
          }
      }else{
          break;
      }
   }
   return node;
}
//解析基础语句
ASTNode::ptr Parser::parsePrimary(){
   ASTNode::ptr node(new ASTNode(ASTNode::DEFAULT,""));
   Token token = m_lexer.m_reader.peek();
   if(token.getType() != Token::DEFAULT){
       if(token.getType() == Token::INTLITERAL){
           //整型字面量
           m_lexer.m_reader.readNext();
           node.reset(new ASTNode(ASTNode::IntLiteral,token.getText()));
       }else if(token.getType() == Token::IDENTIFIER){
           m_lexer.m_reader.readNext();
           node.reset(new ASTNode(ASTNode::Identifier,token.getText()));
       }else if(token.getType() == Token::LPAREN){
           m_lexer.m_reader.readNext();
           node = parsePlusStat();
           if(node.get()->getType()!=ASTNode::DEFAULT){
               token = m_lexer.m_reader.peek();

               if(token.getType()==Token::RPAREN){
                   m_lexer.m_reader.readNext();
               }else{
                   throw std::logic_error("expecting right parent");
               }
           }else{
               throw std::logic_error("expecting an plus statment inside parent");
           }
       }
   }
   return node;
}

}