#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototypes.h"

void helpCommand() {
    printf("\nType -o and then the name you want for the file.\n");
    printf("For example, -o testFile\n");
    printf("The type of information that will be outputted are the token types AKA the order of symbols.\n\n");
    printf("Type -p to see additional information which are:\n");
    printf("How many variables you have.\n");
    printf("How many functions you have.\n");
    printf("How many of each type of variable (3 int variables and 4 string variables).\n");
    printf("This will also apply in the output file.\n\n");
}

// helper functions for lex analyzer file

int reservedWords(char *string) { // list of variable types and special reserved words like sizeof and such (only doing stdio and stdlib libraries)
    if (strcmp(string, "const") == 0) {
		list[lex_index].type = const_sym;
    } else if (strcmp(string, "void") == 0) {
		list[lex_index].type = void_sym;
    } else if (strcmp(string, "int") == 0) {
		list[lex_index].type = int_sym;
    } else if (strcmp(string, "char") == 0) {
		list[lex_index].type = char_sym;
    } else if (strcmp(string, "while") == 0) {
		list[lex_index].type = while_sym;
    } else if (strcmp(string, "do") == 0) {
		list[lex_index].type = do_sym;
    } else if (strcmp(string, "if") == 0) {
		list[lex_index].type = if_sym;
    } else if (strcmp(string, "long") == 0) {
		list[lex_index].type = long_sym;
    } else if (strcmp(string, "else") == 0) {
		list[lex_index].type = else_sym;
    } else if (strcmp(string, "malloc") == 0) {
		list[lex_index].type = malloc_sym;
    } else if (strcmp(string, "sizeof") == 0) {
		list[lex_index].type = sizeof_sym;
    } else if (strcmp(string, "numbers") == 0) {
		list[lex_index].type = number_sym;
    } else if (strcmp(string, "case") == 0) {
        list[lex_index].type = case_sym;
    } else if (strcmp(string, "switch") == 0) {
        list[lex_index].type = swch_sym;
    } else if (strcmp(string, "include") == 0) {
        list[lex_index].type = lib_dir_sym;
    } else if (strcmp(string, "return") == 0) {
        list[lex_index].type = ret_sym;
    } else {
		return 0;
    }
    return 1;
}

int specialCharacter(char c) { // returns true if the character is part of our list
    if (c == '!' || c == '%' || c == '*' || c == '(' || c == ')' || c == ':'
    	|| c == ';' || c == '=' || c == '+' || c == ',' || c == '/'
    	|| c == '<' || c == '>' || c == '-' || c == '#' || c == '\''
        || c == '\"' || c == '{' || c == '}' || c == '.' || c == '&'
        || c == '|') {
    		return 1;
    	} else // didn't end up being any special characters/symbols we wanted
    		return 0;
}

void printlexerror(int err_num) {
    switch (err_num) {
        case 1:
            printf("Lexical Analyzer Error: Invalid Identifier\n");
            printf("Error in line - %d\n", current_line);
            break;
        case 2:
            printf("Lexical Analyzer Error: Number Length\n");
            printf("Error in line - %d\n", current_line);
            break;
        case 3:
            printf("Lexical Analyzer Error: Identifier Length\n");
            printf("Error in line - %d\n", current_line);
            break;
        case 4:
            printf("Lexical Analyzer Error: Invalid Symbol\n");
            printf("Error in line - %d\n", current_line);
            break;
        case 5:
            printf("Lexical Analyzer Error: Never-ending comment section\n");
            break;
        default:
            printf("Implementation Error: Unrecognized Error Type\n");
            break;
    }

	free(list);
	return;
}
