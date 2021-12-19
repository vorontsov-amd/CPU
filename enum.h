#pragma once

#define DEF_CMD(name, num, ...)       \
	CMD_##name = num,				   \

enum CMD
{
	#include "commands"
};

#undef DEF_CMD
