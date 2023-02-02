#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "prototypes.h"

int main(int argc, char *argv[]) {
    static char usage[] = "usage: ./all [-h] [-p] [-o output_file_name] input_file_name\n";
    FILE *fp_output, *fp_input; // files
    int err = 0, p_flag = 0, o_flag = 0, h_flag = 0; // flags and ints
    int length = 0, i = 0, size = 0;
    extern char *optarg; // part of the getopt function (unistd library)
    extern int optind; // same as above
    char c, g, *input, *temp;
    lexeme *main_list; // our list

    // our getopt function
    while ((g = getopt(argc, argv, "hpo:")) != -1) {
		switch (g) {
			case 'o': // outputs everything into a separate file, if not, we print out directly on console
                o_flag = 1;
                fp_output = fopen(optarg, "w");
                if (fp_output == NULL)
                    printf("Error with opening file...\n");
                break;
            case 'p': // print out additional information such as what is an identifier and how many
                p_flag = 1;
                break;
            case 'h':
                h_flag = 1;
                helpCommand();
                break;
			case '?':
				err = 1;
                exit(1);
				break;
		}
	}

    // need at least one argument which is the file that we are reading in
    if ((optind + 1) > argc) {
		printf("optind = %d, argc = %d\n", optind, argc);
		fprintf(stderr, "%s: missing text file name\n", argv[0]);
		fprintf(stderr, usage, argv[0]);
		exit(1);
	} else if (err) { // if we get any unwanted letters or input
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

    fp_input = fopen(argv[optind], "r"); // getting our file input
    if (fp_input == NULL) { // if file runs into an error then we want to exit
        printf("Error with opening file...\n");
        exit(1);
    }

    while (!feof(fp_input)) { // getting the size of the file
        fgetc(fp_input);
        size++;
    }

    input = (char*)malloc(sizeof(char) * size); // appropriately allocating memory from the size of the file
    rewind(fp_input); // rewind the file

    while ((c = fgetc(fp_input)) != EOF)
        input[i++] = c;
    input[i] = '\0';

    length = strlen(input);
    for (i = 0; i < length; i++)
        printf("%c", input[i]);

    main_list = lexanalyzer(input);

    if (p_flag) {
        printf("There are %d comments...\n", amountOf_Comments);
        printf("There are %d directories...\n", amountOf_Libraries);
    } else if (o_flag) {
        fprintf(fp_output, "There are %d comments...\n", amountOf_Comments);
        fprintf(fp_output, "There are %d directories...\n", amountOf_Libraries);
    }

    printf("Lexical Table:\n");
    for (i = 0; i < lex_index; i++) {
        if (main_list[i].type == number_sym)
			printf("%d %d ", number_sym, list[i].value);
		else if (main_list[i].type == ident_sym)
			printf("%d %s ", ident_sym, main_list[i].name);
		else
			printf("%d ", main_list[i].type);
    }

    return 0;
}
