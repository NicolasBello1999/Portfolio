#include <stdio.h>
#include <stdlib.h>
#include "stacks.h"

int main(int argc, char const *argv[])
{
    node *stack = NULL;

    push(&stack, 10);
    push(&stack, 15);
    push(&stack, 84);
    push(&stack, 29);
    push(&stack, 63);

    printStack(&stack);

    return 0;
}