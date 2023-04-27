#include <iostream>
#include <string>
#include <vector>
#include <math.h>

enum associativity{
    left,
    right
};

int getAssociativity(char op){
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

int getPrecedence(char op){
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



template<typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> v){
    for (T e : v)
    {
        o << e << " ";
    }

    return o;
}

std::vector<std::string> exprToRPN(std::string expression){
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
            /*
                    while (
            there is an operator o2 at the top of the operator stack which is not a left parenthesis, 
            and (o2 has greater precedence than o1 or (o1 and o2 have the same precedence and o1 is left-associative))
            ):
                pop o2 from the operator stack into the output queue
            push o1 onto the operator stack
            */
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


bool isNumber(std::string s, double &res){
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

double solveRPN(std::vector<std::string> rpnExpression){
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

int main(){
    std::string input;

    std::getline(std::cin >> std::ws,input);

    std::vector<std::string> rpnExpression = exprToRPN(input);

    std::cout << "Input: " << input << std::endl;
    std::cout << "RPN expression: " << rpnExpression << std::endl;
    std::cout << "Result: " << solveRPN(rpnExpression) << std::endl;



    return 0;
}