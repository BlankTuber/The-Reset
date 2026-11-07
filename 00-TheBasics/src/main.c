#include "evaluate.h"
#include "parse.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>

// Makes the enum types display as their character to see what it actually is.
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
    char equation[] = "2*10/22^(3/2)+5.5-(1+3)/2";

    struct Token *tokenizedEquation = tokenize(equation);            // Tokenize input
    struct Token *orderedEquation = shuntingYard(tokenizedEquation); // Order equation

    int i = 0;

    // Loop through tokenized equation
    while (tokenizedEquation[i].tokenType != EndOfEquation) {
        printf("%c -- %f\n", enumToChar(tokenizedEquation[i].tokenType), tokenizedEquation[i].value);
        i++;
    }

    i = 0;
    printf("\n\n\n");

    // Loop through ordered equation
    while (orderedEquation[i].tokenType != EndOfEquation) {
        printf("%c -- %f\n", enumToChar(orderedEquation[i].tokenType), orderedEquation[i].value);
        i++;
    }

    double calculatedResult = calculate(orderedEquation);

    printf("Final calculation: %f\n\n", calculatedResult);

    free(tokenizedEquation);
    free(orderedEquation);

    return 0;
}
