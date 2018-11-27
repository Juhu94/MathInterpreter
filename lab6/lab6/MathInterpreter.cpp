#include "pch.h"
#include "MathInterpreter.h"
#include <string>
#include <regex>
#include <iostream>
#include <fstream>

using namespace std;

MathInterpreter::MathInterpreter(std::ostream& out_stream)
{
	tokens = {"print","2","*","(","3","+","2",")", };

	//Before submitting code to evaluate , it has to be tokenized	
	//– i.e. broken down to a sequence of strings representing code elements (numbers, variables, operators etc).
	//Start by splitting the code into lines, and then into tokens using whitespace as a separator.

	//Läs från fil, Taget från lab3
	/*string line;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			while (line.length() == 0 && getline(myfile, line))
				;
			string name(line);
			string adress;
			getline(myfile, adress);
			reg.LäggTill(&Person(name, adress));
		}
		myfile.close();
		return true;
	}
	else {
		cout << "Unable to open file";
		return false;
	}*/


	evaluate(tokens);
}
void MathInterpreter::evaluate(const std::vector<std::string>& tokens)
{
	cout << "evaluate\n";
	parse_Stmt();
}
//Stmt:= ConfigStmt | AssgStmt | PrintStmt
void MathInterpreter::parse_Stmt()
{
	std::string next_token = peek();
	if (next_token == "config") {
		cout << "config\n";
		consume("config");
		parse_ConfigStmt();

	}
	else if (next_token == "print") {
		cout << "print\n";
		consume("print");
		parse_PrintStmt();
	}
	else if (is_variable(next_token)) {
		cout << "variable\n";
		consume(next_token);
		//Skapa en variable och sen ge den värdet av MathExp(); ???

	}
}

//ConfigStmt := "config" [ "dec" | "hex" | "bin” ] 
void MathInterpreter::parse_ConfigStmt() 
{
	bool result;
	std::string next_token = peek();
	if (next_token == "dec") {
		consume("dec");
		//Ställ in utskriften till dec
	}
	else if (next_token == "hex") {
		consume("hex");
		//Ställ in utskriften till hex
	}
	else if (next_token == "bin") {
		consume("bin");
		//Ställ in utskriften till bin
	}
}
//AssgStmt := Variable "=" MathExp
void MathInterpreter::parse_AssStmt() 
{

}
//PrintStmt := "print" MathExp 
void MathInterpreter::parse_PrintStmt() 
{
	int sum = parse_MathExp();
	cout << "sum = " << sum << "\n";
}

//MathExp := SumExp
int MathInterpreter::parse_MathExp()
{
	cout << "parse_MathExp\n";
	return parse_SumExp();
}
//SumExp := ProductExp [ "+" ProductExp | "–" ProductExp ]*
int MathInterpreter::parse_SumExp()
{
	cout << "parse_SumExp\n";
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
	cout << "parse_ProductExcp\n";
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
	cout << "parse_PrimaryExp\n";
	int value;
	std::string next_token = peek();
	//Int
	if (is_int(next_token)) {
		value = std::stoi(next_token);
		consume(next_token);
	}
	//Variable
	else if (is_variable(next_token)) {
		value = std::stoi(next_token);
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
		throw std::runtime_error("Expected int or ( ) ");

	return value;
}

void MathInterpreter::consume(const std::string & token)
{
	cout << "consume\n";
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
	cout << "is_variable\n";
	for (int i = 0; i < token.length(); i++) {
		if (isalpha(token[i])) {
			return true;
		}
		else
			return false;
	}
	/*std::regex reg("[a-zA-z] [a-zA-z0-9]*");
	if (std::regex_match(token, reg))
		return true;
	else
		return false;
	*/
}


MathInterpreter::~MathInterpreter()
{

}
