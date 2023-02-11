#include "AssignPatternClause.h"
#include "query_processing_system/evaluator/clause_evaluator/pattern_clause_evaluator/AssignPatternClauseEvaluator.h"

AssignPatternClause::AssignPatternClause(Argument left, std::variant<Wildcard, StringExpression> right)
    : PatternClause(left, right) {}

ClauseEvaluator* AssignPatternClause::getClauseEvaluator() {
    return new AssignPatternClauseEvaluator(getLeftArg(), getRightArg());
}
