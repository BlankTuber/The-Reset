#include "evaluate.h"
#include "parse.h"
#include "tokenize.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EQUATION "2*10/22^(3/2)+5.5-(1+3)/2"

// Compare a token array against expected types and values (values only checked for numbers)
static void assertTokens(const struct Token *actual, const enum TokenType *types, const double *values, int count) {
    for (int i = 0; i < count; i++) {
        assert(actual[i].tokenType == types[i]);
        if (types[i] == Number) {
            assert(fabs(actual[i].value - values[i]) < 1e-9);
        }
    }
    assert(actual[count].tokenType == EndOfEquation);
}

static void test_tokenizer(void) {
    struct Token *tokens = tokenize(EQUATION);

    // 2*10/22^(3/2)+5.5-(1+3)/2
    const enum TokenType types[] = {Number,    Times,  Number, Divide,     Number,     Exponent, OpenParen,
                                    Number,    Divide, Number, CloseParen, Plus,       Number,   Minus,
                                    OpenParen, Number, Plus,   Number,     CloseParen, Divide,   Number};
    const double values[] = {2, 0, 10, 0, 22, 0, 0, 3, 0, 2, 0, 0, 5.5, 0, 0, 1, 0, 3, 0, 0, 2};

    assertTokens(tokens, types, values, 21);

    free(tokens);
    printf("Tokenizer: passed\n");
}

static void test_shuntingYard(void) {
    struct Token *tokens = tokenize(EQUATION);
    struct Token *postfix = shuntingYard(tokens);

    // 2 10 * 22 3 2 / ^ / 5.5 + 1 3 + 2 / -  (no parentheses in the output)
    const enum TokenType types[] = {Number, Number, Times,  Number, Number, Number, Divide, Exponent, Divide,
                                    Number, Plus,   Number, Number, Plus,   Number, Divide, Minus};
    const double values[] = {2, 10, 0, 22, 3, 2, 0, 0, 0, 5.5, 0, 1, 3, 0, 2, 0, 0};

    assertTokens(postfix, types, values, 17);

    free(tokens);
    free(postfix);
    printf("Shunting yard: passed\n");
}

static void test_calculate(void) {
    struct Token *tokens = tokenize(EQUATION);
    struct Token *postfix = shuntingYard(tokens);

    double result = calculate(postfix);
    double expected = 20.0 / pow(22.0, 1.5) + 5.5 - 2.0; // about 3.6938

    assert(fabs(result - expected) < 1e-9);

    free(tokens);
    free(postfix);
    printf("Calculator: passed (%f)\n", result);
}

int main(void) {
    test_tokenizer();
    test_shuntingYard();
    test_calculate();
    printf("All tests passed!\n");
    return 0;
}
