#include "disassm.h"

int main()
{
	FILE* machine_code = nullptr;
	OpenFile(&machine_code, "machine_code.bin", "rb");

	FILE* text_code = nullptr;
	OpenFile(&machine_code, "text_code.txt", "w");

	int BufferSize = 0;
	fread(&BufferSize, 1, sizeof(int), machine_code);
	rewind(machine_code);

	CPU disassembler = {};
	InitCPU(disassembler, BufferSize);
	fread(disassembler.code, disassembler.code_capacity, sizeof(int), machine_code);

	Translate(disassembler, text_code);

	fclose(machine_code);
	fclose(text_code);
}



void Translate(CPU disassembler, FILE* output)
{
	disassembler.ip = 1;
	while (disassembler.ip < disassembler.code_capacity)
	{
		switch (disassembler.code[disassembler.ip])
		{
			case CMD_add:
			{
				fputs("Add\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_div:
			{
				fputs("Div\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_hlt:
			{
				fputs("Hlt\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_in:
			{
				fputs("In\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_mul:
			{
				fputs("Mul\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_out:
			{
				fputs("Out\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_pop:
			{
				fputs("Pop\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_sqrt:
			{
				fputs("Sqrt\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_sub:
			{
				fputs("Sub\n", output);
				disassembler.ip++;
				break;
			}
			case CMD_push:
			{
				fputs("Push ", output);
				disassembler.ip++;
				fprintf(output, "%d", disassembler.code[disassembler.ip++]);
				break;
			}
			case CMD_rpush:
			{
				fputs("Push ", output);
				disassembler.ip++;
				switch (disassembler.code[disassembler.ip++])
				{
				case rax_index:
					fputs("rax\n", output);
					break;
				case rbx_index:
					fputs("rbx\n", output);
					break;
				case rcx_index:
					fputs("rcx\n", output);
					break;
				case rdx_index:
					fputs("rdx\n", output);
					break;
				default:
					fprintf(output, "UNCNOWN CMD %d", disassembler.code[disassembler.ip - 1]);
					break;
				}
				break;
			}
			case CMD_rpop:
			{
				fputs("Pop ", output);
				disassembler.ip++;
				switch (disassembler.code[disassembler.ip++])
				{
				case rax_index:
					fputs("rax\n", output);
					break;
				case rbx_index:
					fputs("rbx\n", output);
					break;
				case rcx_index:
					fputs("rcx\n", output);
					break;
				case rdx_index:
					fputs("rdx\n", output);
					break;
				default:
					fprintf(output, "UNCNOWN CMD %d", disassembler.code[disassembler.ip - 1]);
					break;
				}
				break;
			}
			default:
			{
				fputs("Programm cannot translate incorrectly compiled code\n", output);
				break;
			}
		}
	}
}