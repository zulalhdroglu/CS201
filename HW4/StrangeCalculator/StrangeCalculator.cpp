#include "StrangeCalculator.h"
#include <algorithm>
#include <string>


string infix2prefix(const string exp) {
    StrangeCalculator operators;
    StrangeCalculator operands;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            operators.push(exp[i]);
        }
        else if (exp[i] == ')') {
            operators.getTop();
            while (operators.isEmpty() == false && operators.getTop() != '(') {

                string operator1 = operands.getOperand();
                operands.popOperand();

                string operator2 = operands.getOperand();
                operands.popOperand();

                char operat = operators.getTop();
                operators.pop();

                string newTop =operat+ operator2+operator1;
                operands.pushOperand(newTop);
            }
            operators.pop();
        }
        else if (exp[i] >= '0' && exp[i] <= '9') {
            operands.pushOperand(string(1,exp[i]));
        }
        else if(exp[i]== '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/')  {
            if (!operators.isEmpty()) {
                while (!operators.isEmpty() && presedence(exp[i]) <= presedence(operators.getTop())) {
                    string operator1 = operands.getOperand();
                    operands.popOperand();

                    string operator2 = operands.getOperand();
                    operands.popOperand();

                    char operat = operators.getTop();
                    operators.pop();

                    string tmp = operat + operator2 + operator1;
                    operands.pushOperand(tmp);
                }
                operators.push(exp[i]);
            }
            else if(operators.isEmpty())
                operators.push(exp[i]);
        }
    }
    while (operators.isEmpty() == false) {
        string operator1 = operands.getOperand();
        operands.popOperand();

        string operator2 = operands.getOperand();
        operands.popOperand();

        char operat = operators.getTop();
        operators.pop();

        string tmp = operat + operator2 + operator1;
        operands.pushOperand(tmp);
    }
    return operands.getOperand();
}

double evaluatePrefix(const string exp) {
    StrangeCalculator sc;
    double constant = (double)'0';
    int check = exp.length() - 1;
    while (check >= 0) {
            if (exp[check] >= '0' && exp[check] <= '9') {
                double temp = (double)exp[check] - constant;
                sc.pushIntStack(temp);
                check--;
            }
            else if (exp[check] == '*') {
                double o1, o, newO;
                o = sc.getIntStack();
                sc.popIntStack();
                o1 = sc.getIntStack();
                sc.popIntStack();
                newO = o1 * o;
                sc.pushIntStack(newO);
                check--;
            }
            else if (exp[check] == '+') {
                double o1, o, newO;

                o = sc.getIntStack();
                sc.popIntStack();
                o1 = sc.getIntStack();
                sc.popIntStack();
                newO = o1 + o;
                sc.pushIntStack(newO);
                check--;
            }
            else if (exp[check] == '/') {
                double o1, o, newO;

                o = sc.getIntStack();
                sc.popIntStack();
                o1 = sc.getIntStack();
                sc.popIntStack();
                newO = o / o1;
                sc.pushIntStack(newO);
                check--;

            }
            else if (exp[check] == '-') {
                double o1, o, newO;

                o = sc.getIntStack();
                sc.popIntStack();

                o1 = sc.getIntStack();
                sc.popIntStack();
                newO = o - o1;
                sc.pushIntStack(newO);
                check--;
            }
        }
    return sc.getIntStack();
}
bool isBalancedInfix(const string exp) {
    StrangeCalculator sc;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            sc.push(exp[i]);
        }
        if (exp[i] == ')') {
            if (sc.isEmpty()) {
                return false;
            }
            else
                sc.pop();
        }
    }
    return sc.isEmpty();
}
void evaluateInputPrefixExpression() {
    StrangeCalculator spaceCheck;
    StrangeCalculator noSpace;
    cout << "Please enter infix input: ";
    string input;
    getline(cin, input);
    input.append(" ", input.length());
    for (int i = 0; i <= input.length()-1; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            noSpace.push(input[i]);
        }
        else if (input[i] == '*' || input[i] == '-' || input[i] == '+' || input[i] == '/') {
            noSpace.push(input[i]);
        }
    }
    string newInput = "";
    while (!noSpace.isEmpty()) {
        newInput = noSpace.getTop() + newInput;
        noSpace.pop();
    }
    cout << "The input without spaces: " << newInput << endl;

    int i = 0;
    while (i <= newInput.length() - 1) {
        spaceCheck.push(newInput[i]);
        i++;
    }
    string in = "";

    if (spaceCheck.isEmpty()) {
        cout << "It is not a valid expression!";
    }
    else {
        while (!spaceCheck.isEmpty()) {
            in = spaceCheck.getTop() + in;
            spaceCheck.pop();
            
        }
        if (isBalancedInfix(input)) {
            cout << "The prefix of " << in << " is " << infix2prefix(in) << endl;
            cout << "The result of " << in << " is " << evaluatePrefix(infix2prefix(in)) << endl;
        }
        else {
            cout << "The input it not balanced!";
            return;
        }
    }

}

int presedence(char alpha){
    if (alpha == '+' || alpha == '-')
    {
        return(1);
    }
    if (alpha == '*' || alpha == '/')
    {
        return(2);
    }
    return 0;
}

StrangeCalculator::StrangeCalculator() : operandPtr(NULL), topPtr(NULL),inputPtr(NULL) {

}

