#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <ostream>
#include "SelectClause.h"
#include "Declaration.h"
#include "Synonym.h"
#include "clause/such_that_clause/SuchThatClause.h"
#include "query_processing_system/parser/clause/pattern_clause/AssignPatternClause.h"
#include "query_processing_system/parser/clause/with_clause/WithClause.h"

class Query {
 private:
    // Select clause of the Query
    std::shared_ptr<SelectClause> selectClause;
    // List of declarations in the query
    std::vector<std::shared_ptr<Declaration>> declarations;
    // List of such that clauses in the query
    std::vector<SuchThatClause*> suchThatClauses;
    // List of with clauses in the query
    std::vector<WithClause*> withClauses;
    // Map of synonyms to design entity
    std::unordered_map<std::string, DesignEntity> synonymToDesignEntityMap;
    // List of pattern clauses in the query
    std::vector<PatternClause*> patternClauses;

 public:
    Query();

    ~Query();

    DesignEntity getSynonymDesignEntity(std::string string);

    std::shared_ptr<std::vector<SelectClauseItem>> getSelectClauseItems();

    void setSelectClause(std::shared_ptr<SelectClause> selectClause);

    std::vector<std::shared_ptr<Declaration>> getDeclarations();

    std::vector<SuchThatClause*> getSuchThatClauses();

    std::vector<PatternClause*> getPatternClause();

    std::vector<WithClause*> getWithClause();

    std::vector<Clause*> getAllClauses();

    bool isBooleanQuery();

    bool containsSynonymInDeclaration(std::string);

    /**
     * Add a new declaration to the Query object.
     *
     * @param synonym The synonym of the declaration.
     * @param designEntity The design entity of the synonym.
     */
    void addDeclaration(const Synonym& synonym, DesignEntity designEntity);

    /**
     * Add a new such that clause to the query.
     *
     * @param clause The such that clause to be added.
     */
    void addSuchThatClause(SuchThatClause* clause);

    void addPatternClause(PatternClause* clause);

    void addWithClause(WithClause* clause);

    bool operator==(const Query& other) const;

    friend std::ostream& operator << (std::ostream& os, const Query& query);
};
