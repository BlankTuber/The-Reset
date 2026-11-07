#include "parse.h"
#include <stdlib.h>

enum Associativity { LEFT, RIGHT };

struct Operator {
    enum TokenType type;
    int importance;
    enum Associativity associativity;
};

static const struct Operator operators[] = {
    {Plus, 1, LEFT}, {Minus, 1, LEFT}, {Times, 2, LEFT}, {Divide, 2, LEFT}, {Exponent, 3, RIGHT}};

static const struct Operator *getOperatorInfo(enum TokenType type) {
    int n = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < n; i++) {
        if (operators[i].type == type)
            return &operators[i];
    }
    return NULL;
}

// Count tokens excluding parentheses
static int countTokens(const struct Token *tokens) {
    int count = 0;
    for (int i = 0; tokens[i].tokenType != EndOfEquation; i++) {
        if (tokens[i].tokenType != OpenParen && tokens[i].tokenType != CloseParen)
            count++;
    }
    return count + 1; // Plus 1 for EoE
}

struct Token *shuntingYard(const struct Token *tokens) {
    int totalTokens = 0;
    while (tokens[totalTokens].tokenType != EndOfEquation)
        totalTokens++;

    struct Token *output = calloc(countTokens(tokens), sizeof(struct Token));
    struct Token *stack = calloc(totalTokens + 1, sizeof(struct Token)); // Set up extra space for worst case scenario
    int outSize = 0;
    int stackSize = 0;

    for (int i = 0; tokens[i].tokenType != EndOfEquation; i++) {
        struct Token token = tokens[i]; // Set current token

        if (token.tokenType == Number) {
            output[outSize++] = token; // Numbers go straight to output

        } else if (token.tokenType == OpenParen) {
            stack[stackSize++] = token; // Open paren goes to stack, and starts a "collection"

        } else if (token.tokenType == CloseParen) {
            // Close paren te3ls stack that everything between open paren and close paren shall now be added to output
            while (stackSize > 0 && stack[stackSize - 1].tokenType != OpenParen) {
                output[outSize++] = stack[--stackSize];
            }
            stackSize--; // Go to before open paren position so its effectively discarded

        } else {
            const struct Operator *current = getOperatorInfo(token.tokenType); // Get values for token operator

            while (stackSize > 0 && stack[stackSize - 1].tokenType != OpenParen) {
                const struct Operator *top = getOperatorInfo(stack[stackSize - 1].tokenType); // Values for top of stack

                // If existing operator is bigger importance than current token, pop it (except exponent)
                if (top->importance > current->importance ||
                    (top->importance == current->importance && current->associativity == LEFT)) {
                    output[outSize++] = stack[--stackSize];
                } else {
                    break;
                }
            }
            stack[stackSize++] = token; // Add operator to stack
        }
    }

    // Add whats left in stack to outout
    while (stackSize > 0) {
        output[outSize++] = stack[--stackSize];
    }
    output[outSize].tokenType = EndOfEquation;

    free(stack);
    return output;
}