StrangeCalculator::StrangeCalculator(const StrangeCalculator& aStack) {

    if (aStack.topPtr == NULL) {
        topPtr = NULL;  // original stack is empty
    }
    else {
        // copy first node
        topPtr = new CalculatorNode;
        topPtr->calOperator = aStack.topPtr->calOperator;

        // copy rest of stack
        CalculatorNode* newPtr = topPtr;
        for (CalculatorNode* origPtr = aStack.topPtr->next;
            origPtr != NULL;
            origPtr = origPtr->next) {
            newPtr->next = new CalculatorNode;
            newPtr = newPtr->next;
            newPtr->calOperator = origPtr->calOperator;
        }
        newPtr->next = NULL;
    }
    if (aStack.operandPtr == NULL) {
        operandPtr = NULL;  // original stack is empty
    }
    else {
        // copy first node
        operandPtr = new OperandNode;
        operandPtr->operandStack = aStack.operandPtr->operandStack;

        // copy rest of stack
        OperandNode* newPtr1 = operandPtr;
        for (OperandNode* origPtr1 = aStack.operandPtr->next;
            origPtr1 != NULL;
            origPtr1 = origPtr1->next) {
            newPtr1->next = new OperandNode;
            newPtr1 = operandPtr->next;
            newPtr1->operandStack = origPtr1->operandStack;
        }
        newPtr1->next = NULL;
    }

    if (aStack.inputPtr == NULL) {
        inputPtr = NULL;  // original stack is empty
    }
    else {
        // copy first node
        inputPtr = new IntNode;
        inputPtr->input = aStack.inputPtr->input;

        // copy rest of stack
        IntNode* newPtr2 = inputPtr;
        for (IntNode* origPtr2 = aStack.inputPtr->next;
            origPtr2 != NULL;
            origPtr2 = origPtr2->next) {
            newPtr2->next = new IntNode;
            newPtr2 = inputPtr->next;
            newPtr2->input = origPtr2->input;
        }
        newPtr2->next = NULL;
    }

}
StrangeCalculator::~StrangeCalculator() {

    // pop until stack is empty
    while (!isEmptyOperandStack())
        popOperand();
    while (!isEmpty())
        pop();
    while (!isEmptyIntStack())
        popIntStack();

}
bool StrangeCalculator::isEmptyOperandStack() const {
    return operandPtr == NULL;
}
bool StrangeCalculator::pushOperand(string newItem) {

    // create a new node
    OperandNode* newPtr = new OperandNode;

    // set data portion  of new node
    newPtr->operandStack = newItem;

    // insert the new node
    newPtr->next = operandPtr;
    operandPtr = newPtr;
    return true;
}
bool StrangeCalculator::popOperand() {

    if (isEmptyOperandStack())
        return false;

    // stack is not empty; delete top
    else {
        OperandNode* temp = operandPtr;
        operandPtr = operandPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
bool StrangeCalculator::popOperand(string& stackTop) {

    if (isEmptyOperandStack())
        return false;

    // not empty; retrieve and delete top 
    else {
        stackTop = operandPtr->operandStack;
        OperandNode* temp = operandPtr;
        operandPtr = operandPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
string StrangeCalculator::getOperand()const {

    //if (isEmptyOperandStack())
    //    return NULL;
    //else {
    string stackTop = operandPtr->operandStack;
    return stackTop;
    //}
}
bool StrangeCalculator::isEmpty() const {
    return topPtr == NULL;
}
bool StrangeCalculator::push(char newItem) {

    // create a new node
    CalculatorNode* newPtr = new CalculatorNode;

    // set data portion  of new node
    newPtr->calOperator = newItem;

    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;
    return true;
}
bool StrangeCalculator::pop() {

    if (isEmpty())
        return false;

    // stack is not empty; delete top
    else {
        CalculatorNode* temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
bool StrangeCalculator::pop(char& stackTop) {

    if (isEmpty())
        return false;

    // not empty; retrieve and delete top 
    else {
        stackTop = topPtr->calOperator;
        CalculatorNode* temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
char StrangeCalculator::getTop()const {

    if (isEmpty())
        return false;
    else {
        char stackTop = topPtr->calOperator;
        return stackTop;
    }
}

bool StrangeCalculator::isEmptyIntStack() const {
    return inputPtr == NULL;
}
bool StrangeCalculator::pushIntStack(double newItem) {

    // create a new node
    IntNode* newPtr = new IntNode;

    // set data portion  of new node
    newPtr->input = newItem;

    // insert the new node
    newPtr->next = inputPtr;
    inputPtr = newPtr;
    return true;
}
bool StrangeCalculator::popIntStack() {

    if (isEmptyIntStack())
        return false;

    // stack is not empty; delete top
    else {
        IntNode* temp = inputPtr;
        inputPtr = inputPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
bool StrangeCalculator::popIntStack(double& stackTop) {

    if (isEmptyIntStack())
        return false;

    // not empty; retrieve and delete top 
    else {
        stackTop = inputPtr->input;
        IntNode* temp = inputPtr;
        inputPtr = inputPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}
double StrangeCalculator::getIntStack()const {
    //if (isEmptyOperandStack())
    //    return NULL;
    //else {
        double stackTop = inputPtr->input;
        return stackTop;
    //}
}


