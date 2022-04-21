#ifndef __EASY_CALCULATOR_LEXER_H_
#define __EASY_CALCULATOR_LEXER_H_
#include "token.h"
#include <sstream>
#include <iostream>
#include <map>
namespace easy_cal{

class Lexer{
public:
    enum DFAState{
       INIT,
       IF,
       ELSE,
       ID_INT1,
       ID_INT2,
       ID_INT3,
       ID,    //标识符
       GT,
       GE,
       ASSIGNMENT,
       PLUS,
       MINUS,
       MUL,
       DIV,
       SEMICOLON,
       LPAREN,
       RPAREN,
       INTLITERAL,
       STRINGLITERAL, 
    };
    Lexer();//初始化关键字集合
    void lexer(std::string& code);

    void dump(){
        Token token;
        while((token = m_reader.readNext()).m_type != Token::DEFAULT){
            std::cout << token.m_text << ' ' << token.m_type << std::endl;
        }
    }
private:
    //根据符号初始化DFA当前状态
    DFAState initToken(char ch);
    //初始化DFA的状态
    void initState(DFAState& state){
        state = DFAState::INIT;
    }
    bool isAlpha(char ch){
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
    }   

    bool isDigit(char ch){
        return ch >= '0' && ch <= '9';
    }

    bool isBlank(char ch){
        return ch == ' ' || ch == '\t' || ch == '\n';
    }
    //生成Token
    void createToken(){
        if(m_cur_text.tellp()>0){
            m_cur.m_text = m_cur_text.str();
            m_tokens.push_back(m_cur);
            
            m_cur.m_type = Token::INIT;
            m_cur.m_text = "";
            //清空stringstream
            m_cur_text.str(std::string());
            m_cur_text.clear();
        }
    }  
private:
    std::vector<Token> m_tokens;
    Token              m_cur; //当前正在解析的token
    std::stringstream  m_cur_text;//当前token的文本
    std::map<std::string,Token::TokenType> m_keywords;//关键字集合
    TokenReader        m_reader;
};

}
#endif