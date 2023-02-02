// const defines
#define MAX_IDENT_LEN 20
#define MAX_NUMBER_LEN 10
#define LOWER_CODE_LENGTH 1024 // our lower bound on how much memory we want to store at first
#define MAX_CODE_LENGTH 32768 // our max or upper bound limit to allocate memory

/* we do this to better identify structures and patterns of inputted code by tokenizing the input and then
 creating a symbol table of sorts to better differentiate said code */
typedef enum token {
    while_sym = 1, do_sym, if_sym, else_sym, ident_sym, number_sym, void_sym,
    plus_sym, minus_sym, mult_sym, div_sym, mod_sym, eql_sym, neq_sym, lss_sym, leq_sym,
    gtr_sym, geq_sym, odd_sym, lparen_sym, rparen_sym, comma_sym, brackl_sym,
    brackr_sym, hashtag_sym, semicolon_sym, case_sym, long_sym, colon_sym,
    int_sym, char_sym, str_sym, sizeof_sym, malloc_sym, const_sym, swch_sym,
    lib_dir_sym, ret_sym, assign_sym, squote_sym, dquote_sym, or_sym, not_sym, and_sym
} token;

typedef struct lexeme {
	char name[20]; // storing anything that is a character and then further evaluate what the word is
    token type; // what type of symbol of said variable
	int value; // store the value if the token type is anything numeral based
} lexeme;

// main functions
lexeme *lexanalyzer(char *input); // will return the token type of the input which will then be analyzed later on
void helpCommand();
void printlexerror(int err_num);

// helper functions for the lex analyzer function
int reservedWords(char *string);
int specialCharacter(char c);

// helper functions for the parser function

// global variables used to get how many of each type is in the program
int amountOf_Comments;
int amountOf_Functions;
int amountOf_Variables;
int amountOf_Integers;
int amountOf_Strings;
int amountOf_Characters;
int amountOf_Arrays;
int amountOf_Libraries;
int amountOf_Loops;
int current_line;

// global variables used throughout the lexical analyzer and parser programs
int lex_index;
lexeme *list;
