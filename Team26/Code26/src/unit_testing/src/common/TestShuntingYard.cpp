#include "catch.hpp"
#include <string>
#include <vector>
#include "common/parser/ShuntingYardParser.h"
#include "common/parser/ShuntNode.h"

using StringList = std::vector<std::string>;
std::string simpleTestExpression = "x+y";
std::string testExpression = "v+x*y+z*t";

TEST_CASE("Test Parse Correctly") {
    // Simple expression
    auto simpleExpressionTree = ShuntingYardParser::parse(simpleTestExpression);
    auto inOrder = ShuntNode::getInOrderTraversal(simpleExpressionTree);
    auto preOrder = ShuntNode::getPreOrderTraversal(simpleExpressionTree);
    StringList expectedInOrder = {"x", "+", "y"};
    StringList expectedPreOrder = {"+", "x", "y"};
    REQUIRE(inOrder == expectedInOrder);
    REQUIRE(preOrder == expectedPreOrder);

    // Complex expression
    auto expressionTree = ShuntingYardParser::parse(testExpression);
    inOrder = ShuntNode::getInOrderTraversal(expressionTree);
    preOrder = ShuntNode::getPreOrderTraversal(expressionTree);
    expectedInOrder = {"v", "+", "x", "*", "y", "+", "z", "*", "t"};
    expectedPreOrder = {"+", "+", "v", "*", "x", "y", "*", "z", "t"};
    REQUIRE(inOrder == expectedInOrder);
    REQUIRE(preOrder == expectedPreOrder);
}

TEST_CASE("Test Is Match") {
    auto expressionTree = ShuntingYardParser::parse(testExpression);
    // Positive matches
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("x*y")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x*y")));
    REQUIRE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x*y+z*t")));

    // Negative matches
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("v+x")));
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("y+z*t")));
    REQUIRE_FALSE(ShuntNode::isSubTree(expressionTree, ShuntingYardParser::parse("x*y+z*t")));
}
