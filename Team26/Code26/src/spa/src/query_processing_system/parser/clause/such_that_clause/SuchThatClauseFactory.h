#pragma once

#include <string>
#include <memory>
#include "AffectsClause.h"
#include "AffectsTClause.h"
#include "CallsClause.h"
#include "CallsTClause.h"
#include "FollowsClause.h"
#include "FollowsTClause.h"
#include "ModifiesPClause.h"
#include "ModifiesSClause.h"
#include "NextClause.h"
#include "NextTClause.h"
#include "ParentClause.h"
#include "ParentTClause.h"
#include "UsesPClause.h"
#include "UsesSClause.h"
#include "SuchThatClauseFactory.h"
#include "query_processing_system/exception/QueryException.h"
#include "query_processing_system/exception/QueryExceptionMessages.h"
#include "query_processing_system/parser/Argument.h"
#include "query_processing_system/parser/Query.h"
#include "program_knowledge_base/StorageManager.h"

const char AffectsRelation[] = "Affects";
const char AffectsTRelation[] = "Affects*";

const char CallsRelation[] = "Calls";
const char CallsTRelation[] = "Calls*";

const char FollowsRelation[] = "Follows";
const char FollowsTRelation[] = "Follows*";

const char ModifiesRelation[] = "Modifies";

const char NextRelation[] = "Next";
const char NextTRelation[] = "Next*";

const char ParentRelation[] = "Parent";
const char ParentTRelation[] = "Parent*";

const char UsesRelation[] = "Uses";

class SuchThatClauseFactory {
 public:
    /**
     * Factory method to create a new Such That Clause.
     *
     * @param relation The type of relation.
     * @param leftArg The left argument for the clause.
     * @param rightArg  The right argument for the clause.
     * @return The SuchThatClause object.
     */
    static SuchThatClause* createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg);
};
