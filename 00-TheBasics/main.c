#include <stdio.h>

int main() {
    int firstNum;
    char operator;
    int secondNum;

    printf("Write your first number: ");
    scanf("%d", &firstNum);
    while (getchar() != '\n')
        ;

    printf("Write your operator (*, /, +, -): ");
    scanf("%c", &operator);
    while (getchar() != '\n')
        ;

    printf("Write your second number: ");
    scanf("%d", &secondNum);
    while (getchar() != '\n')
        ;

    if ('*' == operator) {
        int newNum = firstNum * secondNum;
        printf("\n\nYour euqation: %d * %d = %d", firstNum, secondNum, newNum);
    } else if ('/' == operator) {
        int newNum = firstNum / secondNum;
        printf("\n\nYour euqation: %d / %d = %d", firstNum, secondNum, newNum);
    } else if ('+' == operator) {
        int newNum = firstNum + secondNum;
        printf("\n\nYour euqation: %d + %d = %d", firstNum, secondNum, newNum);
    } else if ('-' == operator) {
        int newNum = firstNum - secondNum;
        printf("\n\nYour euqation: %d - %d = %d", firstNum, secondNum, newNum);
    } else {
        printf("Haha thought you could trick me huh?");
    }

    printf("\n\n");

    return 0;
}
