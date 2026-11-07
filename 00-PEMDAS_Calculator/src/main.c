#include "evaluate.h"
#include "parse.h"
#include "tokenize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char equationBuffer[1024];
    if (fgets(equationBuffer, sizeof(equationBuffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input");
        return 1;
    }

    if (strchr(equationBuffer, '\n') == NULL) {
        fprintf(stderr, "Input too long!\n");
        return 1;
    }

    struct Token *tokenizedEquation = tokenize(equationBuffer);      // Tokenize input
    struct Token *orderedEquation = shuntingYard(tokenizedEquation); // Order equation
    double calculatedResult = calculate(orderedEquation);

    printf("Final calculation: %f\n\n", calculatedResult);

    free(tokenizedEquation);
    free(orderedEquation);

    return 0;
}
