#pragma once
#include "..\..\CPU.h"
#include "..\..\enum.h"


const int MAX_LEN_CMD = 5;
const int MIN_BUF_SIZE = 50;

enum LabelStatus
{
	LOADING,
	COMPLETED,
};


const int MAX_LEN_LABEL_NAME = 20;
struct label_t
{
	int pointer;
	char mark[MAX_LEN_LABEL_NAME];
};

struct Label
{
	label_t* label = nullptr;
	size_t size;
	size_t capacity;
	LabelStatus status;
};


label_t NoFindLabel =
{
	-1,
	"Unknown",
};

void Translate(FILE* input, int* code);
bool SyntaxError(char line[], int CountOfOperand);
int AnalysSyntax(char line[]);
Label& LabelCtor(Label& label, int capacity = 20);
inline bool IsMark(const char str[]);
void AddLabel(const char str[], Label& label, const int index);
label_t FindLabel(char str[], Label& label);
inline bool LabelNotCreated(label_t label);

#define CHECK_SYNTAX(CountOfOperand)	{			\
	if (SyntaxError(buffer[i], CountOfOperand))		 \
	{							  \
		printf("Syntax Error in line %d\n", i + 1);	   \
		exit(EXIT_FAILURE);				    \
	}							     \
}
