#pragma once
#include<vector>


class MathInterpreter
{

private:
	std::vector<std::string> tokens;
	int position = 0;
	const std::string ETX = "\u0003";

	void evaluate(const std::vector<std::string>& tokens);

	void parse_Stmt();

	void parse_ConfigStmt();
	void parse_AssStmt();
	void parse_PrintStmt();

	int parse_MathExp();
	int parse_SumExp();
	int parse_ProductExp();
	int parse_PrimaryExp();

	void consume(const std::string& token);
	std::string peek();
	std::string peek(int steps);
	bool is_int(const std::string& token);
	bool is_variable(const std::string& token);

public:
	MathInterpreter(std::ostream& out_stream);
	MathInterpreter(std::vector<std::string>& tokens);
	~MathInterpreter();
};

