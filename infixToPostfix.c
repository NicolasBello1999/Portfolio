/* This program converts infix expressions (<operand> <operator> <operand> AKA 5 + 6) into postfix expressions. 
   This program uses linked lists data structure for the basis of the stack operations because it allows us 
   to dynamically allocate and deallocate memory from the heap during runtime and we don't have to worry about
   array sizes. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stacks.h"

int precedenceCheck(char operator);
void analyzeString(node **stack, char *input);
void analyzeStack(node **stack, char symbol);

int main(int argc, char const *argv[])
{
    node *stack = NULL;
    int popped, symbol;
    char input[1000];
    
    push(&stack, 34);
    push(&stack, 57);
    push(&stack, 81);
    push(&stack, 95);
    push(&stack, 5);
    push(&stack, 9);
    push(&stack, 26);

    printStack(&stack);

    printf("Enter an equation: ");
    fgets(input, 1000, stdin);

    analyzeString(&stack, input);

    // checking for highest priority
    /*if (precedenceCheck(peek(&stack)) >= symbol && (symbol != ')' || symbol != '(')) {
        printf("%c ", pop(&stack));
        push(&stack, symbol);
    } else if (symbol == ')') {
        do {
            popped = pop(&stack);
            printf("%c ", popped);
        } while (popped != '(');
    }
    push(&stack, symbol);*/

    return 0;
}

/*void evaluator(node **stack) {
    if (*stack == NULL) {
        printf("The stack is EMPTY\n");
        return;
    }

    if (peek(&stack))
}*/

int precedenceCheck(char operator) {
    if (operator == '*' || operator == '/' || operator == '%')
        return 2;
    else // additive symbols
        return 1;
}

int isValidOperator(char symbol) {
    if (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-' || symbol == '(' || symbol == ')')
        return 1;
    else
        return 0;
}

void analyzeString(node **stack, char *input) {
    int i = 0;
    char buffer[10];
    node *temp = *stack;

    if (input == NULL) {
        printf("Input string cannot be NULL.\n");
        return;
    }

    printf("Infix to Postfix Expression: \n");
    while (input[i] != '\n') {
        strcpy(buffer, "");
        if (isdigit(input[i]) != 0) {
            while (isdigit(input[i]) != 0) {
                strncat(buffer, &input[i], 1);
                i++;
            }
            printf("%s ", buffer);
        }

        if (isValidOperator(input[i]) == 1)
            analyzeStack(stack, input[i]);

        i++;
    }
    printf("\n");
}

void analyzeStack(node **stack, char symbol) {
    int popped;
    node *temp = *stack;

    if (temp == NULL) {
        push(&temp, symbol);
    } else if (precedenceCheck(peek(&temp)) >= symbol && (symbol != ')' || symbol != '(')) {
        printf("%c ", pop(&temp));
        push(&temp, symbol);
    } else if (symbol == ')') {
        do {
            popped = pop(&temp);
            printf("%c ", popped);
        } while (popped != '(');
    }
    //push(&temp, symbol);
}