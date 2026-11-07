#include "evaluate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calculate(const struct Token *equation) {
    int totalTokens = 0;
    while (equation[totalTokens].tokenType != EndOfEquation)
        totalTokens++;

    double *numStack = calloc(totalTokens + 1, sizeof(double));

    int stackSize = 0;

    for (int i = 0; equation[i].tokenType != EndOfEquation; i++) {
        if (equation[i].tokenType == Number) {
            numStack[stackSize++] = equation[i].value;
        } else {
            if (stackSize < 2) {
                free(numStack);
                fprintf(stderr, "Error: malformed equation\n");
                exit(1);
            }

            double right = numStack[--stackSize];
            double left = numStack[--stackSize];
            switch (equation[i].tokenType) {
            case Plus:
                numStack[stackSize++] = left + right;
                break;
            case Minus:
                numStack[stackSize++] = left - right;
                break;
            case Times:
                numStack[stackSize++] = left * right;
                break;
            case Divide:
                if (right == 0.0) {
                    free(numStack);
                    fprintf(stderr, "Error: Division by zero\n");
                    exit(1);
                }
                numStack[stackSize++] = left / right;
                break;
            case Exponent:
                numStack[stackSize++] = pow(left, right);
                break;
            case OpenParen:
            case CloseParen:
            case Number:
            case EndOfEquation:
            default:
                break;
            }
        }
    }

    if (stackSize != 1) {
        free(numStack);
        fprintf(stderr, "Error: Something wrong!\n");
        exit(1);
    }

    double finalCalc = numStack[0];
    free(numStack);
    return finalCalc;
}
