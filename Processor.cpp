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

	InitCPU(processor, BufferSize, MByte);

	FUCK

	fread(processor.code, BufferSize, sizeof(*processor.code), command);

	FUCK

	Execute(processor);

	ClearCPU(processor);

	fclose(command);
}


#define DEF_CMD(name, num, arg, ...)   				\
	case CMD_##name:					 \
	{						 	  \
		__VA_ARGS__					   \
		processor.ip += (arg + 1);		            \
		break;						     \
	}			

#define DEF_JMP(name, num, sign)							\
	case CMD_##name:								 \
	{										  \
		switch (num) 							           \
		{									    \
			case CMD_call:							     \
			{							 	      \
				StackPush(&processor.callStk, (processor.ip + 1));	       \
				processor.ip = processor.code[processor.ip + 1];		\
				break;								 \
			}									  \
			case CMD_jmp:								   \
			{									    \
				processor.ip = processor.code[processor.ip + 1];		     \
				break;								      \
			}									       \
			default:									\
			{										 \
				double A = 0, B = 0;							  \
				StackPop(&processor.stack, &B);						   \
				StackPop(&processor.stack, &A);						    \
				if (B ##sign## A)							     \
				{									      \
					processor.ip = processor.code[processor.ip + 1];		       \
				}										\
				break;										 \
			}											  \
		}											           \
		break;											            \
	}		



void Execute(CPU& processor)
{
	RenderWindow window(VideoMode(X, Y), "RT!!!");
	processor.ip = 1;
	while (processor.ip < processor.code_capacity)
	{
		int default_cmd = processor.code[processor.ip] & ~NUMBER & ~REGISTR & ~VRAM;
		switch (default_cmd)
		{
			#include "../../commands"
			default: printf("Error: Uncnown CMD %d", default_cmd);
		}
	}
	out:;
}

#undef DEF_CMD
#undef DEF_JMP

void InitCPU(CPU& processor, size_t code_capacity, size_t RAM_size)
{
	processor.RAM = (char*)calloc(RAM_size, sizeof(char));

	if (processor.RAM == nullptr)
	{
		puts("Error. Not enough free memory");
		exit(EXIT_FAILURE);
	}

	processor.ip = 0;
	processor.code_capacity = code_capacity;
	int* free_ptr = (int*)StackCtor(&processor.stack, RAM_size / 10, (element*)processor.RAM);
		 free_ptr = (int*)StackCtor(&processor.callStk, RAM_size / 10, (element*)free_ptr);

	processor.code = free_ptr;
	processor.VRAM = free_ptr + code_capacity;
	for (int i = 0; i < 4; i++)
	{
		processor.registr[i] = 0;
	}
}

void ClearCPU(CPU& processor)
{
	free(processor.RAM);
}


int AnalysMode(int cmd)
{	
	if ((cmd & ~VRAM | NUMBER) == cmd)
		return NUMBER;
	else if ((cmd & ~VRAM | REGISTR) == cmd)
		return REGISTR;
	else if ((cmd | VRAM | REGISTR) == cmd)
		return REGISTR | VRAM;
	else if ((cmd | VRAM | NUMBER) == cmd)
		return NUMBER | VRAM;
}
