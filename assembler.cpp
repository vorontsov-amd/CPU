//#define DEBUG
#include "assembler.h"

int main()
{
	FILE* input = nullptr;
	OpenFile(&input, "..\\..\\text_command.txt", "rb");

	FUCK


	FILE* output = nullptr;
	OpenFile(&output, "..\\..\\machine_code.bin", "wb");

	FUCK

	FILE* outputTXT = nullptr;
	OpenFile(&outputTXT, "..\\..\\machine_code.txt", "w");

	FUCK

	int * code = new int[FileSize(input)];

	Translate(input, code);

	FUCK

	fwrite(code, code[0], sizeof(int), output);

	FUCK

	for (int i = 0; i < code[0]; i++)
		fprintf(outputTXT, "%d ", code[i]);

	FUCK

	fclose(input);
	fclose(output);
	fclose(outputTXT);
	delete[] code;
	return 0;
}

#define IF_REG(name, registr)										 					\
		if (_stricmp(nameReg, #registr) == 0)												 \
		{																  \
			code[ip++] = CMD_##name | REGISTR;											   \
			code[ip++] = registr##_index;												    \
			fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_##name | REGISTR, registr##_index, nameCommand, nameReg); \
		}	



#define IF_RAM(name, registr)																       \
		if (_stricmp(nameReg, #registr) == 0)													 	\
		{																		 \
			code[ip++] = CMD_##name | REGISTR | VRAM;												  \
			code[ip++] = registr##_index;														   \
			fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t [%s]\n", i, CMD_##name | REGISTR | VRAM, registr##_index, nameCommand, nameReg);	    \
		}	




#define DEF_CMD(name, num, args, ...)													     \
		if (_stricmp(nameCommand, #name) == 0)											      \
		{															       \
			CHECK_SYNTAX(args);												        \
			if (args == 0)													         \
			{														          \
				code[ip++] = CMD_##name;										           \
				fprintf(listing_ass, "%08d \t %08X \t          \t %4s\n", i, CMD_##name, nameCommand);			            \
			}															     \
			if (args == 1)														      \
			{															       \
				if (AnalysSyntax(buffer[i]) == NUMBER)										   	\
				{														    	 \
					int operand = 0;											     	  \
					sscanf_s(buffer[i], "%*s %d", &operand);								      	   \
					code[ip++] = CMD_##name | NUMBER;									       	    \
					code[ip++] = operand;												     \
					fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %d\n", i, CMD_##name | NUMBER, operand, nameCommand, operand);   \
				}															       \
				if (AnalysSyntax(buffer[i]) == REGISTR)												\
				{																 \
					char nameReg[4] = "";													  \
					sscanf_s(buffer[i], "%*s %3s", nameReg, (unsigned)_countof(nameReg));					    		   \
					IF_REG(name, rax)													    \
					else IF_REG(name, rbx) 													     \
					else IF_REG(name, rcx)													      \
					else IF_REG(name, rdx)													       \
					else																\
					{																 \
						printf("Syntax error. Unknown oprerator %s in command push in line %d\n", nameReg, i + 1);                                \
					}																   \
				}																	    \
				if (AnalysSyntax(buffer[i]) == VRAM)													     \
				{																	      \
					if (OperandIsNumber(buffer[i]))													       \
					{																	\
						int operand = GetOperandNumber(buffer[i]);											 \
						code[ip++] = CMD_##name | NUMBER | VRAM;											  \
						code[ip++] = operand;														   \
						fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t [%d]\n", i, CMD_##name | NUMBER | VRAM, operand, nameCommand, operand);        \
					}																	     \
					else																	      \
					{																	       \
						char * nameReg = GetOperandRegister(buffer[i]);												\
						IF_RAM(name, rax)															 \
						else IF_RAM(name, rbx) 															  \
						else IF_RAM(name, rcx)															   \
						else IF_RAM(name, rdx)															    \
						else																	     \
						{																	      \
							printf("Syntax error. Unknown oprerator %s in command push in line %d\n", nameReg, i + 1);    					       \
						}																		\
					}																			 \
				}																				  \
			}																					   \
			i++;																					    \
		} else


#define DEF_JMP(name, num, sign)			 									    \
	if(_stricmp(nameCommand, #name) == 0)											     \
	{															      \
		label_t getLabel = FindLabel(buffer[i], label);									       \
		code[ip++] = CMD_##name;												\
		code[ip++] = getLabel.pointer;												 \
		fprintf(listing_ass, "%08d \t %08X \t %08X \t %4s \t %s\n", i, CMD_##name, getLabel.pointer, nameCommand, getLabel.mark); \
		i++;																													   \
	}																																\
	else

void Translate(FILE* input, int* code)
{
	assert(input);
	assert(code);

	FILE* listing_ass = nullptr;
	OpenFile(&listing_ass, "..\\..\\listing_assemblering.txt", "w");

	fprintf(listing_ass, "№ LINE \t\t HEX CMD \t HEX PARAM \t CMD \t PARAM\n");

	int ip = 1;
	char** buffer = FileToBuf(input);

	static Label label = LabelCtor(label);

	int i = 0;
	while (buffer[i] != nullptr)
	{
		char nameCommand[MAX_LEN_CMD] = {};
		sscanf_s(buffer[i], "%4s", nameCommand, MAX_LEN_CMD);

		if (strlen(nameCommand) == 0)
		{
			i++;
			continue;
		}

		if (IsMark(buffer[i]))
		{
			if (label.status == LOADING)
				AddLabel(buffer[i], label, ip);
			i++;
			continue;
		}

		#include "..\..\commands"

		/*else*/ {
			printf("Syntax Error: Unknown command _%s_\n", nameCommand);
			i++;
		}
	}

	code[0] = ip;
	fclose(listing_ass);

	if (label.status == LOADING)
	{
		label.status = COMPLETED;
		Translate(input, code);
	}
}

#undef IF_REG
#undef IF_RAM
#undef DEF_CMD
#undef DEF_JMP



Label& LabelCtor(Label& label, int capacity)
{
	label.capacity = capacity;
	label.size = 0;
	label.label = (label_t*)calloc(capacity, sizeof(label_t));
	label.status = LOADING;
	return label;
}

inline bool IsMark(const char str[])
{
	return strchr(str, ':') != nullptr;
}

void AddLabel(const char str[], Label& label, const int index)
{
	if (label.size == label.capacity)
		ArrayResize<label_t>(label.label, label.capacity, 2 * label.capacity);
	
	char mark[MAX_LEN_LABEL_NAME + 2] = "$ ";
	sscanf_s(str, "%19[^:]", mark + 2, MAX_LEN_LABEL_NAME);

	label_t check = FindLabel(mark, label);

	if (LabelNotCreated(check))
	{
		label.label[label.size].pointer = index;
		strcpy_s(label.label[label.size].mark, mark + 2);
		label.size++;
	}

	else
	{
		puts("Error. Ambiguous use of lables\n");
	}

}

label_t FindLabel(char str[], Label& label)
{
	char mark[MAX_LEN_LABEL_NAME] = "";
	sscanf_s(str, "%*s %19s", mark, MAX_LEN_LABEL_NAME);
	bool find_flag = false;
	int i = 0;

	for (i; i != label.size; i++)
	{
		if (_stricmp(mark, label.label[i].mark) == 0)
		{
			find_flag = true;
			return label.label[i];
		}
	}
	return NoFindLabel;
}

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

	return true;
}

int AnalysSyntax(char line[])
{
	int cringe = 0;
	char kok[10] = "";
	if (sscanf_s(line, "%*s %d", &cringe) == 1)
		return NUMBER;
	else
	{
		sscanf_s(line, "%*s %9s", kok, (unsigned)_countof(kok));
		if ((strchr(kok, '[') != nullptr) && (strchr(kok, ']') != nullptr))
		{
			return VRAM;
		}
		else if ((strchr(kok, '[') != nullptr) || (strchr(kok, ']') != nullptr))
		{
			puts("SYNTAX ERROR");
			exit(EXIT_FAILURE);
		}
		else return REGISTR;
	}
}

bool OperandIsNumber(char line[])
{
	char arg[10] = "";
	sscanf_s(line, "%*s %9s", arg, (unsigned)_countof(arg));
	for (int i = 0; i < 10; i++)
		arg[i] = arg[i + 1];
	*strchr(arg, ']') = '\0';
	int number = 0;
	sscanf_s(arg, "%d", &number);
	return sscanf_s(arg, "%d", &number) == 1;
}

int GetOperandNumber(char line[])
{
	char arg[10] = "";
	sscanf_s(line, "%*s %9s", arg, (unsigned)_countof(arg));
	for (int i = 0; i < 10; i++)
		arg[i] = arg[i + 1];
	*strchr(arg, ']') = '\0';
	int number = 0;
	sscanf_s(arg, "%d", &number);
	return number;
}

char* GetOperandRegister(char line[])
{
	static char arg[10] = "";
	sscanf_s(line, "%*s %9s", arg, (unsigned)_countof(arg));
	for (int i = 0; i < 10; i++)
		arg[i] = arg[i + 1];
	*strchr(arg, ']') = '\0';
	return arg;
}

inline bool LabelNotCreated(label_t label)
{
	return (_strcmpi(label.mark, "Unknown") == 0 and label.pointer == -1);
}
