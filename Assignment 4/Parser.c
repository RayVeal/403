#include "Parser.h"
#include "Tokenizer.h"


//Parser.c must be a recursive decent predictive parser which utilizes single - symbol lookahead.
//Parsers which utilize multi - symbol lookahead will not be accepted.
//If given a grammatically valid input, every token given must be parsed.
//If a syntax error is found, parsing does not need to continue.
//Parsers which do not consume every given token for a grammatically valid input will not be accepted

//(Not actually a parser, just a validator, no parse tree building necessary)
//
//Inputs:
//  What you give back from Tokenizer!
//
//Make sure Tokenizer works before building Parser
//
//Task
//  Apply grammar rules
//  Report syntax errors as a return FALSE
//
//Recursive descent notes
//  call functions for each grammar rule
//  use single symbol lookahead when expecting a terminal to make sure tokens match!


// Function prototypes for non-terminal parsing functions
static _Bool parseFunction(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseHeader(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseArgDecl(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseBody(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseStatementList(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseStatement(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseWhileLoop(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseReturn(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseAssignment(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseExpression(struct lexics* allLexics, int* currentIndex, int numberOfLexics);
static _Bool parseTerm(struct lexics* allLexics, int* currentIndex, int numberOfLexics);

// Function to handle syntax errors
static void syntaxError(const char* expected, struct lexics* allLexics, int currentIndex);

// Recursive descent parsing functions
static _Bool parseFunction(struct lexics* allLexics, int* currentIndex, int numberOfLexics) {
    // Implement parsing for the "function" non-terminal
    _Bool header = parseHeader(allLexics, &currentIndex, numberOfLexics);
    _Bool body = parseBody( allLexics, &currentIndex, numberOfLexics);

    if (header && body)
        return TRUE;

    return FALSE;
}

static _Bool parseHeader(struct lexics* allLexics, int* currentIndex, int numberOfLexics) {
    //_Bool arg_decl = parseArgDecl(allLexics, &currentIndex, numberOfLexics);

    if (allLexics[*currentIndex].token == VARTYPE && tokenEnumToString(allLexics[*currentIndex + 1].token) == IDENTIFIER) {
        *currentIndex += 1;

        if (allLexics[*currentIndex].token == IDENTIFIER && tokenEnumToString(allLexics[*currentIndex + 1].token) == LEFT_PARENTHESIS) {
            *currentIndex += 1;

            if (allLexics[*currentIndex].token == LEFT_PARENTHESIS && parseArgDecl(allLexics, &currentIndex, numberOfLexics)) {
                *currentIndex += 1;

                if (parseArgDecl(allLexics, &currentIndex, numberOfLexics) && allLexics[*currentIndex].token == RIGHT_PARENTHESIS) {
                    //*currentIndex += 1;

                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

static _Bool parseArgDecl(struct lexics* allLexics, int* currentIndex, int numberOfLexics) {
    if (allLexics[*currentIndex].token == VARTYPE && tokenEnumToString(allLexics[*currentIndex + 1].token) == IDENTIFIER) {
        *currentIndex += 1;

        if (allLexics[*currentIndex].token == IDENTIFIER && tokenEnumToString(allLexics[*currentIndex + 1].token) == COMMA) {
            *currentIndex += 1;

            if (allLexics[*currentIndex].token == COMMA && tokenEnumToString(allLexics[*currentIndex + 1].token) == VARTYPE) {
                *currentIndex += 1;

                if (allLexics[*currentIndex].token == VARTYPE && tokenEnumToString(allLexics[*currentIndex + 1].token) == IDENTIFIER) {
                    //*currentIndex += 1;

                    return TRUE;
                }
            }
        }
        //else if no optional
    }

    return FALSE;
}

static _Bool parseBody(struct lexics* allLexics, int* currentIndex, int numberOfLexics) {
    if (allLexics[*currentIndex].token == LEFT_BRACKET && parseStatementList(allLexics, &currentIndex, numberOfLexics)) {
        *currentIndex += 1;

        if (parseStatementList(allLexics, &currentIndex, numberOfLexics) && allLexics[*currentIndex].token == RIGHT_BRACKET) {
            *currentIndex += 1;

            return TRUE;
        }
    }

    return FALSE;
}

static _Bool parseStatementList(struct lexics* allLexics, int* currentIndex, int numberOfLexics) {
    if (parseStatement(allLexics, &currentIndex, numberOfLexics) && parseStatement(allLexics, &currentIndex, numberOfLexics)) {
        //*currentIndex += 1;

        return TRUE;
    }
    //else if no optional

    return FALSE;
}

_Bool parseStatement(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (parseWhileLoop(allLexics, &currentIndex, numberOfLexics) || parseReturn(allLexics, &currentIndex, numberOfLexics) || parseAssignment(allLexics, &currentIndex, numberOfLexics) || parseExpression(allLexics, &currentIndex, numberOfLexics)) {
        //*currentIndex += 1;

        return TRUE;
    }

    return FALSE;
}

_Bool parseWhileLoop(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (allLexics[*currentIndex].token == WHILE_KEYWORD && tokenEnumToString(allLexics[*currentIndex + 1].token) == LEFT_PARENTHESIS) {
        *currentIndex += 1;

        if (tokenEnumToString(allLexics[*currentIndex + 1].token) == LEFT_PARENTHESIS && parseExpression(allLexics, &currentIndex, numberOfLexics)) {
            *currentIndex += 1;

            if (parseExpression(allLexics, &currentIndex, numberOfLexics) && tokenEnumToString(allLexics[*currentIndex + 1].token) == RIGHT_PARENTHESIS) {
                *currentIndex += 1;

                if (tokenEnumToString(allLexics[*currentIndex + 1].token) == RIGHT_PARENTHESIS && parseStatement(allLexics, &currentIndex, numberOfLexics)) {
                    //*currentIndex += 1;

                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

_Bool parseReturn(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (tokenEnumToString(allLexics[*currentIndex + 1].token) == RETURN_KEYWORD && parseExpression(allLexics, &currentIndex, numberOfLexics)) {
        *currentIndex += 1;

        if (parseExpression(allLexics, &currentIndex, numberOfLexics) && tokenEnumToString(allLexics[*currentIndex + 1].token) == EOL) {
            //*currentIndex += 1;

            return TRUE;
        }
    }

    return FALSE;
}

_Bool parseAssignment(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (allLexics[*currentIndex].token == IDENTIFIER && tokenEnumToString(allLexics[*currentIndex + 1].token) == EQUAL) {
        *currentIndex += 1;

        if (tokenEnumToString(allLexics[*currentIndex + 1].token) == EQUAL && parseExpression(allLexics, &currentIndex, numberOfLexics)) {
            *currentIndex += 1;

            if (parseExpression(allLexics, &currentIndex, numberOfLexics) && tokenEnumToString(allLexics[*currentIndex + 1].token) == EOL) {
                //*currentIndex += 1;

                return TRUE;
            }
        }
    }
    return FALSE;
}

_Bool parseExpression(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (parseTerm(allLexics, &currentIndex, numberOfLexics)) {
        if (parseTerm(allLexics, &currentIndex, numberOfLexics) && tokenEnumToString(allLexics[*currentIndex + 1].token) == BINOP) {
            *currentIndex += 1;

            if (tokenEnumToString(allLexics[*currentIndex + 1].token) == BINOP && parseTerm(allLexics, &currentIndex, numberOfLexics)) {
                //*currentIndex += 1;

                return TRUE;
            }
        }
    }

    else if (tokenEnumToString(allLexics[*currentIndex + 1].token) == LEFT_PARENTHESIS && parseExpression(allLexics, &currentIndex, numberOfLexics)) {
        *currentIndex += 1;

        if (parseExpression(allLexics, &currentIndex, numberOfLexics) && tokenEnumToString(allLexics[*currentIndex + 1].token) == RIGHT_PARENTHESIS) {
            //*currentIndex += 1;

            return TRUE;
        }
    }

    return FALSE;
}

_Bool parseTerm(struct lexics* allLexics, int* currentIndex, int numberOfLexics)
{
    if (allLexics[*currentIndex].token == IDENTIFIER || tokenEnumToString(allLexics[*currentIndex + 1].token) == NUMBER) {
        //*currentIndex += 1;

        return TRUE;
    }

    return FALSE;
}


// The main parsing function
_Bool parser(struct lexics* allLexics, int numberOfLexics) {
    int currentIndex = 0;
    _Bool result = parseFunction(allLexics, &currentIndex, numberOfLexics);

    // Check if the entire input was parsed
    if (currentIndex ==  numberOfLexics && result) {
        printf("Parsing successful\n");
        return TRUE;
    }
    else {
        printf("Parsing failed\n");
        return FALSE;
    }
}

// Implement the syntaxError function to handle syntax errors
static void syntaxError(const char* expected, struct lexics* allLexics, int currentIndex) {
    // Handle syntax error and provide error message
    printf("Syntax error: Expected '%s', found '%s' at lexeme '%s'\n",
        expected, tokenEnumToString(allLexics[currentIndex].token), allLexics[currentIndex].lexeme);
}
