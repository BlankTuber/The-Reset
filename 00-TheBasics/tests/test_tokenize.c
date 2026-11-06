#include "tokenize.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void test_tokenizer(void) {
    struct Token *input = tokenize("12.2 + 3.3 - 2.4 / 1.123 * 10.12");

    // Check for desired output
    assert(input[0].tokenType == Number);
    assert(input[0].value == 12.20);

    assert(input[1].tokenType == Plus);
    assert(input[1].value == 0.0);

    assert(input[2].tokenType == Number);
    assert(input[2].value == 3.30);

    assert(input[3].tokenType == Minus);
    assert(input[3].value == 0.0);

    assert(input[4].tokenType == Number);
    assert(input[4].value == 2.40);

    assert(input[5].tokenType == Divide);
    assert(input[5].value == 0.0);

    assert(input[6].tokenType == Number);
    assert(input[6].value == 1.1230);

    assert(input[7].tokenType == Times);
    assert(input[7].value == 0.0);

    assert(input[8].tokenType == Number);
    assert(input[8].value == 10.120);

    assert(input[9].tokenType == EndOfEquation);

    // All tests passed!
    printf("All tests passed!\n\n");

    free(input);
}

int main(void) {
    test_tokenizer();
    return 0;
}
