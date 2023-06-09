#pragma once

#include "source_processor/node/Node.h"
#include "source_processor/exception/SourceException.h"

class IStmtExtractor;

enum class StmtType {
    STMT_ASSIGN,
    STMT_CALL,
    STMT_IF,
    STMT_PRINT,
    STMT_READ,
    STMT_WHILE
};

class StmtNode : public Node {
 public:
    const int stmtIndex;
    const StmtType stmtType;

    virtual void evaluate(IStmtExtractor& extractor) = 0;

    explicit StmtNode(int stmtIndex, StmtType stmtType);
};
