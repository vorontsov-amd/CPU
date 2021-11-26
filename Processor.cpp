#include "Processor.h"

int main()
{
	FILE* command = nullptr;
	OpenFile(&command, "machine_code.bin", "rb");

	long long BufferSize = 0;
	fread(&BufferSize, 1, sizeof(int), command);
	rewind(command);

	CPU processor = {};

	InitCPU(processor, BufferSize);

	fread(processor.code, BufferSize, sizeof(*processor.code), command);

	Execute(processor);

	fclose(command);
}


void Execute(CPU& processor)
{
	processor.ip = 1;
	while (processor.ip < processor.code_capacity)
	{
		switch (processor.code[processor.ip])
		{
		case CMD_push:
		{
			StackPush(&processor.stack, processor.code[++processor.ip]);
			processor.ip++;
			break;
		}
		case CMD_rpush:
		{
			StackPush(&processor.stack, processor.registr[processor.code[++processor.ip]]);
			processor.ip++;
			break;
		}
		case CMD_pop:
		{
			element var = 0;
			StackPop(&processor.stack, &var);
			processor.ip++;
			break;
		}
		case CMD_rpop:
		{
			element variable = 0;
			StackPop(&processor.stack, &variable);
			processor.registr[processor.code[++processor.ip]] = variable;
			processor.ip++;
			break;
		}
		case CMD_add:
		{
			element a = 0, b = 0;
			StackPop(&processor.stack, &a);
			StackPop(&processor.stack, &b);
			StackPush(&processor.stack, a + b);
			processor.ip++;
			break;
		}
		case CMD_div:
		{
			element a = 0, b = 0;
			StackPop(&processor.stack, &a);
			StackPop(&processor.stack, &b);
			StackPush(&processor.stack, b / a);
			processor.ip++;
			break;
		}
		case CMD_in:
		{
			element variable = 0;
			fscanf_s(stdin, EL, &variable);
			StackPush(&processor.stack, variable);
			processor.ip++;
			break;
		}
		case CMD_mul:
		{
			element a = 0, b = 0;
			StackPop(&processor.stack, &a);
			StackPop(&processor.stack, &b);
			StackPush(&processor.stack, a * b);
			processor.ip++;
			break;
		}
		case CMD_out:
		{
			element variable;
			StackPop(&processor.stack, &variable);
			printf(EL, variable);
			processor.ip++;
			break;
		}
		case CMD_sqrt:
		{
			element variable;
			StackPop(&processor.stack, &variable);
			StackPush(&processor.stack, (element)sqrtl(variable));
			processor.ip++;
			break;
		}
		case CMD_sub:
		{
			element a = 0, b = 0;
			StackPop(&processor.stack, &a);
			StackPop(&processor.stack, &b);
			StackPush(&processor.stack, b - a);
			processor.ip++;
			break;
		}
		case CMD_hlt:
		{
			goto out;
		}
		default:
		{
			printf("An unknown command with code %d was detected.Recompile the input file", processor.code[processor.ip]);
			exit(EXIT_FAILURE);
			break;
		}
		}
	}
	out:{;}
}