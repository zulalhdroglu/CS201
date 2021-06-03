#include<iostream>
#include<string>
#include <algorithm>

using namespace std;
string infix2prefix(const string exp);
double evaluatePrefix(const string exp);
bool isBalancedInfix(const string exp);
void evaluateInputPrefixExpression();

int presedence(char alpha);
class StrangeCalculator {
public:
	StrangeCalculator();
	StrangeCalculator(const StrangeCalculator& aStack);
	~StrangeCalculator();

	bool isEmptyOperandStack() const;
	bool pushOperand(string  newItem);
	bool popOperand();
	bool popOperand(string& stackTop);
	string getOperand() const;


	bool isEmpty() const;
	bool push(char  newItem);
	bool pop();
	bool pop(char& stackTop);
	char getTop() const;

	bool isEmptyIntStack() const;
	bool pushIntStack(double  newItem);
	bool popIntStack();
	bool popIntStack(double& stackTop);
	double getIntStack() const;

private:
	struct OperandNode {            // a node on the stack
		string operandStack;        // a data item on the stack
		OperandNode* next;        // pointer to next node
	};
	struct CalculatorNode {            // a node on the stack
		char calOperator;        // a data item on the stack
		CalculatorNode* next;        // pointer to next node
	};
	struct IntNode {            // a node on the stack
		double input;        // a data item on the stack
		IntNode* next;        // pointer to next node
	};
	OperandNode* operandPtr;     // pointer to first node in the stack
	CalculatorNode* topPtr;
	IntNode* inputPtr;
};
