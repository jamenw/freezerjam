/*---------------------------------------
Andrey Akhmedov - DEMO USE ONLY
CS 2420 - Fall 2013
TR 11:30 - 1:30
Assignment 1 - Stacks
-----------------------------------------*/

#include <iostream> 
#include <string> 
#include <stack> 
#include <sstream> 
#include <algorithm>  
#include <functional>  
#include <cctype> 
#include <locale> 


using namespace std;
//checks to see if it's a digit, but first checks if it's in range (if(n >= digit.size()) because of the peeking feature I built in down there. 
bool isDigit(const string& digit, const size_t& n) {
	if (n >= digit.size()) {
		return false;
	}
	else if (digit.at(n) >= 48 && digit.at(n) <= 57) {
		return true;
	}
	else return false;
}
//checks to see if character passed in is an operator 
bool isOperator(const string& oper, const size_t& n) {
	if (oper.at(n) >= 40 && oper.at(n) <= 43 || oper.at(n) == 45 || oper.at(n) == 47 || oper.at(n) == 94){
		return true;
	}
	else return false;
}
//just checks for precedence, I see a lot of students assigning the variables number values now. Both methods work 
bool greaterOrEqualPrecedence(const string& oper1, const stack<string>& t) {
	if (t.empty()) {
		return true;
	}
	if (t.top() != "(") {

		if (oper1.at(0) == 94 && t.top() != "^") {
			return true;
		}
		else if ((oper1.at(0) == 42 || oper1.at(0) == 47) && (t.top() == "+" || t.top() == "-")) {
			return true;
		}
		else if ((oper1.at(0) == 43 || oper1.at(0) == 45) && (t.top() == "+" || t.top() == "-")) {
			return true;
		}
		else return false;
	}
	else return true;
}

string convertInfxToPfx(const string& infx) {
	//********************************************************************************************************************* 
	//initialize all the variables to use for this function 
	string pfx = "";
	stack<string> s;
	string sym = "";
	int check = 0; //used to check for recent parenthesis 
	//********************************************************************************************************************* 

	for (size_t p = 0; p < infx.size(); p++) {    //this just loops through the entire expression, checking each value 
		sym += infx.at(p);
		//********************************************************************************************************************* 
		//this obviously checks for if the character is a digit and will peek ahead to see if it needs to place a space or not 
		if (isDigit(infx, p)) {
			if (isDigit(infx, p + 1)) {
				pfx += infx.at(p);
			}
			else {
				pfx += infx.at(p);
				pfx += 32; //ASCII 32 = space 
			}
		}
		//********************************************************************************************************************* 
		//this does all of the operator work and figures out precedence and using the stack 
		else if (isOperator(infx, p)) {
			if (infx.at(p) == 40) { //ASCII 40 = ( 
				s.push(sym);
			}
			else if (infx.at(p) == 42 || infx.at(p) == 43 || infx.at(p) == 45 || infx.at(p) == 47 || infx.at(p) == 94) { //ASCII 42, 43, 45, 47, 94 = *, +, -, /, ^ 
				if (greaterOrEqualPrecedence(sym, s)) {
					s.push(sym);
				}
				else {
					pfx += s.top();
					pfx += 32;
					s.pop();
					s.push(sym);
				}
			}
			else if (infx.at(p) == 41) { //ASCII 41 = ) 
				sym = s.top();
				if (sym.at(0) != 40) {
					pfx += s.top();
					pfx += 32;
					s.pop();
					do {
						if (s.top() == "(") {
							s.pop();
							check = 1;
						}
						else if (s.empty()) {
							check = 1;
						}
						else {
							pfx += s.top();
							pfx += 32;
							s.pop();
							check = 0;
						}
					} while (check == 0);
				}
				else {
					s.pop();
				}
			}
		}
		sym.clear();
	}
	//******************************************************************************************* 
	//this will clear the remaining items in stack after the expression has been run through 
	if (!s.empty()) {
		while (!s.empty()) {
			sym = s.top();
			if (sym.at(0) != 40) {
				pfx += s.top();
				pfx += 32;
				s.pop();
			}
			else { s.pop(); }
		}
	}
	//******************************************************************************************* 
	check = 0;
	return pfx;
}

