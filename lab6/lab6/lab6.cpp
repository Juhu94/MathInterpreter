// lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "MathInterpreter.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{

	MathInterpreter mi(std::cout);
	
	//Test av is_variable();
	/*std::string str;
	while (true) {
		cin >> str;	
		//std::regex reg("[a-zA-z] [a-zA-z0-9]*");		
		//bool match = regex_match(str, reg);
		//cout << (match ? "Matched" : "Not matched") << endl << endl;
		for (int i = 0; i < str.length(); i++) {
			if (isalpha(str[i])) {
				cout << "DEN KAN GE DIG FAN PÅ";
			}
		}
	}*/

	
	//Test av is_int();
	
	/*std::string str;
	while (true) {
		cin >> str;
		std::regex reg("-?[0-9]+");
		bool match = regex_match(str, reg);
		cout << (match ? "Matched" : "Not matched") << endl << endl;
	}*/
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
