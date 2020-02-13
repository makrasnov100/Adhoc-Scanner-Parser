#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

enum MsgType {Info,Warning,Error,Success};

class Parser
{
private:
	int level;
	bool showParseWarnings;

public:

    Parser(bool showParseWarnings);

	void PerformParse(std::vector <TokenType> programText);

	//Check for specific term types
	void Parser::ProccessProgram(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessStmtList(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessStmt(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessExpr(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessTermTail(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessTerm(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessFactorTail(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessFactor(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessAddOp(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessMultOp(int& idx, std::vector<TokenType>& tokens);
	void Parser::ProccessEnd(int& idx, std::vector<TokenType>& tokens);

	//Console Utilities
	void Parser::PreExitMessage(MsgType type, std::string msg);
};

#endif