//This helps with testing, do not modify. 
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

	//get rid of spaces 
	whatItIs.erase(whatItIs.begin(), std::find_if(whatItIs.begin(), whatItIs.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	whatItIs.erase(std::find_if(whatItIs.rbegin(), whatItIs.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), whatItIs.end());

	if (whatItShouldBe == whatItIs) {
		cout << "Passed test " << testName << " ***  Output was \"" << whatItIs << "\"" << endl;
		return true;
	}
	else {
		if (whatItShouldBe == "") {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \"" << whatItIs << "\"" << endl << "  Output should have been blank. " << endl;
		}
		else {
			cout << "***Failed test " << testName << " *** " << endl << "   Output was \"" << whatItIs << "\"" << endl << "  Output should have been \"" << whatItShouldBe << "\"" << endl;
		}
		return false;
	}
}

int main() {

	string expression = "(2+3)";
	string result = convertInfxToPfx(expression);
	checkTest("Test #1", "2 3 +", result);

	expression = "2+3";
	result = convertInfxToPfx(expression);
	checkTest("Test #2", "2 3 +", result);

	expression = "(123+456)";
	result = convertInfxToPfx(expression);
	checkTest("Test #3", "123 456 +", result);

	expression = "(8-5)";
	result = convertInfxToPfx(expression);
	checkTest("Test #4", "8 5 -", result);

	expression = "((3-4)-5)";
	result = convertInfxToPfx(expression);
	checkTest("Test #5", "3 4 - 5 -", result);

	expression = "(3 - (4 - 5))";
	result = convertInfxToPfx(expression);
	checkTest("Test #6", "3 4 5 - -", result);

	expression = "(3*(8/2))";
	result = convertInfxToPfx(expression);
	checkTest("Test #7", "3 8 2 / *", result);

	expression = "3 + 8 / 2";
	result = convertInfxToPfx(expression);
	checkTest("Test #8", "3 8 2 / +", result);

	expression = "24 / 3 + 2";
	result = convertInfxToPfx(expression);
	checkTest("Test #9", "24 3 / 2 +", result);

	expression = "((1 + 2) * (3 + 4))";
	result = convertInfxToPfx(expression);
	checkTest("Test #10", "1 2 + 3 4 + *", result);

	expression = "2^3";
	result = convertInfxToPfx(expression);
	checkTest("Test #11", "2 3 ^", result);

	expression = "8 + 3^4";
	result = convertInfxToPfx(expression);
	checkTest("Test #12", "8 3 4 ^ +", result);

	expression = "(((3+12)-7)*120)/(2+3)";
	result = convertInfxToPfx(expression);
	checkTest("Test #13", "3 12 + 7 - 120 * 2 3 + /", result);

	expression = "((((9+(2*(110-(20/2))))*8)+1000)/2)-((400*2500)-1000001)";
	result = convertInfxToPfx(expression);
	checkTest("Test #14", "9 2 110 20 2 / - * + 8 * 1000 + 2 / 400 2500 * 1000001 - -", result);

	//A few extra expressions I made myself, it definitely helped reinforce the entire project by finding my own expressions. Just comment out to try! 
	/*expression = "((9+((7+4+2)-6)/2)+3)";
	result = convertInfxToPfx(expression);
	checkTest("Test #15", "9 7 4 2 + + 6 - 2 / + 3 +", result);

	expression = "((((4^5)+20)-14)+(7/10))+((3/9)*(21^5))";
	result = convertInfxToPfx(expression);
	checkTest("Test #16", "4 5 ^ 20 + 14 - 7 10 / + 3 9 / 21 5 ^ * +", result);*/

	system("pause");
	return 0;
}