#pragma once
#include "SuchThatClauseEvaluator.h"
#include <string>
#include <unordered_set>
#include <memory>

class IntStringClauseEvaluator : public SuchThatClauseEvaluator<int, std::string> {
 private:
    std::unordered_set<std::string> evaluateNumberSynonymHelper(StoragePointer storage, int stmtNumber);
 protected:
    IntStringClauseEvaluator(Argument left, Argument right);

    void setLeftArgResult(std::unordered_set<int> result) override;

    void setRightArgResult(std::unordered_set<std::string> result) override;

    std::unordered_set<int> getLeftArgEntities(StoragePointer storage) override;

    std::unordered_set<std::string> getRightArgEntities(StoragePointer storage) override;

    void handleLeftWildcard() override;

    void handleRightWildcard() override;

    void evaluateNumberSynonym(StoragePointer storage);

    void evaluateSynonymSynonym(StoragePointer storage);

    void evaluateSynonymString(StoragePointer storage);

    void evaluateNumberString(StoragePointer storage);
 public:
    std::shared_ptr<ClauseResult> evaluateClause(StoragePointer storage) override;
};
