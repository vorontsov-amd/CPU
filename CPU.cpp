#include "CPU.h"


void InitCPU(CPU& processor, size_t start_capacity)
{
	processor.code = (int*)calloc(start_capacity, sizeof(int));
	processor.ip = 0;
	processor.code_capacity = start_capacity;
	StackCtor(&processor.stack, 20);
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
}


void OpenFile(FILE** openfile, const char filename[], const char format[])
{
	assert(openfile);
	assert(filename);
	assert(format);

	fopen_s(openfile, filename, format);
	if (*openfile == nullptr)
	{
		printf("Error: The Program cannot open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
}