#include "BaseExtractor.h"

BaseExtractor::BaseExtractor() = default;

void BaseExtractor::extractProgram(const std::shared_ptr<ProgramNode>& node) {
    if (node->procedureList.empty()) {
        throw SourceExtractorException(BaseExtractorEmptyProcedureListExceptionMessage);
    }

    for (auto& procedure : node->procedureList) {
        extractProcedure(procedure);
    }
}

void BaseExtractor::extractProcedure(const std::shared_ptr<ProcedureNode>& node) {
    extractStmtList(node->stmtListNode);
}

void BaseExtractor::extractStmtList(const std::shared_ptr<StmtListNode>& node) {
    if (node->stmtList.empty()) {
        throw SourceExtractorException(BaseExtractorEmptyStatementListExceptionMessage);
    }

    for (auto& stmt : node->stmtList) {
        extractStmt(stmt);
    }
}

void BaseExtractor::extractStmt(const std::shared_ptr<StmtNode>& node) {
    currentStmtNo = node->stmtIndex;
}

