#include "IntStringClauseEvaluator.h"

IntStringClauseEvaluator::IntStringClauseEvaluator(Argument left, Argument right)
    : SuchThatClauseEvaluator<int, std::string>(left, right) {}

std::shared_ptr<ResultTable> IntStringClauseEvaluator::evaluateClause(StoragePointer storage) {
    auto argumentType = getClauseArgumentType(leftArg.getArgumentType(), rightArg.getArgumentType());
    if (argumentType == ClauseArgumentTypes::NUMBER_STRING) {
        evaluateNumberString(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_SYNONYM) {
        evaluateNumberSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_SYNONYM) {
        evaluateSynonymSynonym(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_STRING) {
        evaluateSynonymString(storage);
    } else if (argumentType == ClauseArgumentTypes::SYNONYM_WILDCARD) {
        evaluateSynonymWildcard(storage);
    } else if (argumentType == ClauseArgumentTypes::NUMBER_WILDCARD) {
        evaluateNumberWildcard(storage);
    } else {
        throw std::exception();
    }
    optimiseResults();
    return clauseResultTable;
}

void IntStringClauseEvaluator::evaluateSynonymString(StoragePointer storage) {
    std::unordered_set<int> leftResults;
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto res = evaluateNumberSynonymHelper(storage, statement);
        if (res.count(rightArg.getValue())) {
            leftResults.insert(statement);
        }
    }
    setLeftArgResult(leftResults);
}

void IntStringClauseEvaluator::evaluateNumberString(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    if (!res.count(rightArg.getValue())) {
        clauseResultTable->setNoResults();
    }
}

void IntStringClauseEvaluator::evaluateNumberSynonym(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    setRightArgResult(res);
}

void IntStringClauseEvaluator::evaluateSynonymSynonym(StoragePointer storage) {
    // Set initial empty results
    std::unordered_map<std::string, std::unordered_set<std::string>> res;
    auto statementsToEvaluate = getLeftArgEntities(storage);
    for (int statement : statementsToEvaluate) {
        auto synonymResults = evaluateNumberSynonymHelper(storage, statement);
        if (!synonymResults.empty()) {
            res.insert({std::to_string(statement), synonymResults});
        }
    }
    setLeftAndRightArgResult(res);
}

std::unordered_set<std::string> IntStringClauseEvaluator::evaluateNumberSynonymHelper(StoragePointer storage,
                                                                                      int stmtNumber) {
    auto parentRelation = getChildrenRelationMap(storage);
    auto iterator = parentRelation.find(stmtNumber);
    auto relationshipStore = getRelationshipManager(storage);
    std::unordered_set<std::string> res;
    if (iterator != parentRelation.end()) {
        // This statement has children
        for (auto child : iterator->second) {
            if (relationshipStore.count(child)) {
                PkbUtil::setUnion(res, relationshipStore.find(child)->second);
            }
        }
    }
    if (relationshipStore.count(stmtNumber)) {
        PkbUtil::setUnion(res, relationshipStore.find(stmtNumber)->second);
    }
    return res;
}

void IntStringClauseEvaluator::evaluateNumberWildcard(StoragePointer storage) {
    auto res = evaluateNumberSynonymHelper(storage, stoi(leftArg.getValue()));
    if (res.empty()) {
        clauseResultTable->setNoResults();
    }
}

std::unordered_map<int, std::unordered_set<int>>
IntStringClauseEvaluator::getChildrenRelationMap(StoragePointer storage) {
    return storage->getParentTManager()->getAllRelationshipEntries();
}

void IntStringClauseEvaluator::handleLeftWildcard() {
    leftArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::STMT);
}

void IntStringClauseEvaluator::handleRightWildcard() {
    rightArg = Argument(ArgumentType::SYNONYM, "WILDCARD_PLACEHOLDER", DesignEntity::VARIABLE);
}

void IntStringClauseEvaluator::setLeftArgResult(std::unordered_set<int> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(leftArg.getValue(),
                                                             PkbUtil::intSetToStringSet(result));
}

void IntStringClauseEvaluator::setRightArgResult(std::unordered_set<std::string> result) {
    clauseResultTable = ResultTable::createSingleColumnTable(rightArg.getValue(), result);
}

void IntStringClauseEvaluator::setLeftAndRightArgResult(
        std::unordered_map<std::string, std::unordered_set<std::string>> results) {
    clauseResultTable = ResultTable::createTableFromMap(results, leftArg.getValue(), rightArg.getValue());
}

std::unordered_set<int> IntStringClauseEvaluator::getLeftArgEntities(StoragePointer storage) {
    return PkbUtil::getIntEntitiesFromPkb(storage, leftArg.getDesignEntity());
}

std::unordered_set<std::string> IntStringClauseEvaluator::getRightArgEntities(StoragePointer storage) {
    return PkbUtil::getStringEntitiesFromPkb(storage, rightArg.getDesignEntity());
}
