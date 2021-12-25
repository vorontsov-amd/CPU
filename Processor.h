#pragma once
#include "..\..\CPU.h"
#include "..\..\enum.h"


struct CPU
{
	Stack stack;
	double registr[4];
	int ip;
	int* code;
	size_t code_capacity;
};


#define CODE processor.code
#define IP processor.ip
#define REGISTER processor.registr
#define POP(ptr) StackPop(&processor.stack, (element*)(&##ptr));
#define PUSH(num) StackPush(&processor.stack, (element)(num));
#define MODE AnalysMode(processor.code[processor.ip])

void InitCPU(CPU& processor, size_t start_capacity);
void ClearCPU(CPU& processor);
void Execute(CPU& processor);
int AnalysMode(int cmd);
