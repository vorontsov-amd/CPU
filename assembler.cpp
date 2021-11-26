#define LOGFILE
#include "assembler.h"

int main()
{
	FILE* input = nullptr;
	OpenFile(&input, "text_command.txt", "rb");

	FILE* output = nullptr;
	OpenFile(&output, "machine_code.bin", "wb");

	CPU assembler = {0};
	InitCPU(assembler, 50);
	//StackCtor(&assembler.stack, 20);
	//ClearCPU(assembler);

	Translate(input, assembler);
	fwrite(assembler.code, assembler.code[0], sizeof(int), output);

	//ClearCPU(assembler);
	fclose(input);
	fclose(output);
	return 0;
}


void Translate(FILE* input, CPU& assembler)
{
	assert(input);

	FILE* listing_ass;
	OpenFile(&listing_ass, "listing_assemblering.txt", "w");

	fprintf(listing_ass, "№ LINE \t\t HEX CMD \t HEX PARAM \t CMD \t PARAM\n");

	assembler.ip = 1;

	char** buffer = FileToBuf(input);

	int i = 0;
	while (buffer[i] != nullptr)
	{
		char nameCommand[MAX_LEN_CMD] = {};
		sscanf_s(buffer[i], "%4s", nameCommand, MAX_LEN_CMD);

		if (assembler.ip == assembler.code_capacity)
		{
			ArrayResize(assembler.code, assembler.code_capacity, assembler.code_capacity * 2);
		}

		if (_stricmp(nameCommand, "push") == 0)
		{
			CHECKSYNTAX(ONE_OPERAND);

			int operand = 0;
			if (sscanf_s(buffer[i], "%*s %d", &operand) == 1)
			{
				assembler.code[assembler.ip++] = CMD_push;
				assembler.code[assembler.ip++] = operand;
				fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %d\n", i, CMD_push, operand, nameCommand, operand);
			}
			else
			{
				assembler.code[assembler.ip++] = CMD_rpush;
				char nameReg[4] = "";
				sscanf_s(buffer[i], "%*s %3s", nameReg, (unsigned)_countof(nameReg));
				if (_stricmp(nameReg, "rax") == 0)
				{
					assembler.code[assembler.ip++] = rax_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_rpush, rax_index, nameCommand, nameReg);

				}
				else if (_stricmp(nameReg, "rbx") == 0)
				{
					assembler.code[assembler.ip++] = rbx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_rpush, rbx_index, nameCommand, nameReg);

				}
				else if (_stricmp(nameReg, "rcx") == 0)
				{
					assembler.code[assembler.ip++] = rcx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_rpush, rcx_index, nameCommand, nameReg);

				}
				else if (_stricmp(nameReg, "rdx") == 0)
				{
					assembler.code[assembler.ip++] = rdx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_rpush, rdx_index, nameCommand, nameReg);

				}
				else
				{
					printf("Syntax error. Unknown oprerator %s in command push in line %d\n", nameReg, i + 1);
				}
			}
			i++;
		}

		else if (_stricmp(nameCommand, "pop") == 0)
		{	
			char operand[4] = "";
			if (sscanf_s(buffer[i], "%*s %3s", operand, (unsigned)_countof(operand)) == -1)
			{
				assembler.code[assembler.ip++] = CMD_pop;
				fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_pop, nameCommand);

			}
			else
			{
				CHECKSYNTAX(ONE_OPERAND);
				
				assembler.code[assembler.ip++] = CMD_rpop;
				if (_stricmp(operand, "rax") == 0)
				{
					assembler.code[assembler.ip++] = rax_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %-4s \t %s\n", i, CMD_rpop, rax_index, nameCommand, operand);

				}
				else if (_stricmp(operand, "rbx") == 0)
				{
					assembler.code[assembler.ip++] = rbx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %-4s \t %s\n", i, CMD_rpop, rbx_index, nameCommand, operand);

				}
				else if (_stricmp(operand, "rcx") == 0)
				{
					assembler.code[assembler.ip++] = rcx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %-4s \t %s\n", i, CMD_rpop, rcx_index, nameCommand, operand);

				}
				else if (_stricmp(operand, "rdx") == 0)
				{
					assembler.code[assembler.ip++] = rdx_index;
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %-4s \t %s\n", i, CMD_rpop, rdx_index, nameCommand, operand);

				}
				else
				{
					printf("Syntax error. Unknown oprerator %s in command pop in line %d\n", operand, i + 1);
				}
			}
			i++;
		}

		else if (_stricmp(nameCommand, "sub") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_sub;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_sub, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "mul") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_mul;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_mul, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "div") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_div;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_div, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "sqrt") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_sqrt;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_sqrt, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "in") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_in;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_in, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "hlt") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_hlt;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_hlt, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "out") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_out;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_out, nameCommand);
			i++;
		}

		else if (_stricmp(nameCommand, "add") == 0)
		{
			CHECKSYNTAX(ZERO_OPERAND);
			assembler.code[assembler.ip++] = CMD_add;
			fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_add, nameCommand);
			i++;
		}

		else
		{
			printf("Syntax Error: Unknown command %s\n", nameCommand);
			i++;
		}
	}

	assembler.code[0] = assembler.ip;
}


bool SyntaxError(char line[], int CountOfOperand)
{
	char Erroperand[2] = "";
	if (CountOfOperand == ONE_OPERAND)
		return !(sscanf_s(line, "%*s %*s %1s", Erroperand, (unsigned)_countof(Erroperand)) == -1);
	else if (CountOfOperand == ZERO_OPERAND)
		return !(sscanf_s(line, "%*s %1s", Erroperand, (unsigned)_countof(Erroperand)) == -1);
}