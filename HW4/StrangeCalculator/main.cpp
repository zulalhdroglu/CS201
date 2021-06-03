#include <iostream>
using namespace std;
#include "StrangeCalculator.h"

int main() {
	cout << "prefix of: 9+3 is: " << infix2prefix("9+3") << endl;
	cout << "prefix of: 9-3*5 is: " << infix2prefix("9-3*5") << endl;
	cout << "prefix of: 3+2-3/(7*2) is: " << infix2prefix("3+2-3/(7*2)") << endl;
	cout << "prefix of: (4+2)/(5/3) is: " << infix2prefix("(4+2)/(5/3)") << endl;
	cout << "prefix of: (8-6)/(3*4)+4+9/(3*6) is: " << infix2prefix("(8-6)/(3*4)+4+9/(3*6)") << endl;


	cout << "Checkpoint 1" << endl;
	cout << "result of: 9+3 is: " << evaluatePrefix(infix2prefix("9+3")) << endl;
	cout << "result of: 9-3*5 is: " << evaluatePrefix(infix2prefix("9-3*5")) << endl;
	cout << "result of: 3+2-3/(7*2) is: " << evaluatePrefix(infix2prefix("3+2-3/(7*2)")) << endl;
	cout << "result of: (4+2)/(5/3) is: " << evaluatePrefix(infix2prefix("(4+2)/(5/3)")) << endl;
	cout << "result of: (8-6)/(3*4)+4+9/(3*6) is: " << evaluatePrefix(infix2prefix("(8-6)/(3*4)+4+9/(3*6)")) << endl;

	cout << "Checkpoint 2" << endl;
	cout << isBalancedInfix("(((4+7()(") << endl;
	cout << isBalancedInfix("(()4+9/2)))") << endl;
	cout << isBalancedInfix("((5+)4(") << endl;
	cout << isBalancedInfix("((5+2)(*4/4*()3+8)") << endl;
	cout << isBalancedInfix("(((5+4)*3-3/(4+5)))") << endl;


	cout << "Checkpoint 3" << endl;
	evaluateInputPrefixExpression();
	evaluateInputPrefixExpression();


	return 0;
}