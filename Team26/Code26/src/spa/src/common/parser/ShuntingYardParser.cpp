#include "ShuntingYardParser.h"

std::shared_ptr<ShuntNode> ShuntingYardParser::parse(std::string expr) {
    std::stack<std::shared_ptr<ShuntNode>> result;
    std::stack<char> opStack;
    bool isPrevFactor = false;

    for (int i = 0; i < expr.size(); ++i) {
        const char c = expr[i];
        if (isspace(c)) {
            continue;
        } else if (std::isdigit(c)) /* constant */ {
            parseDigit(expr, i, isPrevFactor, result);
        } else if (std::isalpha(c)) /* variable */ {
            parseVariable(expr, i, isPrevFactor, result);
        } else if (isMathOp(c)) /* operator or bracket */ {
            parseOperatorOrBracket(c, opStack, isPrevFactor, result);
        } else {
            throw ShuntingYardParserException(
                    ParserShuntingYardParserUnknownOperatorExceptionMessage);
        }
    }

    while (!opStack.empty()) {
        processOperator(opStack, result);
    }

    if (result.size() != 1) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }

    return result.top();
}

std::shared_ptr<ShuntNode> ShuntingYardParser::parse(std::string expr,
                                                 const std::shared_ptr<std::unordered_set<std::string>>& exprVariables,
                                                 const std::shared_ptr<std::unordered_set<int>>& exprConstants) {
    std::stack<std::shared_ptr<ShuntNode>> result;
    std::stack<char> opStack;
    bool isPrevFactor = false;

    for (int i = 0; i < expr.size(); ++i) {
        const char c = expr[i];
        if (isspace(c)) {
            continue;
        } else if (std::isdigit(c)) /* constant */ {
            parseDigit(exprConstants, expr, i, isPrevFactor, result);
        } else if (std::isalpha(c)) /* variable */ {
            parseVariable(exprVariables, expr, i, isPrevFactor, result);
        } else if (isMathOp(c)) /* operator or bracket */ {
            parseOperatorOrBracket(c, opStack, isPrevFactor, result);
        } else {
            throw ShuntingYardParserException(
                    ParserShuntingYardParserUnknownOperatorExceptionMessage);
        }
    }

    while (!opStack.empty()) {
        processOperator(opStack, result);
    }

    if (result.size() != 1) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }

    return result.top();
}

void ShuntingYardParser::parseDigit(std::string expr, int& i, bool& isPrevFactor,
                                    std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (isPrevFactor) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }
    int k = i;
    while (k < expr.size() && std::isdigit(expr[k])) {
        ++k;
    }
    std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
    result.push(node);
    i = k - 1;
    isPrevFactor = true;
}

void ShuntingYardParser::parseVariable(std::string expr, int& i,
                                       bool& isPrevFactor, std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (isPrevFactor) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }
    int k = i;
    while (k < expr.size() && std::isalnum(expr[k])) {
        ++k;
    }
    std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
    result.push(node);
    i = k - 1;
    isPrevFactor = true;
}

void ShuntingYardParser::parseOperatorOrBracket(char c, std::stack<char>& opStack, bool& isPrevFactor,
                                               std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (c == '(') {
        opStack.push(c);
    } else if (c == ')') {
        while (!opStack.empty() && opStack.top() != '(') {
            processOperator(opStack, result);
        }
        if (opStack.empty()) {
            throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
        }
        opStack.pop();

    } else {
        while (!opStack.empty() && ranking[opStack.top()] >= ranking[c]) {
            processOperator(opStack, result);
        }
        opStack.push(c);
    }
    isPrevFactor = false;
}

void ShuntingYardParser::parseDigit(const std::shared_ptr<std::unordered_set<int>>& exprConstants, std::string expr,
                                    int& i, bool& isPrevFactor, std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (isPrevFactor) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }
    int k = i;
    while (k < expr.size() && std::isdigit(expr[k])) {
        ++k;
    }
    exprConstants->insert(std::stoi(expr.substr(i, k - i)));
    std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k - i));
    result.push(node);
    i = k - 1;
    isPrevFactor = true;
}

void ShuntingYardParser::parseVariable(const std::shared_ptr<std::unordered_set<std::string>>& exprVariables,
                                       std::string expr, int& i, bool& isPrevFactor,
                                       std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (isPrevFactor) {
        throw ShuntingYardParserException(ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }
    int k = i;
    while (k < expr.size() && std::isalnum(expr[k])) {
        ++k;
    }
    exprVariables->insert(expr.substr(i, k -i));
    std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(expr.substr(i, k -i));
    result.push(node);
    i = k - 1;
    isPrevFactor = true;
}

void ShuntingYardParser::processOperator(std::stack<char>& opStack, std::stack<std::shared_ptr<ShuntNode>>& result) {
    if (result.size() < 2) {
        throw ShuntingYardParserException(
                ParserShuntingYardParserInvalidExpressionExceptionMessage);
    }

    std::shared_ptr<ShuntNode> node = std::make_shared<ShuntNode>(std::string(1, opStack.top()));
    opStack.pop();
    node->right = result.top();
    result.pop();
    node->left = result.top();
    result.pop();
    result.push(node);
}

bool ShuntingYardParser::isMathOp(const char &value) {
    std::unordered_set<char> mathOp = {'+', '-', '*', '/', '%', '(' , ')'};
    return mathOp.find(value) != mathOp.end();
}
