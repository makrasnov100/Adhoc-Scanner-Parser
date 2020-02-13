#include "Scanner.h"
#include "Token.h"
#include <string>
#include <vector>
#include <cctype>   //isdigit
#include <iostream>

Scanner::Scanner()
{
    //Setup Scanner
}

std::vector<Token> Scanner::PerformScan(std::string text)
{
    //Reference: Used Psuedo code provided in text book (Figure 2.5)

    //Variables keeping track of the scanning progress
    std::vector<Token> tokens;
    int counter = 0;

    //Skip initial white space
    while(text[counter] == ' ' || text[counter] == '\r' || text[counter] == '\n' || text[counter] == '\t')
    {
        counter++;
    }

    //Run scanner until lexigraphical error occurs or reached end of program
    while(counter < text.size() && counter != -1)
    {
        //Check one charecter a time branching into peeks and loops for more complex tokens
        switch (text[counter])
        {
            case '(':
                tokens.push_back(Token(text.substr(counter, 1), lparen));
                break;
            case ')':
                tokens.push_back(Token(text.substr(counter, 1), rparen));
                break;
            case '+':
                tokens.push_back(Token(text.substr(counter, 1), plus));
                break;
            case '-':
                tokens.push_back(Token(text.substr(counter, 1), minus));
                break;
            case '*':
                tokens.push_back(Token(text.substr(counter, 1), times));
                break;
            case ':':
                counter++;
                if(counter < text.size() && text[counter] == '=') 
                {
                    tokens.push_back(Token(text.substr(counter-1, 2), assign));
                } 
                else 
                {
                    tokens.push_back(Token("", error));
                    return tokens;
                }
                break;
            case '/':
                counter++;
                if(counter < text.size() && (text[counter] == '/' || text[counter] == '*'))
                {
                    counter = ScanUntilEndOfComment(counter, text);
                }
                else
                {
                    counter--;
                    tokens.push_back(Token(text.substr(counter, 1), division));
                }
                break;
            case '.':
            {
                int startCounter = counter;
                counter++;
                //check if first character after decimal is a digit
                if (counter < text.size() && isdigit(text[counter]))
                {
                    //include any remaining digit characters
                    counter++;
                    while (counter < text.size() && isdigit(text[counter]))
                    {
                        counter++;
                    }
                    counter--;
                    tokens.push_back(Token(text.substr(startCounter, counter-startCounter), number));
                }
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                int startCounter = counter;
                counter++;
                //check if a valid number (only one period (decimal) and as many digits, no letters)
                bool decimalIncluded = false;
                while (counter < text.size() && (isdigit(text[counter]) || text[counter] == '.' && !decimalIncluded))
                {
                    if (text[counter] == '.')
                    {
                        decimalIncluded = true;
                    }
                    counter++;
                }
                counter--;

                tokens.push_back(Token(text.substr(startCounter, (counter - startCounter) + 1), number));
                break;
            }
            case '\r':
            case '\n':
            case ' ':
            case '\t':
                break;
            default:
                //check for id
                if(isalpha(text[counter]))
                {
                    std::string curID = "";
                    curID += text[counter];

                    counter++;
                    while(counter < text.size() && (isalnum(text[counter])))
                    {
                        curID += text[counter];
                        counter++;
                    }
                    counter--;

                    //Check if "read" or "write" keywords otherwise its an "id"
                    if (curID == "read")
                        tokens.push_back(Token(text.substr(counter - 3, 4), read));
                    else if (curID == "write")
                        tokens.push_back(Token(text.substr(counter - 4, 5), write));
                    else
                        tokens.push_back(Token(text.substr(counter - (curID.size()-1), curID.size()), id));
                }
                else
                {
                    tokens.push_back(Token("", error));
                    return tokens;
                }
        }
        counter++;
    }

    //write an end of program token for parser to use
    tokens.push_back(Token("", end));

    return tokens;
}


//Skips to end of comment by searching for a remination of a started comment
//NOTE: starts on the charecter that openend the comment
int Scanner::ScanUntilEndOfComment(int counter, std::string &text)
{
    counter++;
    while(counter < text.size())
    {
        if(text[counter] == '\n')
        {
            return counter;
        }
        else if (text[counter] == '*' && text[counter+1] < text.size() && text[counter+1] == '/')
        {
            counter++;
            return counter;
        }
        else
        {
            counter++;
        }
    }
    return counter;
}

