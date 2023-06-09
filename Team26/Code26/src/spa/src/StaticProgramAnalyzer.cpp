#include "StaticProgramAnalyzer.h"
#include <utility>

void StaticProgramAnalyzer::readProgramFromFile(const std::string& filename) {
    std::shared_ptr<IStore> store = std::make_shared<Store>(storageManager->getWriteStorage(),
                                                            storageManager->getReadStorage());
    sourceManager.process(filename, store);
}

void StaticProgramAnalyzer::evaluateQuery(std::string query, std::list<std::string>& results) {
    queryManager.process(query, results, storageManager->getReadStorage());
}
