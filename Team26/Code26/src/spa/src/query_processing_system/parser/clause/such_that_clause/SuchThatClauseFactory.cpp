#include <utility>
#include <iostream>

#include "SuchThatClauseFactory.h"

SuchThatClause *SuchThatClauseFactory::createSuchThatClause(std::string relation, Argument leftArg, Argument rightArg) {
    if (relation == ModifiesRelation || relation == UsesRelation) {
        ArgumentType leftArgType = leftArg.getArgumentType();
        if (leftArgType == ArgumentType::SYNONYM) {  // checks if first argument type is a Synonym
            Query query;
            DesignEntity leftArgDesignEntity = leftArg.getDesignEntity();
            if (leftArgDesignEntity == DesignEntity::PROCEDURE) {  // checks if Synonym is a procedure
//                std::cout << "synonym: procedure created" << std::endl;
                if (relation == ModifiesRelation) {
                    return new ModifiesPClause(leftArg, rightArg);
                } else {
                    return new UsesPClause(leftArg, rightArg);
                }
            } else {  // else the Synonym is a statement
//                std::cout << "synonym: statement created" << std::endl;
                if (relation == ModifiesRelation) {
                    return new ModifiesSClause(leftArg, rightArg);
                } else {
                    return new UsesSClause(leftArg, rightArg);
                }
            }
        } else if (leftArgType == ArgumentType::CHARACTERSTRING) {
//            std::cout << "character string: procedure created" << std::endl;
            if (relation == ModifiesRelation) {
                return new ModifiesPClause(leftArg, rightArg);
            } else {
                return new UsesPClause(leftArg, rightArg);
            }
        } else if (leftArgType == ArgumentType::NUMBER) {
//            std::cout << "number: statement created" << std::endl;
            if (relation == ModifiesRelation) {
                return new ModifiesSClause(leftArg, rightArg);
            } else {
                return new UsesSClause(leftArg, rightArg);
            }
        } else {
            // Wildcards cannot be created
            throw QueryValidationException(relation + QueryValidatorInvalidModifiesOrUsesRelationshipInSelectClause);
        }
    } else if (relation == FollowsRelation) {
        return new FollowsClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == FollowsTRelation) {
        return new FollowsTClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentRelation) {
        return new ParentClause(std::move(leftArg), std::move(rightArg));
    } else if (relation == ParentTRelation) {
        return new ParentTClause(std::move(leftArg), std::move(rightArg));
    } else {
        // No such relation, throw error
        throw QueryInvalidRelationship(relation + QueryParserInvalidRelationshipInSelectClause);
    }
}
