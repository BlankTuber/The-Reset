#include "tokenize.h"
#include <stdio.h>

char enumToChar(enum TokenType tokenType) {
    char strTokenType;
    switch (tokenType) {
    case Plus:
        strTokenType = '+';
        break;
    case Minus:
        strTokenType = '-';
        break;
    case Times:
        strTokenType = '*';
        break;
    case Divide:
        strTokenType = '/';
        break;
    case Exponent:
        strTokenType = '^';
        break;
    case OpenParen:
        strTokenType = '(';
        break;
    case CloseParen:
        strTokenType = ')';
        break;
    case Number:
        strTokenType = 'N';
        break;
    case EndOfEquation:
        strTokenType = 'E';
        break;
    default:
        strTokenType = '?';
        break;
    };
    return strTokenType;
}

int main() {
    char equation[] = "12.2 + 3.3 - 2.4 / 1.123 * 10.12";

    struct Token *tokenizedEquation = tokenize(equation);

    int i = 0;
    while (tokenizedEquation[i].tokenType != EndOfEquation) {
        printf("%c -- %f\n", enumToChar(tokenizedEquation[i].tokenType), tokenizedEquation[i].value);
        i++;
    }

    return 0;
}
