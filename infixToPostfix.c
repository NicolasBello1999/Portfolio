/* This program converts infix expressions (<operand> <operator> <operand> AKA 5 + 6) into postfix expressions. 
   This program uses linked lists data structure for the basis of the stack operations because it allows us 
   to dynamically allocate and deallocate memory from the heap during runtime and we don't have to worry about
   array sizes. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stacks.h"

#define INPUTSIZE 128

int precedenceCheck(char operator);
int isValidOperator(char symbol);
char *infixToPostfix(char *input);
void postFixCalculator(char *postfix);

int main(int argc, char const *argv[])
{
    int i = 0;
    char c;
    char input[INPUTSIZE], *postfix = (char*)malloc(sizeof(char) * (INPUTSIZE + 1));
    
    printf("Enter an equation: ");
    fgets(input, INPUTSIZE, stdin);

    while (input[i] != '\n') {
        if (isalpha(input[i]) || isValidOperator(input[i]) == -1)
            fprintf(stderr, "ERROR: Invalid expression, please try again...\n");
        else if (isValidOperator(input[i]) != 1)
            fprintf(stderr, "ERROR: Invalid symbol, please try again...\n");

        i++;
    }

    postfix = infixToPostfix(input);
    printf("%s\n", postfix);

    return 0;
}

int precedenceCheck(char operator) {
    // highest priority (besides paranthesises)
    if (operator == '*' || operator == '/' || operator == '%')
        return 2;
    else if (operator == '+' || operator == '-')
        return 1;
    else
        return 0;
}

int isValidOperator(char symbol) {
    if (symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-' || symbol == '(' || symbol == ')')
        return 1;
    else if (symbol == '$' || symbol == '&')
        return -1;
}

char *infixToPostfix(char *input) {
    int i = 0;
    char symbol = 'a';
    char buffer[128], *postfix = (char*)malloc(sizeof(char) * (INPUTSIZE + 1));
    node *temp = NULL;

    strcpy(buffer, "");
    strcpy(postfix, "");

    if (input == NULL) {
        fprintf(stderr, "ERROR: Input string cannot be NULL...\n");
        return NULL;
    }

    printf("Infix to Postfix Expression: \n");
    while (input[i] != '\n') { // make sure we stop at the end
        if (isdigit(input[i]) != 0) { // check we are at a number
            while (isdigit(input[i]) != 0) { // checking if the number has more than one digit (larger numbers)
                strncat(buffer, &input[i], 1); // concatenate to string
                strncat(postfix, &input[i], 1);
                i++; // iterate to next character
            }
            printf("%s ", buffer); // print out result
            strcpy(buffer, ""); // clear string
        } else if (isValidOperator(input[i]) == 1) {
            if (input[i] == '(')
                push(&temp, input[i]);
            else if (input[i] == ')') {
                while (peek(&temp) != '(') { // keep popping off from the stack until we hit '('
                    if (peek(&temp) != ')') {
                        symbol = peek(&temp);
                        strncat(postfix, &symbol, 1);
                    }
                    printf("%c ", pop(&temp));
                }
                pop(&temp); // pop the final '('
            } else {
                while (temp != NULL && precedenceCheck(peek(&temp)) >= precedenceCheck(input[i])) {
                    symbol = peek(&temp);
                    strncat(postfix, &symbol, 1);
                    printf("%c ", pop(&temp));
                }
                push(&temp, input[i]);
            }
            i++; // iterate to next character
        }
    }

    // print the last operand if present
    if (buffer[0] != '\0')
        printf("%s ", buffer);

    // pop any remaining operators from the stack and add them to the output
    while (temp != NULL) {
        symbol = peek(&temp);
        strncat(postfix, &symbol, 1);
        printf("%c ", pop(&temp));
    }
    printf("\n");

    // free memory from the temporary stack
    freeStack(&temp);

    return postfix;
}

void postFixCalculator(char *postfix) {

}

void postFixSomething(int number) {
    
}