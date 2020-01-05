#include "monty.h"

/**
 * get_op - Gets an operation according to the selected opcode.
 *
 *
 * @command: opcode.
 *
 *
 * Description - This program will select a function according to the opcode.
 *
 *
 * Return: → Nothing (void).
 *
 */

void *get_op(char *command, unsigned int line_number)
{
	instruction_t op[] = {
		{"push", op_push},
		{"pall", op_pall},
		{"pint", op_pint},
		{"pop", op_pop},
		{"swap", op_swap},
		{"add", op_add},
		{"nop", op_nop},
		{NULL, NULL}
	};
	char *_push = strstr(command, "push");
	void *function;
	int index = 1;

	if (_push)
		function = (op[0].f);

	else
	{
		while (index < 7)
		{
			if (strcmp(command, op[index].opcode))
				function = (op[index].f);
		}
		index++;
	}
	exec = function(stack_t, line_number);
	exec();
}
