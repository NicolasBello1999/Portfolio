#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// structs
typedef struct hashmap hashmap;
typedef struct department department;
typedef struct employee employee;

struct hashmap {
    int size;
    employee **list;
};

struct department {
    int dep_id;
    char *dep_name;
    char *position;
};

struct employee {
    int id;
    int age;
    char *name;
    department *dep;
};

hashmap *createMap(int size);
int menu();
int checkInput(char *input);

int main()
{
    int size = 0, choice = 0, c;
    hashmap *map = NULL;
        
    scanf("%d", &size); // not good practice to use scanf as its prone to buffer overflow attacks (hacking) but for this project I will use it nonetheless
    while ((c = getchar()) != '\n' && c != EOF);
    
    map = createMap(size);
    
    do {
        choice = menu();
        if (choice == 1) {
            
        } else if (choice == 2) {
            
        } else if (choice == 3) {
            
        } else if (choice == 4) {
            printf("Exiting program...\n");
        }
    } while (choice != 4);


    return 0;
}

hashmap *createMap(int size) {
    hashmap *map = (hashmap*)malloc(sizeof(hashmap));
    map->size = size;
    map->list = (employee**)malloc(sizeof(employee) * size);
    
    return map;
}

int menu() {
    char input[10];
    int choice = 0;

    printf("\nMenu options: \n");
    printf("1. Enter employee info\n");
    printf("2. Delete employee\n");
    printf("3. Redo employee info\n");
    printf("4. Exit program\n");
    printf("Enter option: ");
    
    fgets(input, 10, stdin);
    choice = checkInput(input);

    if (choice == -1) {
        printf("ERROR! while reading input...\n");
    } else if (choice == -2) {
        printf("ERROR! alpha character detected...\n");
    } else if (choice == -3) {
        printf("ERROR! non-numeric character detected...\n");
    } else if (choice < 1 || choice > 4) {
        printf("ERROR! number input was not in the choice range (1-4)...\n");
    }
        
    return choice;
}

/*!
 * @function    checkInput
 * @abstract    Check if user input is valid.
 * @discussion  This function takes the user's input in a format of a string and then checks
 *              if the user put any letters or symbols. If so, we return a number that would
 *              match an error. Otherwise, it will convert the string to an integer.
 *
 * @param       input    The user's input in string format.
 *
 * @result      Converted string into an integer result.
*/
int checkInput(char *input) {
    int length, i;
    
    if (input == NULL) {
        return -1; // error reading input
    }
    
    length = strlen(input);
    
    // checking user input
    for (i = 0; i < length - 1; i++) {
        if (isalpha(input[i])) { // if input is a character
            return -2;
        } else if (isdigit(input[i]) == 0) { // if input is not a number
            return -3;
        }
    }
    
    return atoi(input); // if no errors are encountered
}

void createEmployee(hashmap **map) {
    
}