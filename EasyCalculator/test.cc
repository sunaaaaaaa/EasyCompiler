#include "lexer/lexer.h"
#include <string>
#include <unistd.h>
int main(){
    easy_cal::Lexer lexer;

    std::string code = "int a = 45;";
    std::string code2 = "int a = 45; int b = 6; a + b; if (a + b = 5) else();";
    lexer.lexer(code);
    sleep(1);
    lexer.dump();
    lexer.lexer(code2);
    lexer.dump();
}