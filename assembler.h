#pragma once
#include "..\..\CPU.h"
#include "..\..\enum.h"


const int MAX_LEN_CMD = 5;
const int MIN_BUF_SIZE = 50;


void Translate(FILE* input, int* code);
bool SyntaxError(char line[], int CountOfOperand);
int AnalysSyntax(char line[]);


#define CHECK_SYNTAX(CountOfOperand)	{					       \
	if (SyntaxError(buffer[i], CountOfOperand))					\
	{										 \
		printf("Syntax Error in line %d\n", i + 1);				  \
		exit(EXIT_FAILURE);							   \
	}										    \
}
