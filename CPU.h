#pragma once
#include "C:\\Users\voron\Documents\Code\C\SXLib\SXLib\SXLIB.h"
#include "C:\\Users\voron\Documents\Code\C\Stack\Stack\Stack.h"

enum CMD
{
	CMD_push = 1,
	CMD_rpush,
	CMD_pop,
	CMD_rpop,
	CMD_out,
	CMD_add,
	CMD_sub,
	CMD_mul,
	CMD_div,
	CMD_sqrt,
	CMD_in,
	CMD_hlt = -1,
};


enum RegistIndex
{
	rax_index,
	rbx_index,
	rcx_index,
	rdx_index,
};

struct CPU
{
	Stack stack;
	int registr[4];
	int ip;
	int* code;
	size_t code_capacity;
};


void OpenFile(FILE** openfile, const char filename[], const char format[]);
void InitCPU(CPU& processor, size_t start_capacity);
void ClearCPU(CPU& processor);