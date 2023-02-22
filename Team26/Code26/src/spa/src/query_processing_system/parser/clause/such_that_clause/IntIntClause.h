#pragma once
#include "SuchThatClause.h"
#include <unordered_set>

class IntIntClause : public SuchThatClause {
 protected:
    IntIntClause(Argument leftArg, Argument rightArg);

    std::unordered_set<ArgumentType> getValidLeftArgumentType() override;

    std::unordered_set<ArgumentType> getValidRightArgumentType() override;
};
