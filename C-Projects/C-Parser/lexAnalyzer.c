#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "prototypes.h"

// tokenizing our program input which will then be evaluated in our parser program (parse through code) to check if the code follows C syntax
lexeme *lexanalyzer(char *input) {
    list = malloc(sizeof(lexeme) * 4000); // allocating memory to our lexical list
    int length = strlen(input), i = 0, j = 0, x = 0;
    int tempVal = 0, comEnd, limit = 0, current_line = 1;
    char *line_buffer = (char*)malloc(sizeof(char) * 100), tempChar;

    printf("Length is %d\n", length);

    while (i < length) { // iterate through the entire string (which contains the entire file)
        limit = 0; // used to limit the size of identifiers & numbers

        if (input[i] == '\n')
            current_line++;

        while (isspace(input[i]) || iscntrl(input[i])) // skips whitespaces / tabs / etc.
            i++;

        if (input[i] == '/' && input[i + 1] == '/') { // skipping single line comments
            printf("Detected line comment...\n");
			while (input[i] != '\n') {
				i++;
			}
      		i++;
            amountOf_Comments++; // increment the comment identicator
			continue; // re-iterate the condition in-case there's another comment after a recent one
        }

        if (input[i] == '/' && input[i + 1] == '*') { // checking for the beginning of the multi-line comment
            printf("Detected comment section...\n");
            comEnd = 0;
            while (1) { // we keep iterating until we find the end of the part of the multi-comment
                if (input[i] == '*' && input[i + 1] == '/') {
					comEnd = 1; // signify that we reached the end of the comment section
                    break;
				}
                i++;

				// the comment section never ends
				if (i >= length && comEnd == 0) {
					printlexerror(5);
                    return NULL;
                }
            }
            amountOf_Comments++; // increment the comment identicator
            i += 2; // in order to skip over the '*/' part
        }

        // checking for directories/libraries such as #include <stdio.h> & #include <stdlib.h>
        // (these are the only 2 directories/libraries we will be checking for)
        if (input[i] == '#') {
            printf("Detected library directory...\n");
            j = 0;
            while (input[i] != '\n')
                line_buffer[j++] = input[i++];

            // since strcmp can be a bit weird sometimes, we can match as a substring using strstr() function
            if (strstr(line_buffer, "#include <stdio.h>") != NULL) {
                list[lex_index].type = lib_dir_sym;
                strcpy(list[lex_index].name, "<stdio.h>");
            } else if (strstr(line_buffer, "#include <stdlib.h>") != NULL) {
                list[lex_index].type = lib_dir_sym;
                strcpy(list[lex_index].name, "<stdlib.h>");
            } else {
                printf("Error: Unrecognized directory\n");
                printf("%s\n", line_buffer);
                return NULL;
            }

            i++;
            lex_index++;
            amountOf_Libraries++;
        }

        // going to check for identifiers and reserved words
        if (isalpha(input[i])) {
			list[lex_index].name[limit] = input[i];
			i++, limit++;

			while (isalnum(input[i])) {
				// reached the identifier limit
				if (limit == MAX_IDENT_LEN) {
					printlexerror(3);
					return NULL;
				}

				list[lex_index].name[limit] = input[i];
				i++, limit++;
			}

			list[lex_index].name[limit] = '\0';

			if (reservedWords(list[lex_index].name) == 0) { // if it's not any of the reserved words then it's a regular variable
                list[lex_index].type = ident_sym;
            }
			lex_index++;
			continue;
		}

        // now we are going to check for numbers
		if (isdigit(input[i])) {
			while (isdigit(input[i])) {
				// we reached the limit for the amount of digits to be in a number
				if (limit == MAX_NUMBER_LEN) {
					printlexerror(2);
					return NULL;
				}

				tempChar = input[i];
				tempVal = atoi(&tempChar);

				list[lex_index].value = (10 * list[lex_index].value) + tempVal;
				i++, limit++;
			}

			// there should be no letters in the number sequence
			if (isalpha(input[i])) {
				printlexerror(1);
				return NULL;
			}

			list[lex_index].type = number_sym; // for number/integer
			lex_index++;
			continue;
		}

        // checking for a particular symbol
        if (specialCharacter(input[i]) == 1) {
            switch (input[i]) {
                case '\'':
                    list[lex_index].type = squote_sym;
                    break;
                case '\"':
                    list[lex_index].type = dquote_sym;
                    break;
                case '#':
                    list[lex_index].type = hashtag_sym;
                    break;
                case '*':
                    if (input[i + 1] != '/') // to avoid classifying a comment as mult
                        list[lex_index].type = mult_sym;
                    break;
                case '/':
                    if (input[i + 1] != '*' && input[i + 1] != '/') // to avoid classifying a comment as div
                        list[lex_index].type = div_sym;
                    break;
                case '+':
                    list[lex_index].type = plus_sym;
                    break;
                case '-':
                    list[lex_index].type = minus_sym;
                    break;
                case '(':
                    list[lex_index].type = lparen_sym;
                    break;
                case ')':
                    list[lex_index].type = rparen_sym;
                    break;
                case ',':
                    list[lex_index].type = comma_sym;
                    break;
                case ';':
                    list[lex_index].type = semicolon_sym;
                    break;
                case ':':
                    list[lex_index].type = colon_sym;
                    break;
                case '=':
                    if (input[i + 1] == '=') {
                        list[lex_index].type = eql_sym;
                        i++;
                    } else {
                        list[lex_index].type = assign_sym;
                    }
                    break;
                case '!':
                    if (input[i + 1] == '=') {
                        list[lex_index].type = neq_sym;
                        i++;
                    } else {
                        list[lex_index].type = not_sym;
                    }
                    break;
                case '>':
                    if (input[i + 1] == '=') {
                        list[lex_index].type = geq_sym;
                        i++;
                    } else {
                        list[lex_index].type = gtr_sym;
                    }
                    break;
                case '<':
                    if (input[i + 1] == '=') {
                        list[lex_index].type = leq_sym;
                        i++;
                    } else {
                        list[lex_index].type = lss_sym;
                    }
                    break;
				case '&':
					if (input[i + 1] == '&') {
						list[lex_index].type = and_sym;
						i++;
					} else {
						printlexerror(4);
                        return NULL;
					}
					break;
				case '|':
					if (input[i + 1] == '|') {
						list[lex_index].type = or_sym;
						i++;
					} else {
						printlexerror(4);
						return NULL;
					}
					break;
            }
            i++;
			lex_index++;
        } else if (specialCharacter(input[i]) == 0) {
            printlexerror(4);
            printf("The unwanted character/symbol is - %c\n", input[i]);
            return NULL;
        }
    }

    return list;
}
