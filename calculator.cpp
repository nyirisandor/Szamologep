#include "calculator.h"


int calculator::getAssociativity(char op){
    switch (op)
    {
    case '+':
        return associativity::left;
    case '-':
        return associativity::left;
    case '/':
        return associativity::left;
    case '*':
        return associativity::left;
    case '%':
        return associativity::left;
    case '^':
        return associativity::right;
    
    default:
        return associativity::left;
    }
}

int calculator::getPrecedence(char op){
    switch (op)
    {
    case '+':
        return 2;
    case '-':
        return 2;
    case '/':
        return 3;
    case '*':
        return 3;
    case '%':
        return 3;
    case '^':
        return 4;
    
    default:
        return 0;
    }
}


std::vector<std::string> calculator::exprToRPN(std::string expression){
    std::vector<std::string> output = {""};
    std::vector<std::string> operatorStack;

    while (expression.length() > 0)
    {
        if(expression[0] == ' '){ //if the token is a whitespace
            
        }
        else if(expression[0] == '('){
            operatorStack.emplace_back("(");
        }
        else if(expression[0] == ')'){
            while (operatorStack.back() != "(")
            {
                output.emplace_back(operatorStack.back());
                operatorStack.pop_back();
            }
            operatorStack.pop_back();
            
        }
        else if(isdigit(expression[0]) || output.back() == "" || expression[0] == '.'){ // if token is a part of the number
            output.back() +=expression[0];
        }
        else{ //if token is operator
            char op = expression.at(0);

           while(operatorStack.size() > 0 &&operatorStack.back() != "(" && (getPrecedence(operatorStack.back()[0]) > getPrecedence(op) || (getPrecedence(operatorStack.back()[0]) == getPrecedence(op) && getAssociativity(op) == associativity::left))){
                output.emplace_back(operatorStack.back());
                operatorStack.pop_back();
           }


            operatorStack.emplace_back("");
            operatorStack.back() += op;
            output.emplace_back("");
        }

        expression.erase(0,1);
        
    }

    while(operatorStack.size() > 0)
    {
        output.emplace_back(operatorStack.back());
        operatorStack.pop_back();
    }
    
    



    return output;
}


bool calculator::isNumber(std::string s, double &res){
    try
    {
        res = std::stod(s);
        return true;
    }
    catch(const std::exception& e)
    {
        return false;
    }
    
}

double calculator::solveRPN(std::vector<std::string> rpnExpression){
    std::vector<double> stack;
    double num;
    for(std::string e: rpnExpression)
    {
        if(isNumber(e,num)){
            stack.emplace_back(num);
        }
        else{
            double rightNum = stack.back();
            stack.pop_back();
            double leftNum = stack.back();
            stack.pop_back();
            if(e == "+"){
                stack.push_back(leftNum + rightNum);
            }
            else if(e == "-"){
                stack.push_back(leftNum - rightNum);
            }
            else if(e == "/"){
                stack.push_back(leftNum / rightNum);
            }
            else if(e == "*"){
                stack.push_back(leftNum * rightNum);
            }
            else if(e == "%"){
                stack.push_back((int)leftNum%(int)rightNum);
            }
            else if(e == "^"){
                stack.push_back(pow(leftNum,rightNum));
            }
        }
    }
    

    return stack.at(0);
}