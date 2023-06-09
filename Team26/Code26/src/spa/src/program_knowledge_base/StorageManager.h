#pragma once

#include <vector>
#include <memory>
#include "Storage.h"
#include "program_knowledge_base/relationship/IWriteRelationshipManager.h"
#include "program_knowledge_base/entity/IWriteEntityManager.h"
#include "program_knowledge_base/pattern/IWritePatternManager.h"
#include "program_knowledge_base/relationship/IReadRelationshipManager.h"
#include "program_knowledge_base/entity/IReadEntityManager.h"
#include "program_knowledge_base/pattern/IReadPatternManager.h"

using WriteStorage = Storage<IWriteRelationshipManager, IWriteEntityManager, IWritePatternManager>;
using ReadStorage =  Storage<IReadRelationshipManager, IReadEntityManager, IReadPatternManager>;

class StorageManager {
 private:
    std::shared_ptr<StorageUtil> storageUtil;
 public:
    StorageManager() {
        storageUtil = std::make_shared<StorageUtil>();
    }

    std::shared_ptr<WriteStorage> getWriteStorage() {
        return std::make_shared<WriteStorage>(storageUtil);
    }

    std::shared_ptr<ReadStorage> getReadStorage() {
        return std::make_shared<ReadStorage>(storageUtil);
    }
};
