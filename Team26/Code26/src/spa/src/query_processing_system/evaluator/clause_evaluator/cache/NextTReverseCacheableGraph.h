#pragma once
#include "TransitiveCacheableGraph.h"
#include <unordered_map>
#include <unordered_set>

class NextTReverseCacheableGraph : public TransitiveCacheableGraph {
 public:
    explicit NextTReverseCacheableGraph(CacheStorage storage);

    void setBase() override;
};
