#pragma once

enum NumOperand
{
	ZERO_OPERAND = 0,
	ONE_OPERAND = 1,
};

enum CommandMode
{
	NUMBER = 0x80000000,
	REGISTR = 0x40000000,
	VRAM = 0x20000000,
};

enum RegistIndex
{
	rax_index,
	rbx_index,
	rcx_index,
	rdx_index,
};


#define DEF_CMD(name, num, ...)       \
	CMD_##name = num,		


#define DEF_JMP(name, num, ...)			   \
	CMD_##name = num,

enum CMD
{
	#include "commands"
};

#undef DEF_CMD
#undef DEF_JMP
