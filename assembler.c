/*
 ============================================================================
 Name        : Lab.c
 Author      : Akil Pughazhendi and Ram Muthukumar
 Class       : EE460N
 Description : LC-3b Assembler
 ============================================================================
 */

#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

FILE* infile = NULL;
FILE* outfile = NULL;

typedef struct{
	char* label;
	int lineNo;
}symbol;

const char* Opcodes[28]={
	"add", "and", "br", "brn", "brz", "brp", "brnz", "brnp", "brzp", "brnzp", "halt", "jmp", "jsr", "jsrr",
	"ldb", "ldw", "lea", "nop", "not", "ret", "lshf", "rshfl", "rshfa", "rti", "stb", "stw", "trap", "xor"
};

symbol table[255];

#define MAX_LINE_LENGTH 255
enum
{
	DONE, OK, EMPTY_LINE
};

int toNum( char * pStr ){

	char * t_ptr;
	char * orig_pStr;
	int t_length,k;
	int lNum, lNeg = 0;
	long int lNumLong;

	orig_pStr = pStr;
	if( *pStr == '#' ){				/* decimal */
		pStr++;
		if( *pStr == '-' ){			/* decimal is negative */
			lNeg = 1;
			pStr++;
		}
		t_ptr = pStr;
		t_length = strlen(t_ptr);
		for(k=0;k < t_length;k++){
			if (!isdigit(*t_ptr)){
				printf("Error: invalid decimal operand, %s\n",orig_pStr);
				exit(4);
			}
			t_ptr++;
		}
		lNum = atoi(pStr);
		if (lNeg)
			lNum = -lNum;
		return lNum;
	}
	else if( *pStr == 'x' ){	/* hex     */
		pStr++;
		if( *pStr == '-' ){				/* hex is negative */
			lNeg = 1;
			pStr++;
		}
		t_ptr = pStr;
		t_length = strlen(t_ptr);
		for(k=0;k < t_length;k++){
			if (!isxdigit(*t_ptr)){
				printf("Error: invalid hex operand, %s\n",orig_pStr);
				exit(4);
			}
			t_ptr++;
		}
		lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
		lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
		if( lNeg )
			lNum = -lNum;
		return lNum;
	}
	else{
		printf( "Error: invalid operand, %s\n", orig_pStr);
		exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
	}
}

int isOpcode(char* rawOpcode){
	int j;
	for(j = 0; j < 28; j += 1){
		if(strcmp(rawOpcode, Opcodes[j]) == 0){return j;}
	}
	return -1;
}

int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
	** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4){
	char * lRet, * lPtr;
	int i;
	if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
		return( DONE );
	for( i = 0; i < strlen( pLine ); i++ )
		pLine[i] = tolower( pLine[i] );

	/* convert entire line to lowercase */
	*pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

	/* ignore the comments */
	lPtr = pLine;
	while( *lPtr != ';' && *lPtr != '\0' &&*lPtr != '\n' )
		lPtr++;
	*lPtr = '\0';
	if( !(lPtr = strtok( pLine, "\t\n ," ) ) )
		return( EMPTY_LINE );

	if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ){ /* found a label */
		*pLabel = lPtr;
		if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
	}
	*pOpcode = lPtr;
	if( !( lPtr = strtok( NULL, "\t\n ," ) ) )
		return( OK );
	*pArg1 = lPtr;
	if( !( lPtr = strtok( NULL, "\t\n ," ) ) )
		return( OK );
	*pArg2 = lPtr;
	if( !( lPtr = strtok( NULL, "\t\n ," ) ) )
		return( OK );
	*pArg3 = lPtr;
	if( !( lPtr = strtok( NULL, "\t\n ," ) ) )
		return( OK );
	*pArg4 = lPtr;
	return( OK );
}

void pass1(void){
	/* do stuff*/
}

void pass2(void){
	/* do stuff*/
}

 int main(int argc, char* argv[]) {
	 printf("%d\n", isOpcode("add"));
	 printf("%d\n", isOpcode("snot"));
	 printf("%d\n", isOpcode("rshfl"));
	 printf("%d\n", isOpcode("brnz"));
	 printf("%d\n", isOpcode("pocket"));
}
