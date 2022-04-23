#ifndef __EASY_CALCULATOR_TOKEN_H_
#define __EASY_CALCULATOR_TOKEN_H_
#include <string>
#include <vector>
#include <iostream>
namespace easy_cal{

class Token{
public:
    friend class Lexer;
    enum TokenType{
        INIT,  //初始态
        PLUS,  //+
        MINUS, //-
        MUL,   //*
        DIV,   // /
        GE,    //>=
        GT,    //>
        EQ,    //=
        LE,    //<=
        LT,    //<
        SEMICOLON,  //;
        LPAREN,     //(
        RPAREN,     //)
        ASSIGN,     //=
        IF,
        ELSE,       //else关键字
        INT,        //int关键字 
        IDENTIFIER, //标识符
        INTLITERAL,//整型字面量
        STRINGLITERAL,//字符型字面量
        DEFAULT, //默认Token，用于TokenReader终止判断
    };
    Token(){};
    Token(TokenType type):m_type(type){} 
    Token(std::string& text,TokenType type):m_text(text),m_type(type){}
    const std::string& getText()const {return m_text;}
    const TokenType getType()const {return m_type;}
private:
    std::string m_text; //Token文本
    TokenType m_type;   //Token类型
};

class TokenReader{
public:
    TokenReader(){
        m_default = Token(Token::DEFAULT);
    };
    TokenReader(std::vector<Token>& tokens){
        m_default = Token(Token::DEFAULT);
        m_tokens.swap(tokens);
    }
    void init(){
        initPos();
        m_tokens.clear();
    }
    void initPos(){
        m_pos = 0;
    }
    //读取下一个Token
    const Token& readNext(){
        if(m_pos < m_tokens.size()){
            return m_tokens.at(m_pos++);
        }
        return m_default;
    }
    //访问下一个Token，但不取出
    const Token& peek(){
        if(m_pos < m_tokens.size()){
            return m_tokens.at(m_pos);
        }
        return m_default;
    }

    void  back(){
        if(m_pos > 0){
           m_pos--;
        }
    }
    uint32_t getPosition(){
        return m_pos;
    }

    void setPosition(uint32_t position){
        if(m_pos >= 0 && m_pos < m_tokens.size()){
             m_pos = position;
        }
    }
private:
    std::vector<Token> m_tokens;
    uint32_t m_pos = 0;
    Token   m_default;
};

}

#endif