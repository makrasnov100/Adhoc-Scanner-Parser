#include "Token.h"
#include "Parser.h"
#include <vector>
#include <iostream>

Parser::Parser(bool showParseWarnings)
{
	level = 0;
	this->showParseWarnings = showParseWarnings;
}

void Parser::PerformParse(std::vector<TokenType> tokens)
{
	if (tokens[tokens.size() - 1] == error)
		std::cout << "[ERROR] Parser WILL fail since scanner found a lexigraphical error [ERROR]" << std::endl;

	int idx = 0; //start index

	//Begin proccesing program recursively
	ProccessProgram(idx, tokens);

	if (tokens[tokens.size() - 1] == error)
		std::cout << "[ERROR] Parser SHOULD HAVE failed since scanner found a lexigraphical error [ERROR]" << std::endl;
}

//Root Proccessing (Every function results in idx equaling -1 if not a match) 
void Parser::ProccessProgram(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	ProccessStmtList(idx, tokens);
	if (idx != -1)
	{
		ProccessEnd(idx, tokens);
		if (idx != -1)
		{
			PreExitMessage(Success, "Program parser has completed work without errors!");
			return;
		}
	}
	
	PreExitMessage(Error, "Program parser has encountered syntax errors!");
	idx = -1;
}

void Parser::ProccessStmtList(int& idx,  std::vector<TokenType>& tokens)
{
	level++;
	int startIdx = idx;

	ProccessStmt(idx, tokens);
	if (idx != -1)
	{
		ProccessStmtList(idx, tokens);
		if (idx != -1)
		{
			PreExitMessage(Info, "Matched - Stmt_List");
			return;
		}
	}
	else
	{
		PreExitMessage(Info, "Matched - Empty Stmt_List");
		idx = startIdx;
		return;
	}

	PreExitMessage(Warning, "Failed to match Stmt_List");
	idx = -1;
}

void Parser::ProccessStmt(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	int startIdx = idx;
	if (tokens[idx] == id)
	{
		idx++;

		if (tokens[idx] == assign)
		{
			idx++;

			ProccessExpr(idx, tokens);
			if (idx != -1)
			{
				PreExitMessage(Info, "Matched - Stmt");
				return;
			}
		}
	}
	idx = startIdx;


	if (tokens[idx] == read)
	{
		idx++;

		if (tokens[idx] == id)
		{
			idx++;
			PreExitMessage(Info, "Matched - Stmt");
			return;
		}
	}
	idx = startIdx;


	if (tokens[idx] == write)
	{
		idx++;

		ProccessExpr(idx, tokens);
		if (idx != -1)
		{
			PreExitMessage(Info, "Matched - Stmt");
			return;
		}
	}

	PreExitMessage(Warning, "Failed to match Stmt");
	idx = -1;
}

void Parser::ProccessExpr(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	ProccessTerm(idx, tokens);
	if (idx != -1)
	{
		ProccessTermTail(idx, tokens);
		if (idx != -1)
		{
			PreExitMessage(Info, "Matched - Expr");
			return;
		}
	}

	PreExitMessage(Warning, "Failed to match Expr");
	idx = -1;
}

void Parser::ProccessTermTail(int& idx, std::vector<TokenType>& tokens)
{
	level++;
	int startIdx = idx;

	ProccessAddOp(idx, tokens);
	if (idx != -1)
	{
		ProccessTerm(idx, tokens);
		if (idx != -1)
		{
			ProccessTermTail(idx, tokens);
			if (idx != -1)
			{
				PreExitMessage(Info, "Matched - TermTail");
				return;
			}
		}
	}
	else
	{
		idx = startIdx;
		PreExitMessage(Info, "Matched - Empty TermTail");
		return;
	}

	PreExitMessage(Warning, "Failed to match TermTail");
	idx = -1;
}

void Parser::ProccessTerm(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	ProccessFactor(idx, tokens);
	if (idx != -1)
	{
		ProccessFactorTail(idx, tokens);
		if (idx != -1)
		{
			PreExitMessage(Info, "Matched - Term");
			return;
		}
	}

	PreExitMessage(Warning, "Failed to match Term");
	idx = -1;
}

void Parser::ProccessFactorTail(int& idx, std::vector<TokenType>& tokens)
{
	level++;
	int startIdx = idx;

	ProccessMultOp(idx, tokens);
	if (idx != -1)
	{
		ProccessFactor(idx, tokens);
		if (idx != -1)
		{
			ProccessFactorTail(idx, tokens);
			if (idx != -1)
			{
				PreExitMessage(Info, "Matched - FactorTail");
				return;
			}
		}
	}
	else
	{
		idx = startIdx;
		PreExitMessage(Info, "Matched - Empty FactorTail");
		return;
	}

	PreExitMessage(Warning, "Failed to match FactorTail");
	idx = -1;
}

void Parser::ProccessFactor(int& idx, std::vector<TokenType>& tokens) 
{
	level++;
	int startIdx = idx;

	if (tokens[idx] == lparen)
	{
		idx++;

		ProccessExpr(idx, tokens);
		if (idx != -1)
		{
			if (tokens[idx] == rparen)
			{
				idx++;
				PreExitMessage(Info, "Matched - Factor");
				return;
			}
		}
	}
	idx = startIdx;

	if (tokens[idx] == id)
	{
		idx++;
		PreExitMessage(Info, "Matched - Factor");
		return;
	}
	idx = startIdx;

	if (tokens[idx] == number)
	{
		idx++;
		PreExitMessage(Info, "Matched - Factor");
		return;
	}
	
	PreExitMessage(Warning, "Failed to match Factor");
	idx = -1;
}

void Parser::ProccessAddOp(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	if (tokens[idx] == plus || tokens[idx] == minus)
	{
		idx++;
		PreExitMessage(Info, "Matched - AddOp");
		return;
	}

	PreExitMessage(Warning, "Failed to match AddOp");
	idx = -1;
}

void Parser::ProccessMultOp(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	if (tokens[idx] == times || tokens[idx] == division)
	{
		idx++;
		PreExitMessage(Info, "Matched - MultOp");
		return;
	}

	PreExitMessage(Warning, "Failed to match MultOp");
	idx = -1;
}

void Parser::ProccessEnd(int& idx, std::vector<TokenType>& tokens)
{
	level++;

	if (tokens[idx] == end)
	{
		idx++;
		PreExitMessage(Info, "Matched - End");
		return;
	}

	PreExitMessage(Warning, "Failed to match End");
	idx = -1;
}

//Console Utility
void Parser::PreExitMessage(MsgType type, std::string msg)
{
	level--;

	if (!showParseWarnings && type == Warning)
		return;

	std::cout << std::string(level*2, ' ') << msg << std::endl;
}