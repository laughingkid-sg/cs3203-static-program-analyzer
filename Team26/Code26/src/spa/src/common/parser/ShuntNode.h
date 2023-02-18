#pragma once
#include <string>
#include <memory>
#include <utility>
#include <vector>

class ShuntNode;

class ShuntNode {
 private:
    /**
     * Given a string, check if it can be composed of contiguous elements of strings in the vector.
     */
    static bool isSubVector(std::vector<std::string> stringVector, std::vector<std::string> subVector);

 public:
    const std::string value;

    std::shared_ptr<ShuntNode> left;

    std::shared_ptr<ShuntNode> right;

    explicit ShuntNode(std::string value) : value(std::move(value)), left(nullptr), right(nullptr) {}

    static std::vector<std::string> getInOrderTraversal(std::shared_ptr<ShuntNode> node);

    static std::vector<std::string> getPreOrderTraversal(std::shared_ptr<ShuntNode> node);

    /**
     * Given another node, check if the tree rooted at that node is a subtree of the current tree.
     * @return True, if it is a sub tree. Otherwise, false.
     */
    static bool isSubTree(const std::shared_ptr<ShuntNode>& fullTree, const std::shared_ptr<ShuntNode>& partialTree);
};
