#include "Givens.h"


//Constants:
//
//TRUE and FALSE
//
//shouldn't need them in c99
//
//max lexeme size
//
//no lexeme will be bigger than 256 characters
//
//No input will be larger than 256 lexemes
//
//definition of struct named lexics
//
//token category
//
//string representation of the lexeme, make sure you null - terminate your strings!
//
//enum for all Tokens of lexical structure
//
//	all the token classes
//
//	Boolean functions for identifying a valid identifier and number


_Bool validNumber(char* aLexeme){
	regex_t numberRegex;
	regcomp(&numberRegex, "^[0-9][0-9]*$", REG_EXTENDED);
	return !regexec(&numberRegex, aLexeme, 0, 0, 0);	
}

_Bool validIdentifier(char * aLexeme){
	regex_t identifierRegex;
	regcomp(&identifierRegex, "^[a-zA-Z][a-zA-Z0-9]*$", REG_EXTENDED);
	return !regexec(&identifierRegex, aLexeme, 0, 0, 0);
}