#include "Tokenizer.h"
#include <string.h>
#include <ctype.h>


//Read through file input
//
//break input into individual lexemes
//
//each lexeme found will be placed in an array
//
//Longest possible substring using whitespace and non - alphanumeric
//so don't use a pre-built tokenizer
//
//There is a strcpy function, use this with null - terminated strings


static _Bool tokenizeLexeme(const char* lexeme, struct lexics* aLex, int* numLex) {
    //based on provided lexical structure
    if (strcmp(lexeme, "(") == 0) {
        aLex[(*numLex)].token = LEFT_PARENTHESIS;
    }
    else if (strcmp(lexeme, ")") == 0) {
        aLex[(*numLex)].token = RIGHT_PARENTHESIS;
    }
    else if (strcmp(lexeme, "{") == 0) {
        aLex[(*numLex)].token = LEFT_BRACKET;
    }
    else if (strcmp(lexeme, "}") == 0) {
        aLex[(*numLex)].token = RIGHT_BRACKET;
    }
    else if (strcmp(lexeme, "while") == 0) {
        aLex[(*numLex)].token = WHILE_KEYWORD;
    }
    else if (strcmp(lexeme, "return") == 0) {
        aLex[(*numLex)].token = RETURN_KEYWORD;
    }
    else if (strcmp(lexeme, "=") == 0) {
        aLex[(*numLex)].token = EQUAL;
    }
    else if (strcmp(lexeme, ",") == 0) {
        aLex[(*numLex)].token = COMMA;
    }
    else if (strcmp(lexeme, ";") == 0) {
        aLex[(*numLex)].token = EOL;
    }
    else if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "void") == 0) {
        aLex[(*numLex)].token = VARTYPE;
    }
    else if (validIdentifier(lexeme)) {
        aLex[(*numLex)].token = IDENTIFIER;
    }
    else if (strcmp(lexeme, "+") == 0 || strcmp(lexeme, "*") == 0 || strcmp(lexeme, "!=") == 0 || strcmp(lexeme, "==") == 0 || strcmp(lexeme, "%") == 0) {
        aLex[(*numLex)].token = BINOP;
    }
    else if (validNumber(lexeme)) {
        aLex[(*numLex)].token = NUMBER;
    }
    else {
        return FALSE;
    }

    strncpy(aLex[(*numLex)].lexeme, lexeme, LEXEME_MAX);
    (*numLex)++;

    return TRUE;
}


//Parameters
//
//An array of lexics structs(pointer) (this will be large enough)
//
//an integer pointer(used for returning length of array)
//
//A pointer to a file object
//
//You will not need to be responsible for initializing the FILE object, just for reading the file
//
// 
//Returns
//
//_Bool: wrapper integer representing true / false

_Bool tokenizer(struct lexics* aLex, int* numLex, FILE* inf) {
    char lexeme[LEXEME_MAX];
    int c;

    while ((c = fgetc(inf)) != EOF) {
        if (isspace(c)) {
            while ((c = fgetc(inf)) != EOF && isspace(c)) {
                // Skip whitespace characters
            }
            // Push back the last non-whitespace character
            ungetc(c, inf);
        }
        else if (isalnum(c) || c == '_') {
            ungetc(c, inf);
            int i = 0;
            while ((c = fgetc(inf)) != EOF && (isalnum(c) || c == '_')) {
                if (i < LEXEME_MAX - 1) {
                    lexeme[i++] = c;
                }
                else {
                    return FALSE;
                }
            }
            lexeme[i] = '\0';
            ungetc(c, inf);
            if (!tokenizeLexeme(lexeme, aLex, numLex)) {
                return FALSE;
            }
        }
        else {
            lexeme[0] = c;
            lexeme[1] = '\0';
            if (!tokenizeLexeme(lexeme, aLex, numLex)) {
                return FALSE;
            }
        }
    }

    return TRUE;
}
