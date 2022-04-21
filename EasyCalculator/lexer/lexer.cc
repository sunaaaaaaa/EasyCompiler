#include "lexer.h"
#include <iostream>

namespace easy_cal{

Lexer::Lexer(){
   m_keywords.insert(std::map<std::string,Token::TokenType>::value_type("int",Token::INT));
   m_keywords.insert(std::map<std::string,Token::TokenType>::value_type("if",Token::IF));
   m_keywords.insert(std::map<std::string,Token::TokenType>::value_type("else",Token::ELSE));
}

Lexer::DFAState Lexer::initToken(char ch){
   DFAState state = DFAState::INIT;
   if(ch == ' '){
       return state;
   }else if(isAlpha(ch)){
      state = DFAState::ID;
      m_cur.m_type = Token::IDENTIFIER;
      m_cur_text << ch;
   }else if(isDigit(ch)){
      //目前只识别整数
      state = DFAState::INTLITERAL;
      m_cur.m_type = Token::INTLITERAL;
      m_cur_text << ch;
   }else if(ch == '>'){
      state = DFAState::GT;
      m_cur.m_type = Token::GT;
      m_cur_text << ch;
   }else if(ch == '='){
      state = DFAState::ASSIGNMENT;
      m_cur.m_type = Token::ASSIGN;
      m_cur_text << ch; 
   }else if(ch == '<'){
      // state = DFAState::;
      // m_cur.m_type = Token::GT;
      // m_cur_text << ch;
   }else if(ch == '+'){
      state = DFAState::PLUS;
      m_cur.m_type = Token::PLUS;
      m_cur_text << ch;
   }else if(ch == '-'){
      state = DFAState::MINUS;
      m_cur.m_type = Token::MINUS;
      m_cur_text << ch; 
   }else if(ch == '*'){
      state = DFAState::MUL;
      m_cur.m_type = Token::MUL;
      m_cur_text << ch;
   }else if(ch == '/'){
      state = DFAState::DIV;
      m_cur.m_type = Token::DIV;
      m_cur_text << ch;
   }else if(ch == '('){
      state = DFAState::LPAREN;
      m_cur.m_type = Token::LPAREN;
      m_cur_text << ch;
   }else if(ch == ')'){
      state = DFAState::RPAREN;
      m_cur.m_type = Token::RPAREN;
      m_cur_text << ch;
   }else if(ch == ';'){
      state = DFAState::SEMICOLON;
      m_cur.m_type = Token::SEMICOLON;
      m_cur_text << ch;
   }else{
      throw std::logic_error("this char now is not support");
   }
   return state;
}


void Lexer::lexer(std::string& code){
   // const char* reader =  code.c_str();
   DFAState state = DFAState::INIT;

   try{
      //每次循环预读一个字符
      for(auto ch:code){
         switch (state)
         {
         case DFAState::INIT:
            //如果状态机当前为INIT状态，根据当前字符进行状态转移
            state = initToken(ch);
            break;
         case DFAState::ID:
            //如果当前状态机处于ID状态，检测下一个字符是否为字符或者下划线或者数字
            //注意，不支持下划线开头，因为初始状态不会根据_来进行状态转移
            if(isAlpha(ch)||isDigit(ch)||ch == '_'){
               m_cur_text << ch;
            }else { //不是的话，生成Token，并重置状态机
               //如果是关键字
               auto it = m_keywords.find(m_cur_text.str());
               if(it != m_keywords.end()){
                  //关键字
                  m_cur.m_type = it->second;
               }
               //如果不是关键字，则表示当前为标识符
               createToken();
               state = initToken(ch);
            }
            break;
         case DFAState::INTLITERAL:
            if(isDigit(ch)){
               m_cur_text << ch;
            }else{
               createToken();
               state = initToken(ch);
            }
            break;
         case DFAState::GE:
            //GE为终止状态 >=
            createToken();
            state = initToken(ch);
            break;
         case DFAState::GT:
             if(ch == '='){
                //将token类型设置为GE
                m_cur.m_type = Token::TokenType::GE;
                //状态机转到GE
                state = DFAState::GE;
             }else{
                createToken();
                state = initToken(ch);
             }
             break;
         case DFAState::ASSIGNMENT:
            // == 语句 暂时不实现
            createToken();
            state = initToken(ch);
            break;
         case DFAState::LPAREN:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::RPAREN:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::PLUS:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::MINUS:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::MUL:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::DIV:
            createToken();
            state = initToken(ch);
            break;
         case DFAState::SEMICOLON:
            createToken();
            state = initToken(ch);
            break;  
         default:
            break;
         }
      }
      //处理最后一个字符
      createToken();
   }catch(std::exception& e){
      throw std::logic_error(e.what());
   }
   m_reader = TokenReader(m_tokens);
}

}