#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int i, length;
    char *arr, *temp, c;
    arr = malloc(sizeof(char));

    for (i = 0; i < 10; i++) {
        printf("Enter a letter or number: ");
        //c = getchar();
        scanf(" %c", &c);
        arr[i] = c;
        length = strlen(arr);

        if (length == i) {
            temp = realloc(arr, sizeof(arr) * 2);

            if (temp != NULL) {
                printf("Realloc memory successfully...\n");
                arr = temp;
            }
            else {
                printf("Failed to realloc memory...\n");
                free(arr);
            }
        }
    }

    length = strlen(arr);
    for (i = 0; i < length; i++)
        printf("Element [%d] = %c\n", i, arr[i]);
    return 0;
}
