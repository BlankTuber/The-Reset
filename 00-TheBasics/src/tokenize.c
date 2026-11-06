
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
int equationLength(const char *equation) {
    int i = 0;
    int length = 0;
    while (equation[i] != '\0') {
        switch (equation[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
            length++;
            break;
        default:
            break;
        };

        if (equation[i] >= '0' && equation[i] <= '9') {
            while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == '.') {
                i++;
            }
            length++;
            i--;
        }

        i++;
    }

    return length + 1; // Add 1 for EndOfEquation
}

struct Token *tokenize(const char *equation) {
    const int length = equationLength(equation);
    struct Token *token_list = malloc(length * sizeof(struct Token));

    int index = 0;
    int token_index = 0;

    while (equation[index] != '\0') {
        switch (equation[index]) {
        case '+':
            token_list[token_index].tokenType = Plus;
            token_index++;
            break;
        case '-':
            token_list[token_index].tokenType = Minus;
            token_index++;
            break;
        case '*':
            token_list[token_index].tokenType = Times;
            token_index++;
            break;
        case '/':
            token_list[token_index].tokenType = Divide;
            token_index++;
            break;
        case '^':
            token_list[token_index].tokenType = Exponent;
            token_index++;
            break;
        case '(':
            token_list[token_index].tokenType = OpenParen;
            token_index++;
            break;
        case ')':
            token_list[token_index].tokenType = CloseParen;
            token_index++;
            break;
        default:
            break;
        }

        if (equation[index] >= '0' && equation[index] <= '9') {
            token_list[token_index].tokenType = Number;

            double total = 0.0;
            double fraction_weight = 0.1;

            int in_fraction = 0;
            int totalDots = 0;

            while ((equation[index] >= '0' && equation[index] <= '9') || equation[index] == '.') {
                if (equation[index] == '.') {
                    in_fraction = 1;
                    index++;
                    totalDots++;
                    if (totalDots > 1) {
                        fprintf(stderr, "Error: malformed number (extra decimal point)\n");
                        exit(1);
                    }
                    continue;
                }

                if (in_fraction) {
                    double piece = equation[index] - '0';
                    piece = piece * fraction_weight;
                    fraction_weight /= 10;
                    total += piece;
                    index++;
                } else {
                    double piece = equation[index] - '0';
                    total = (total * 10) + piece;
                    index++;
                }
            }

            token_list[token_index].value = total;
            token_index++;
            index--;
        }

        index++;
    }
    token_list[token_index].tokenType = EndOfEquation;
    return token_list;
}
