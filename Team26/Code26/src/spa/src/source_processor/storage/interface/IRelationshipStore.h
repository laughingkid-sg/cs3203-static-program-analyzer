#pragma once

#include <string>

class IRelationshipStore {
 public:
    virtual void insertFollowsRelationship(const int &previousStmtNo, int &currentStmtNo) = 0;
    virtual void insertParentsRelationship(const int &parentStmtNo, int &childStmtNo) = 0;
    virtual void insertUsesSRelationship(const int &stmtNo, const std::string &variableName) = 0;
    virtual void insertModifiesSRelationship(const int &stmtNo, const std::string &variableName) = 0;
    virtual void insertUsesPRelationship(std::string  &procedureName, const std::string &variableName) = 0;
    virtual void insertModifiesPRelationship(std::string  &procedureName, const std::string &variableName) = 0;
};
