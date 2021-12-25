//#define DEBUG
#include "assembler.h"

int main()
{
	FILE* input = nullptr;
	OpenFile(&input, "..\\..\\text_command.txt", "rb");

	FUCK;

	FILE* output = nullptr;
	OpenFile(&output, "..\\..\\machine_code.bin", "wb");

	FUCK;
	
	int * code = new int[FileSize(input)];

	FUCK;

	Translate(input, code);

	FUCK;

	fwrite(code, code[0], sizeof(int), output);

	fclose(input);
	fclose(output);
	return 0;
}

#define IF(name, registr)															      \
		if (_stricmp(nameReg, #registr) == 0)												       \
		{																        \
			code[ip++] = CMD_##name | REGISTR;												 \
			code[ip++] = registr##_index;													  \
			fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_##name | REGISTR, registr##_index, nameCommand, nameReg);	   \
		}																																		      




#define DEF_CMD(name, num, args, ...)																 \
		if (_stricmp(nameCommand, #name) == 0)														  \
		{																		   \
			CHECK_SYNTAX(args);															    \
			if (args == 0)																     \
			{																	      \
				code[ip++] = CMD_##name;													       \
				fprintf(listing_ass, "%08d \t %08X \t\t\t\t %s\n", i, CMD_##name, nameCommand);							        \
			}																		 \
			if (args == 1)																	  \
			{																		   \
				if (AnalysSyntax(buffer[i]) == NUMBER)													    \
				{																	     \
					int operand = 0;														      \
					sscanf_s(buffer[i], "%*s %d", &operand);									 		       \
					code[ip++] = CMD_##name | NUMBER;													\
					code[ip++] = operand;															 \
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %d\n", i, CMD_##name | NUMBER, operand, nameCommand, operand);                       \
				}																		   \
				if (AnalysSyntax(buffer[i]) == REGISTR)														    \
				{																		     \
					char nameReg[4] = "";														  	      \
					sscanf_s(buffer[i], "%*s %3s", nameReg, (unsigned)_countof(nameReg));					                                       \
					IF(name, rax)																	\
					else IF(name, rbx) 																 \
					else IF(name, rcx)																  \
					else IF(name, rdx)																   \
					else																		    \
					{																		     \
						printf("Syntax error. Unknown oprerator %s in command push in line %d\n", nameReg, i + 1);   						      \
					}																		       \
				}																				\
			}																					 \
			i++;																					  \
		} else


void Translate(FILE* input, int* code)
{
	assert(input);

	FILE* listing_ass = nullptr;
	OpenFile(&listing_ass, "..\\..\\listing_assemblering.txt", "w");

	FUCK;

	fprintf(listing_ass, "№ LINE \t\t HEX CMD \t HEX PARAM \t CMD \t PARAM\n");

	int ip = 1;
	char** buffer = FileToBuf(input);

	FUCK;

	int i = 0;
	while (buffer[i] != nullptr)
	{
		char nameCommand[MAX_LEN_CMD] = {};
		sscanf_s(buffer[i], "%4s", nameCommand, MAX_LEN_CMD);

		FUCK;	

		#include "..\..\commands"

		/*else*/ {
			printf("Syntax Error: Unknown command %s\n", nameCommand);
			i++;
		}
		FUCK;
	}

	code[0] = ip;
}

#undef IF
#undef DEF_CMD


bool SyntaxError(char line[], int CountOfOperand)
{
	char Erroperand[2] = "";

	if (CountOfOperand == ONE_OPERAND)
	{

		return (sscanf_s(line, "%*s %*s %1s", Erroperand, (unsigned)_countof(Erroperand)) != -1);
	}
	else if (CountOfOperand == ZERO_OPERAND)
	{
		return (sscanf_s(line, "%*s %1s", Erroperand, (unsigned)_countof(Erroperand)) != -1);
	}
}

int AnalysSyntax(char line[])
{
	int cringe = 0;
	if (sscanf_s(line, "%*s %d", &cringe) == 1)
		return NUMBER;
	else return REGISTR;
}
