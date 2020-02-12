#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

enum TokenType {assign, plus, minus, times, division, lparen, rparen, id, read, write, number, error};

class Scanner
{
public:
    Scanner();

    std::vector<TokenType> PerformScan(std::string programText);
    int ScanUntilEndOfComment(int counter, std::string &text);
};

#endif