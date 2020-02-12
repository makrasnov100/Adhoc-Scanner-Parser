#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

enum ContextFreeGrammarTerms {program, stmt_list, stmt, expr, term_tail, term, factor_tail, factor, add_op, mult_op};

class Parser
{
public:
    Parser();

	std::vector<ContextFreeGrammarTerms> PerformParse(std::vector <TokenType> programText);

	//Check for specific term types

};

#endif
