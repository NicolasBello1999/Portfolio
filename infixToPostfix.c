/* This program converts infix expressions (<operand> <operator> <operand> AKA 5 + 6) into postfix expressions. 
   This program uses linked lists data structure for the basis of the stack operations because it allows us 
   to dynamically allocate and deallocate memory from the heap during runtime and we don't have to worry about
   array sizes. */

#include <stdio.h>
#include <stdlib.h>
#include "stacks.h"

int precedenceCheck(int operator);

int main(int argc, char const *argv[])
{
    node *stack = NULL;
    int popped;

    push(&stack, 34);
    push(&stack, 57);
    push(&stack, 81);
    push(&stack, 95);
    push(&stack, 5);
    push(&stack, 9);
    push(&stack, 26);

    printStack(&stack);

    int symbol;

    // checking for highest priority
    if (precedenceCheck(peek(&stack)) >= symbol && (symbol != ')' || symbol != '(')) {
        printf("%c ", pop(&stack));
        push(&stack, symbol);
    } else if (symbol == ')') {
        do {
            popped = pop(&stack);
            printf("%c ", popped);
        } while (popped != '(');
    }
    push(&stack, symbol);

    return 0;
}

/*void evaluator(node **stack) {
    if (*stack == NULL) {
        printf("The stack is EMPTY\n");
        return;
    }

    if (peek(&stack))
}*/

int precedenceCheck(int operator) {
    if (operator == '*' || operator == '/' || operator == '%')
        return 2;
    else // additive symbols
        return 1;
}