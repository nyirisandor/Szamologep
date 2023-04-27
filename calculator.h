#pragma once

#include <string>
#include <vector>
#include <math.h>



namespace calculator{

    enum associativity{
        left,
        right
    };

    int getAssociativity(char op);

    int getPrecedence(char op);

    std::vector<std::string> exprToRPN(std::string expression);

    bool isNumber(std::string s, double &res);

    double solveRPN(std::vector<std::string> rpnExpression);
}
