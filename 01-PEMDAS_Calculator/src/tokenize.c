
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>

// Count the equation's required length
int equationLength(const char *equation) {
    int i = 0;
    int length = 0;

    // Loop over the equation until end of string character
    while (equation[i] != '\0') {
        switch (equation[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '(':
        case ')':
            length++; // All operators add 1 length
            break;
        default:
            break;
        };

        // Check for if the char is a number
        if (equation[i] >= '0' && equation[i] <= '9') {

            // Loop to find neighbor numbers, so that they only take 1 lenght, as they will be combined
            while ((equation[i] >= '0' && equation[i] <= '9') || equation[i] == '.') {
                i++;
            }
            length++;
            i--; // Step back once cuz while loop stops at first non-number, and we dont want it to be skipped
        }

        i++;
    }

    return length + 1; // Add 1 for EndOfEquation
}

struct Token *tokenize(const char *equation) {
    const int length = equationLength(equation); // Get equation length

    // Allocate zeroed memory for array of a "length" amount of "Token" structs
    struct Token *token_list = calloc(length, sizeof(struct Token));

    int index = 0;
    int token_index = 0;

    // Loop over equation until end of string char
    while (equation[index] != '\0') {

        // Switch to set each operator's token type
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

        // Check if char is a number
        if (equation[index] >= '0' && equation[index] <= '9') {
            token_list[token_index].tokenType = Number;

            double total = 0.0;
            double fraction_weight = 0.1; // Fraction weight to calculate decimal places

            int in_fraction = 0; // Check to see if we are in decimal terretory
            int totalDots = 0;   // Minor block for potentially malformed number

            while ((equation[index] >= '0' && equation[index] <= '9') || equation[index] == '.') {
                // If the char is a fraction, enable in_fraction and go to next char
                if (equation[index] == '.') {
                    in_fraction = 1;
                    index++;
                    totalDots++;

                    // Kill program if malformed number
                    if (totalDots > 1) {
                        free(token_list);
                        fprintf(stderr, "Error: malformed number (extra decimal point)\n");
                        exit(1);
                    }
                    continue;
                }

                // If in fraction, calculate decimal place and set up for next
                if (in_fraction) {
                    double piece = equation[index] - '0';
                    piece = piece * fraction_weight;
                    fraction_weight /= 10;
                    total += piece;
                    index++;
                } else { // Else calculate whole number with left-shift calculation
                    double piece = equation[index] - '0';
                    total = (total * 10) + piece;
                    index++;
                }
            }

            // Set value and make sure index doesn't skip next char
            token_list[token_index].value = total;
            token_index++;
            index--;
        }

        index++;
    }

    // Add end of equation to let users of the function find the end
    token_list[token_index].tokenType = EndOfEquation;
    return token_list;
}
