#pragma once
#include "..\..\CPU.h"
#include "..\..\enum.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>

using namespace sf;

struct CPU
{
	Stack stack;
	Stack callStk;
	char* RAM;
	int* VRAM;
	double registr[4];
	int ip;
	int* code;
	size_t code_capacity;
};

enum Resolution
{
	X = 1280,
	Y = 720,
};

const int PixelSize = 40;
const int MByte = 1024 * 1024;

#define CODE processor.code
#define IP processor.ip
#define REGISTER processor.registr
#define POP(ptr) StackPop(&processor.stack, (element*)(&##ptr));
#define PUSH(num) StackPush(&processor.stack, (element)(num));
#define MODE AnalysMode(processor.code[processor.ip])
#define VIDEORAM processor.VRAM

void InitCPU(CPU& processor, size_t code_capacity, size_t RAM_size);
void ClearCPU(CPU& processor);
void Execute(CPU& processor);
int AnalysMode(int cmd);
