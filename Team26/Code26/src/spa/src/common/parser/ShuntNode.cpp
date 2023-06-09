#include "ShuntNode.h"
#include <algorithm>

std::vector<std::string> ShuntNode::getPreOrderTraversal(const std::shared_ptr<ShuntNode>& node) {
    std::vector<std::string> res;
    if (node == nullptr) {
        return res;
    }
    res.push_back(node->value);
    auto left = getPreOrderTraversal(node->left);
    res.insert(res.end(), left.begin(), left.end());
    auto right = getPreOrderTraversal(node->right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

std::vector<std::string> ShuntNode::getInOrderTraversal(const std::shared_ptr<ShuntNode>& node) {
    std::vector<std::string> res;
    if (node == nullptr) {
        return res;
    }
    auto left = getInOrderTraversal(node->left);
    res.insert(res.end(), left.begin(), left.end());
    res.push_back(node->value);
    auto right = getInOrderTraversal(node->right);
    res.insert(res.end(), right.begin(), right.end());
    return res;
}

bool ShuntNode::isSubVector(std::vector<std::string> stringVector, std::vector<std::string> subVector) {
    if (subVector.size() > stringVector.size()) {
        return false;
    }
    for (int i = 0; i <= stringVector.size() - subVector.size(); i++) {
        // i is a possible starting point of a subarray
        if (std::equal(subVector.begin(), subVector.end(), stringVector.begin() + i)) {
            return true;
        }
    }
    return false;
}

bool ShuntNode::isSubTree(const std::shared_ptr<ShuntNode>& fullTree, const std::shared_ptr<ShuntNode>& partialTree) {
    /**
     * Given 2 trees A and B. Tree B is a subtree of A if the pre-order
     * traversal of B is a substring of the pre-order traversal of A AND
     * the in-order traversal of B is a substring of the in-order traversal of A.
     * The runtime is O(n).
     */
    if (partialTree == nullptr) {
        return true;
    }
    if (fullTree == nullptr) {
        return false;
    }
    std::vector<std::string> inOrder = getInOrderTraversal(fullTree);
    std::vector<std::string> preOrder = getPreOrderTraversal(fullTree);
    std::vector<std::string> partialInOrder = getInOrderTraversal(partialTree);
    std::vector<std::string> partialPreOrder = getPreOrderTraversal(partialTree);
    bool inOrderSubstring = isSubVector(inOrder, partialInOrder);
    bool preOrderSubstring = isSubVector(preOrder, partialPreOrder);
    return inOrderSubstring && preOrderSubstring;
}

bool ShuntNode::operator==(const ShuntNode& other) const {
    auto thisInOrder = getInOrderTraversal(std::make_shared<ShuntNode>(*this));
    auto thisPreOrder = getPreOrderTraversal(std::make_shared<ShuntNode>(*this));
    auto otherInOrder = getInOrderTraversal(std::make_shared<ShuntNode>(other));
    auto otherPreOrder = getPreOrderTraversal(std::make_shared<ShuntNode>(other));

    return (thisInOrder == otherInOrder) && (thisPreOrder == otherPreOrder);
}
