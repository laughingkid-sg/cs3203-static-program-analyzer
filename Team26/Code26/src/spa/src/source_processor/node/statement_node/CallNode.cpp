#include "CallNode.h"
#include <memory>
#include "source_processor/design_extractor/interface/statement_extractor/IStmtExtractor.h"

CallNode::CallNode(int stmtIndex, std::string processName)
    : StmtNode(stmtIndex, StmtType::STMT_CALL), processName(processName) {}

void CallNode::evaluate(IStmtExtractor &extractor) {
    extractor.extractCall(shared_from_this());
}
