#include "Scanner.h"
//#include "Parser.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    //TODO: replace with classes
    std::string enumStr[] = {"assign", "plus", "minus", "times", "division", "lparen", "rparen", "id", "read", "write", "number", "error"};

    //Scanner* scanner = new Scanner();
    Scanner scanner;

    std::string programText =
        "read A\n"
        "/*asdasdasd  */"
        "read B\n"
        "//asdasd asdasd//*/"
        "sum := A + B\n"
        "write sum\n"
        "write sum / 2\n"; 

    std::vector<TokenType> tokens = scanner.PerformScan(programText);

    std::cout << "Program that was parsed: " << std::endl;
    std::cout << programText << std::endl;

    std::cout << "----------------------------- " << std::endl;
    std::cout << "Program tokens from scanner: " << std::endl;
    for(int i = 0; i < tokens.size(); i++)
    {
        std::cout << enumStr[tokens[i]] << std::endl;
    }

    return 0;
}