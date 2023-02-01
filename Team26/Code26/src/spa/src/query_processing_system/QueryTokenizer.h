#pragma once

#include <vector>
#include <memory>
#include <string>
#include "common/Tokenizer.h"


class QueryTokenizer : public Tokenizer {
 private:
    void readSpecialChar() override;

 protected:
    /**
     * This function reads a string that is contained within a set of inverted commas.
     */
    void readStringExpression();

 public:
    explicit QueryTokenizer(const std::string& query);

    std::vector<std::shared_ptr<Token>> tokenize() override;
};
