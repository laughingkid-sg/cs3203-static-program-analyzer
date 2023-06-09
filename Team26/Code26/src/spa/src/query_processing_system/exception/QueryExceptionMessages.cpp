#include "QueryExceptionMessages.h"

/**
 * Semantic Errors
 */
const char QueryValidatorDuplicatedSynonymInDeclaration[] =
        "No duplicated synonyms allowed. This synonym has been declared more than once: ";
const char QueryValidatorUndeclaredSelectClauseSynonym[] =
        "Please select a synonym that was in the declaration. This synonym has yet to be declared: ";
const char QueryValidatorUndeclaredSuchThatClauseArgument[] =
        "This argument in the relationship clause has yet to be declared: ";
const char QueryValidatorInvalidFirstDesignEntityInRelation[] =
        " is an invalid first argument for the given relation.";
const char QueryValidatorInvalidSecondDesignEntityInRelation[] =
        " is not a valid second argument for the given relation.";
const char QueryValidatorInvalidModifiesOrUsesRelationshipInSelectClause[] =
        " relationship was not created as the first argument cannot be identified. Note that wildcards are invalid.";
const char QueryInvalidNumberOfPatternArguments[] =
        " pattern clause has the wrong number of arguments.";
const char QueryValidatorIncompatibleAttributeReference[] =
        "Incompatible attribute references in with clause.";
const char QueryValidatorInvalidAttributeReference[] =
        "Invalid attribute references in with clause.";

/**
 * Syntax Errors
 */
const char QueryParserInvalidWildcardInSelectClause[] =
        "Not allowed to select a wildcard.";
const char QueryParserInvalidRelationshipInSelectClause[] =
        " is not a valid relationship, please modify your input. Note that PQL is case-sensitive.";
const char QueryParserInvalidTokenForRelationshipArgument[] =
        " is an invalid argument type in the relationship clause. Please modify your input.";
const char QueryParserInvalidEndingSemicolon[] =
        "Please remove the semicolon at the end of your Select clause.";
const char QueryParserUnexpectedToken[] =
        "Please check your input, unexpected token while parsing: ";
const char QueryParserUnbalancedStringExpression[] =
        "Cannot start/end string expression with operator.";
const char QueryValidatorInvalidFirstArgumentTypeInRelation[] =
        " is not a valid first argument type for the given relation.";
const char QueryValidatorInvalidSecondArgumentTypeInRelation[] =
        " is not a valid second argument type for the given relation.";
const char QueryInvalidCreatePatternArgument[] =
        " needs to be declared as an assign/while/if synonym to be used in a pattern clause.";
const char QueryValidatorIfWhilePatternRightArgWildcard[] =
        " should be a wildcard instead for if/while pattern clause.";
const char QueryParserInvalidSelectClause[] =
        " is an invalid select clause return value.";
const char QueryParserInvalidEqualSignInWithClause[] =
        " needs to be = for with clause.";
const char QueryParserInvalidReferenceInWithClause[] =
        " is not a valid with clause reference type.";
const char QueryParserInvalidAttributeRefInWithClause[] =
        " is not a valid with clause attribute reference syntax.";
const char QueryTokenizerInvalidPunctuation[] =
        " is an invalid punctuation.";
const char QueryParserInvalidIdent[] =
        " violates one or more IDENT grammar rules.";
const char QueryParserInvalidStringExpression[] =
        " violates one or more expr grammar rules.";
const char QueryParserInvalidLanguageRules[] =
        "One or more PQL grammar rules violated.";
const char QueryParserEmptyClause[] =
        "Must have value in clause.";
