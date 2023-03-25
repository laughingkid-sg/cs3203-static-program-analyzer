#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "StringStringClauseEvaluator.h"

class UsesPClauseEvaluator : public StringStringClauseEvaluator {
 public:
    UsesPClauseEvaluator(Argument left, Argument right);

    StringStringMap getRelationshipManager() override;

    StringStringMap getOppositeRelationshipManager() override;
};
