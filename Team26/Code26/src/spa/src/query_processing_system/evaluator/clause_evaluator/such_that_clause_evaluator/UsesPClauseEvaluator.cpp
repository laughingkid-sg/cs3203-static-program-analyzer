#include "UsesPClauseEvaluator.h"

UsesPClauseEvaluator::UsesPClauseEvaluator(Argument left, Argument right)
        : SuchThatClauseEvaluator(left, right) {}

std::unordered_map<int , std::unordered_set<int>> UsesPClauseEvaluator::getRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllRelationshipEntries();
}

std::unordered_map<int , std::unordered_set<int>>
UsesPClauseEvaluator::getOppositeRelationshipManager(StoragePointer storage) {
    return storage->getFollowsManager()->getAllReversedRelationshipEntries();
}

void UsesPClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void UsesPClauseEvaluator::setRightArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void UsesPClauseEvaluator::setLeftAndRightArgResult(
        std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
}


std::unordered_set<int> UsesPClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<int> UsesPClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, rightArg.getDesignEntity());
}

std::shared_ptr<ResultTable> UsesPClauseEvaluator::evaluateClause(StoragePointer storage) {
    return clauseResultTable;
}
