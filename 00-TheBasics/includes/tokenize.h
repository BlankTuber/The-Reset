#ifndef TOKENIZE_H
#define TOKENIZE_H

enum TokenType {
    Plus,
    Minus,
    Times,
    Divide,
    Exponent,
    OpenParen,
    CloseParen,
    Number,
    EndOfEquation
};

struct Token {
    enum TokenType tokenType;
    double value;
};

struct Token *tokenize(const char *equation);

#endif
