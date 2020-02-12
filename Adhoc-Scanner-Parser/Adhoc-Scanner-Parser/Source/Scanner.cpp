#include "Scanner.h"
#include <string>
#include <vector>
#include <cctype>   //isdigit

Scanner::Scanner()
{
    //Setup Scanner
}

std::vector<TokenType> Scanner::PerformScan(std::string text)
{
    //Used Psuedo code provided in text book (Figure 2.5)

    //Variables keeping track of the scanning progress
    std::vector<TokenType> tokens;
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
                tokens.push_back(lparen);
                break;
            case ')':
                tokens.push_back(rparen);
                break;
            case '+':
                tokens.push_back(plus);
                break;
            case '-':
                tokens.push_back(minus);
                break;
            case '*':
                tokens.push_back(times);
                break;
            case ':':
                counter++;
                if(counter < text.size() && text[counter] == '=') 
                {
                    tokens.push_back(assign);
                } 
                else 
                {
                    tokens.push_back(error);
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
                    tokens.push_back(division);
                }
                break;
            case '.':
                counter++;
                //check if first character after decimal is a digit
                if(counter < text.size() && isdigit(text[counter]))
                {
                    //include any remaining digit characters
                    counter++;
                    while(counter < text.size() && isdigit(text[counter]))
                    {
                        counter++;
                    }
                    tokens.push_back(number);
                    counter--;
                }
                break;
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

                //(TODO: if need ending point its counter - 1)
                tokens.push_back(number);
                counter--;
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

                    //check if "read" or "write" keywords
                    if(curID == "read")
                    {
                        tokens.push_back(read);
                    }
                    else if (curID == "write")
                    {
                        tokens.push_back(write);
                    }
                    else
                    {
                        tokens.push_back(id);
                    }

                    counter--;
                }
                else
                {
                    tokens.push_back(error);
                    return tokens;
                }
        }
        counter++;
    }

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

