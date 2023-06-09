#include <algorithm>
#include <iostream>
#include <string>
#include "Query.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"
#include "query_processing_system/exception/QueryException.h"

Query::Query() {}

Query::~Query() {
    for (auto clause : suchThatClauses) {
        delete clause;
    }

    for (auto clause : patternClauses) {
        delete clause;
    }

    for (auto  clause : withClauses) {
        delete clause;
    }
}

std::shared_ptr<std::vector<SelectClauseItem>> Query::getSelectClauseItems() {
    return selectClause->getSelectClauseItems();
}

void Query::setSelectClause(std::shared_ptr<SelectClause> selectClause_) {
    selectClause = selectClause_;
}

/* Declarations */
std::vector<std::shared_ptr<Declaration>> Query::getDeclarations() {
    return declarations;
}

void Query::addDeclaration(const Synonym& synonym, DesignEntity designEntity) {
    auto declaration = std::make_shared<Declaration>(synonym, designEntity);
    declarations.push_back(declaration);
    synonymToDesignEntityMap.insert({synonym.getIdent(), declaration->getDesignEntity()});
}

bool Query::containsSynonymInDeclaration(std::string string) {
    return synonymToDesignEntityMap.find(string) != synonymToDesignEntityMap.end();
}

std::vector<Clause*> Query::getAllClauses() {
    std::vector<Clause*> clauses;
    auto allSuchThatClauses = getSuchThatClauses();
    auto allPatternClauses = getPatternClause();
    auto allWithClauses = getWithClause();

    clauses.insert(clauses.end(), allSuchThatClauses.begin(), allSuchThatClauses.end());
    clauses.insert(clauses.end(), allPatternClauses.begin(), allPatternClauses.end());
    clauses.insert(clauses.end(), allWithClauses.begin(), allWithClauses.end());

    return clauses;
}

std::vector<SuchThatClause*> Query::getSuchThatClauses() {
    return suchThatClauses;
}

void Query::addSuchThatClause(SuchThatClause* clause) {
    suchThatClauses.push_back(clause);
}

std::vector<PatternClause*> Query::getPatternClause() {
    return patternClauses;
}

void Query::addPatternClause(PatternClause* clause) {
    patternClauses.push_back(clause);
}

/* With Clause */
std::vector<WithClause*> Query::getWithClause() {
    return withClauses;
}

void Query::addWithClause(WithClause* clause) {
    withClauses.push_back(clause);
}

DesignEntity Query::getSynonymDesignEntity(std::string string) {
    if (synonymToDesignEntityMap.count(string)) {
        DesignEntity de = synonymToDesignEntityMap[string];
        return de;
    } else {
        throw SemanticException(QueryValidatorUndeclaredSuchThatClauseArgument + string);
    }
}

bool Query::isBooleanQuery() {
    return selectClause->getSelectClauseReturnType() == SelectClauseReturnType::BOOLEAN;
}

bool Query::operator==(const Query &other) const {
    // Check if 2 pointers are equal by checking if the objects they are pointed to are equals
    auto ptrComparisonPredicate = [](const auto &item1, const auto &item2) {
        return (*item1) == (*item2);
    };

    bool sameDeclarations = std::is_permutation(declarations.begin(), declarations.end(),
                                                other.declarations.begin(), other.declarations.end(),
                                                ptrComparisonPredicate);

    bool sameSelectClause = selectClause == other.selectClause;

    return sameDeclarations && sameSelectClause;
}

std::ostream& operator << (std::ostream& os, const Query& query) {
    os << "Displaying query object\n\n";

    // Output declarations
    os << "Declarations: \n";
    for (auto i : query.declarations) {
        os << *i << "\n";
    }

    // Output select clauses
    os << "Select clauses: " << query.selectClause << "\n";
    return os;
}
