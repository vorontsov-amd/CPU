//#define DEBUG
#include "Processor.h"

int main()
{
	FILE* command = nullptr;
	OpenFile(&command, "..\\..\\machine_code.bin", "rb");
	
	FUCK

	long long BufferSize = 0;
	fread(&BufferSize, 1, sizeof(int), command);
	rewind(command);

	FUCK

	CPU processor = {};

	InitCPU(processor, BufferSize);

	FUCK

	fread(processor.code, BufferSize, sizeof(*processor.code), command);

	FUCK

	Execute(processor);

	ClearCPU(processor);

	fclose(command);
}


#define DEF_CMD(name, num, arg, ...)         \
	case CMD_##name:		      \
	{				       \
		__VA_ARGS__			\
		processor.ip += (arg + 1);       \
		break;				  \
	}			

#define DEF_JMP(name, num, sign)					    \
	case CMD_##name:						     \
	{								      \
		switch (num) 						       \
		{							        \
			case CMD_call:					         \
			{							  \
				StackPush(&processor.callStk, (processor.ip + 1)); \
				processor.ip = processor.code[processor.ip + 1];    \
				break;						     \
			}							      \
			case CMD_jmp:						       \
			{								\
				processor.ip = processor.code[processor.ip + 1];         \
				break;							  \
			}								   \
			default:							    \
			{								     \
				double A = 0, B = 0;					      \
				StackPop(&processor.stack, &B);				       \
				StackPop(&processor.stack, &A);					\
				if (B ##sign## A)						 \
				{								  \
					processor.ip = processor.code[processor.ip + 1];	   \
				}								    \
				break;								     \
			}									      \
		}								 		       \
		break;											\
	}										   



void Execute(CPU& processor)
{
	processor.ip = 1;
	while (processor.ip < processor.code_capacity)
	{
		int default_cmd = processor.code[processor.ip] & ~NUMBER & ~REGISTR;
		switch (default_cmd)
		{
			#include "../../commands"
			default: printf("Error: Uncnown CMD %d", default_cmd);
		}
	}
	out:;
}

#undef DEF_CMD


void InitCPU(CPU& processor, size_t start_capacity)
{
	processor.code = (int*)calloc(start_capacity, sizeof(int));
	processor.ip = 0;
	processor.code_capacity = start_capacity;
	StackCtor(&processor.stack, 20);
	StackCtor(&processor.callStk, 20);
	for (int i = 0; i < 4; i++)
	{
		processor.registr[i] = 0;
	}

	if (processor.code == nullptr)
	{
		puts("Error. Not enough free memory");
		exit(EXIT_FAILURE);
	}
}

void ClearCPU(CPU& processor)
{
	free(processor.code);
	StackDtor(&processor.stack);
	StackDtor(&processor.callStk);
}


int AnalysMode(int cmd)
{
	if ((cmd | NUMBER) == cmd)
		return NUMBER;
	else if ((cmd | REGISTR) == cmd)
		return REGISTR;
}
