//Author: Kostiantyn Makrasnov
//Date: 02/12/2020
//Sources: Textbook Psuedo-code (Figure 2.5, Figure 2.17), C++ reference (http://www.cplusplus.com/reference)
//Assignment: EX03_01, EX03_02, EX03_03 (possibly)

#include "Scanner.h"
#include "Parser.h"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    //TODO: replace with classes
    std::string tokenStr[] = {"assign", "plus", "minus", "times", "division", "lparen", "rparen", "id", "read", "write", "number", "error", "end"};

    //Setup compiler objects
    Scanner scanner;
    Parser parser(true);   //do not show parse warnings

    //Setup program to compile
    std::string programText =
        "read A\n"
        "read B\n"
        "sum := (A + B)\n"
        "write sum\n"
        "write sum / 2\n";

    std::string programText2 =
        "read A\n"
        "read B\n";

    std::string programText3 =
        "id := (A * B) + 7\n";

    std::string programText4 =
        "read write\n";

    std::string programText5 =
        "read A\n"
        "read B\n"
        "read C\n"
        "result := (A + (B * C))/(C * A)\n"
        "write result\n"
        "read D\n"
        "A := (result * (A + B + C))/(D * D * D)\n";

    //Begin Compilation
    std::vector<TokenType> tokens = scanner.PerformScan(programText5);

    std::cout << "Program that was parsed: " << std::endl;
    std::cout << programText5 << std::endl;

    std::cout << "----------------------------------------------- " << std::endl;
    std::cout << "(EX03_01) Program tokens from scanner: " << std::endl;
    for(int i = 0; i < tokens.size(); i++)
    {
        std::cout << tokenStr[tokens[i]] << std::endl;
    }

    std::cout << "----------------------------------------------- " << std::endl;
    std::cout << "(EX03_02) Program trace of matches from parser: " << std::endl;
    parser.PerformParse(tokens);

    return 0;
}