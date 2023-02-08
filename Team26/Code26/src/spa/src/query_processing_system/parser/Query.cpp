#include <algorithm>
#include <iostream>

#include "Query.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"
#include "query_processing_system/exception/QueryException.h"

Query::Query() {}

Query::~Query() {
    for (auto clause : suchThatClauses) {
        delete clause;
    }
}

std::shared_ptr<SelectClause> Query::getSelectClause() {
    return selectClause;
}

std::vector<std::shared_ptr<Declaration>> Query::getDeclarations() {
    return declarations;
}

std::vector<SuchThatClause*> Query::getSuchThatClauses() {
    return suchThatClauses;
}

void Query::setSelectClause(std::shared_ptr<SelectClause> selectClause_) {
    selectClause = selectClause_;
}

void Query::addSuchThatClause(SuchThatClause* clause) {
    suchThatClauses.push_back(clause);
}

void Query::addDeclaration(const Synonym& synonym, DesignEntity designEntity) {
    auto declaration = std::make_shared<Declaration>(synonym, designEntity);
    declarations.push_back(declaration);
//    std::cout << synonym.getIdent() << " " << toString(declaration->getDesignEntity()) << std::endl;
    synonymToDesignEntityMap.insert({synonym.getIdent(), declaration->getDesignEntity()});
}

DesignEntity Query::getSynonymDesignEntity(std::shared_ptr<Synonym> synonym) {
    return getSynonymDesignEntity(synonym->getIdent());
}

DesignEntity Query::getSynonymDesignEntity(std::string string) {
    if (synonymToDesignEntityMap.count(string)) {
        DesignEntity de = synonymToDesignEntityMap[string];
        return de;
    } else {
        throw QueryInvalidRelationshipArguments(QueryValidatorUndeclaredSuchThatClauseArgument + string);
    }
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
