#include "pch.h"
#include "MathInterpreter.h"
#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <map>
#include <bitset>

using namespace std;

MathInterpreter::MathInterpreter(std::ostream& out_stream)
{
	
	//Before submitting code to evaluate , it has to be tokenized	
	//– i.e. broken down to a sequence of strings representing code elements (numbers, variables, operators etc).
	//Start by splitting the code into lines, and then into tokens using whitespace as a separator.

	string line;
	ifstream myfile("math_test.txt");
	if (myfile.is_open()) {
		while (!myfile.eof())
		{
			getline(myfile, line);
			tokens = splitString(line);
			evaluate(tokens);
			position = 0;
		}
		myfile.close();
	}
	else {
		throw std::runtime_error("Unable to open file\n");
	}
}

std::vector<std::string> MathInterpreter::splitString(std::string& line) {
	//cout << line << "\n";

	std::regex reg("\\s+");
	std::sregex_token_iterator iter(line.begin(), line.end(), reg, -1);
	std::sregex_token_iterator end;

	std::vector<std::string> vec(iter, end);
	return vec;
}

void MathInterpreter::evaluate(const std::vector<std::string>& tokens)
{
	//cout << "evaluate\n";
	parse_Stmt();
}

//Stmt:= ConfigStmt | AssgStmt | PrintStmt
void MathInterpreter::parse_Stmt()
{
	//cout << "parse_Stmt\n";
	std::string next_token = peek();
	if (next_token == "config") {
		consume(next_token);
		parse_ConfigStmt();

	}
	else if (next_token == "print") {
		consume(next_token);
		parse_PrintStmt();
	}
	else if (is_variable(next_token)) {
		parse_AssStmt();
	}
	else {
		throw std::runtime_error("Syntax error, Expected config, print or a variable");
	}
}

//ConfigStmt := "config" [ "dec" | "hex" | "bin” ] 
void MathInterpreter::parse_ConfigStmt() 
{
	std::string next_token = peek();
	if (next_token == "dec") {
		cout << std::dec;
		consume(next_token);
		//Ställ in utskriften till dec
	}
	else if (next_token == "hex") {
		cout << std::hex;
		consume(next_token);
		//Ställ in utskriften till hex
	}
	else if (next_token == "bin") {
		cout << std::bitset<32>();
		consume(next_token);
		//Ställ in utskriften till bin
	}
	else {
		throw std::runtime_error("Expected dec, hex, or bin as configuration");
	}
}

//AssgStmt := Variable "=" MathExp
void MathInterpreter::parse_AssStmt() 
{
	std::string val = peek();
	consume(val);
	std::string next_token = peek();
	if (next_token == "=") {
		consume(next_token);
		int sum = parse_MathExp();
		hashtable[val] = sum;
	}
	else {
		throw std::runtime_error("Expected = ");
	}
}
//PrintStmt := "print" MathExp 
void MathInterpreter::parse_PrintStmt() 
{
	int sum = parse_MathExp();
	cout << sum << "\n";
}

//MathExp := SumExp
int MathInterpreter::parse_MathExp()
{
	//cout << "parse_MathExp\n";
	return parse_SumExp();
}

//SumExp := ProductExp [ "+" ProductExp | "–" ProductExp ]*
int MathInterpreter::parse_SumExp()
{
	//cout << "parse_SumExp\n";
	int result = parse_ProductExp();

	std::string next_token = peek();
	while (1) {
		if (next_token == "+") {
			consume("+");
			result = (result + parse_ProductExp());
		}
		else if (next_token == "-") {
			consume("-");
			result = (result - parse_ProductExp());
		}
		else
			break;

		next_token = peek();
	}

	return result;
}
//ProductExp := PrimaryExp [ "*" PrimaryExp | "/" PrimaryExp ]*
int MathInterpreter::parse_ProductExp()
{
	//cout << "parse_ProductExcp\n";
	int result = parse_PrimaryExp();

	std::string next_token = peek();
	while (1) {
		if (next_token == "*") {
			consume("*");
			result = (result * parse_PrimaryExp());
		}
		else if (next_token == "/") {
			consume("/");
			result = (result / parse_PrimaryExp());
		}
		else
			break;

		next_token = peek();
	}

	return result;
}

//PrimaryExp := Int | Variable | ( MathExp )
int MathInterpreter::parse_PrimaryExp()
{
	//cout << "parse_PrimaryExp\n";
	int value;
	std::string next_token = peek();
	//Int
	if (is_int(next_token)) {
		value = std::stoi(next_token);
		consume(next_token);
	}
	//Variable
	else if (is_variable(next_token)) {
		auto it = hashtable.find(next_token);
		if (it != hashtable.end())
			value = it->second;
		consume(next_token);
	}
	//(MathExp)
	else if (next_token == "(") {
		consume("(");
		value = parse_MathExp();
		if (peek() == ")")
			consume(")");
		else
			throw std::runtime_error("Expected )\n");
	}
	//No valid PrimaryExp found, which is an error
	else
		throw std::runtime_error("Expected int or ( ) \n");

	return value;
}

void MathInterpreter::consume(const std::string & token)
{
	//cout << "consume\n";
	std::string next_token = peek();
	if (next_token == ETX)
		throw std::runtime_error("Consumed past last token\n");
	if (next_token != token)
		throw std::runtime_error("Could not consume token " + token + "\n");
	
	++position;
}

std::string MathInterpreter::peek()
{
	return peek(0);
}

std::string MathInterpreter::peek(int steps)
{
	if (position + steps >= tokens.size()) return ETX;
	
	return tokens[position + steps];
}

bool MathInterpreter::is_int(const std::string & token)
{
	std::regex reg("-?[0-9]+");
	if (std::regex_match(token, reg))
		return true;
	else
		return false;
}

bool MathInterpreter::is_variable(const std::string & token)
{
	//cout << "is_variable\n";
	for (int i = 0; i < token.length(); i++) {
		if (isalpha(token[i])) {
			return true;
		}
		else
			return false;
	}
}

MathInterpreter::~MathInterpreter()
{

}
