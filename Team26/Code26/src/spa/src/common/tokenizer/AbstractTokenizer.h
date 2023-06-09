#pragma once

#include <vector>
#include <string>
#include <memory>
#include "common/tokenizer/token/Token.h"

/**
 * The tokenizer class tokenize an input stream into a token list.
 * */
class AbstractTokenizer {
 private:
    /**
     * This function loads the next special character from the stream to the currentToken.
     * A special character is a character that is not an alphabetic or numeric character.
     * Punctuation marks and other symbols are examples of special characters.
     * */
    virtual void readSpecialChar() = 0;

    /**
     * This functions checks if there exist leading zeros the current token.
     *
     * @return Returns true if there a leading zero in current token.
     * */
     bool hasLeadingZero();

 protected:
    /**
     * The incoming stream to read from.
     * */
    std::istream* istream;

    /**
     * Temporary storage for current token.
     * */
    std::string currentToken;

    /**
     * List of token that are tokenized.
     * */
    std::vector<std::shared_ptr<Token>> tokens;

    /**
     * Extract and return the next character in the input sequence.
     *
     * @return The first character read or end-of-file value if stream is empty.
     * */
    char nextChar();

    /**
     * Returns the next character in the input sequence without extracting it.
     *
     * @returns The next character in the input sequence, as a value of type char.
     * */
    char peekChar();

    /**
     * This function loads the next INTEGER from the stream to the currentToken.
     * */
    void readInteger();

    /**
     * This function loads the next NAME (or INDENT) from the stream to the currentToken.
     * */
    void readName();

    /**
      * Get the currentToken value.
      *
      * @return The token that current token that has been tokenized;
      * */
    std::string getCurrentToken();

    /**
     * Add token to the the token list.
     *
     * @param token The token to be added.
     * */
    void addToken(const std::shared_ptr<Token>& token);

 public:
    /**
     * Constructor for the Source Processor initialization.
     *
     * @param stream The input SIMPLE program as a stream to be tokenized.
     * */
    explicit AbstractTokenizer(std::istream* stream);

    /**
     * Constructor for the Query Processing Subsystem initialization.
     *
     * @param stream The query to be tokenized.
     * */
    explicit AbstractTokenizer(const std::string& query);

    /**
     * This functions tokenizes the input stream.
     *
     * @return The token list after tokenizing the input stream.
     * */
    virtual std::vector<std::shared_ptr<Token>> tokenize() = 0;
};
