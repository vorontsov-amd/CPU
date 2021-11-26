#pragma once
#include "CPU.h"

const int MAX_LEN_CMD = 5;
const int MIN_BUF_SIZE = 50;

enum NumOperand
{
	ZERO_OPERAND = 0,
	ONE_OPERAND = 1,
};

void Translate(FILE* input, CPU& assembler);
bool SyntaxError(char line[], int CountOfOperand);

#define CHECKSYNTAX(CountOfOperand)	{							\
	if (SyntaxError(buffer[i], (CountOfOperand)))			  	 \
	{															  \
		printf("Syntax Error: More one operand in line %d\n", i);  \
		exit(EXIT_FAILURE);											\
	}																 \
}