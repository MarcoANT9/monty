#include "monty.h"

/**
 * malloc_fail - Function for when malloc fails.
 *
 * Description - Prints error message.
 *
 * Return: Nothing (void)
 */

void malloc_fail(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}


/**
 * clean_command - Cleans a opcommand of spaces and other strings.
 *
 * @buffer: Buffer read from the file.
 *
 * Description - Cleans a command for better understanding.
 *
 * Return: → Pointer to a clean command.
 *         → Null on failure.
 */

char *clean_command(char *buffer)
{
	char *new_comm, *push = "push";
	int index = 0, jndex, pndex = 0;

	while (buffer[index] == ' ' && buffer[index] != '\n')
		index++;
	while (buffer[index] != ' ' && buffer[index] != '\n')
	{
		if (buffer[index] == push[pndex])
			pndex++; /** To know if the opcode is "push" */
		index++, jndex++; /** How many words there are in the opcode */
	}
	if (jndex == pndex) /** The opcode is "Push" */
	{
		while (buffer[index] == ' ' && buffer[index] != '\n')
			index++;
		while (buffer[index] != ' ' && buffer[index] != '\n')
		{
			index++, jndex++;
		}
	} /** Argument to "push" is counted */
	new_comm = malloc(sizeof(char) * (jndex + 1));
	if (new_comm == NULL)
		malloc_fail();
	index = 0, jndex = 0;
	while (buffer[index] == ' ' && buffer[index] != '\n')
		index++;
	while (buffer[index] != ' ' && buffer[index] != '\n')
	{
		new_comm[jndex] = buffer[index], index++, jndex++;
	}
	if (pndex == 4) /** The command is PUSH */
	{
		while (buffer[index] == ' ' && buffer[index] != '\n')
			index++;
		while (buffer[index] != ' ' && buffer[index] != '\n')
		{new_comm[jndex] = buffer[index];
			index++, jndex++;
		}
	} new_comm[jndex] = '\0';
	return (new_comm);
}

/**
 * read_line - Compares the line with the opcommands.
 *
 * @file_line: Line the file is currently in.
 * @clean_command: Opcode clean.
 *
 * Description - This program takes a line from a file and compares it to a
 *               dictionary of opcodes to see if it can execute it, then it
 *               directions the corresponding function. The function returns
 *               0 on success and 1 on failure.
 *
 * Return: → 0 on success.
 *         → 1 on failure.
 *
 */

int read_line(unsigned int file_line, char *clean_command)
{
	char *oplist[] = {"push", "pall", "pint", "pop", "swap", "add", "nop",
			  NULL};
	int index = 0, jndex, eq = 0;

	while (oplist[index] != NULL)
	{
		jndex = 0;
		while (oplist[index][jndex] != '\0')
		{
			if (oplist[index][jndex] == clean_command[jndex])
			{
				eq = 1;
				jndex++;
			}
			else
			{
				eq = 0;
				break;
			}
		}
		if (eq == 1)
			break;
		index++;
	}
	if (eq == 0)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", file_line,
			clean_command);
		return (1);
	}
	get_op(clean_command, file_line);
	return (0);
}


/**
 * main - Main function
 *
 * @argc: Number of arguments
 * @argv: List of arguments
 *
 *
 * Description - This program will take a path to a monty file and interpret
 *               commands for execution.
 *
 *
 *
 * Return: → 0 on success.
 *         → 1 on failure.
 *
 */

int main(int argc, char **argv)
{
	FILE *file;
	unsigned int file_line = 1;
	size_t line_len = 0;
	char *buffer = NULL, *clean_op;
	ssize_t rd;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((rd = getline(&buffer, &line_len, file)) != -1)
	{
		if (*buffer == '\n')
			file_line++;
		else
		{
			clean_op = clean_command(buffer); /** Malloc inside */
			if (read_line(file_line, clean_op) == 1)
			{
				free(clean_op);
				exit(EXIT_FAILURE);
			}
			free(clean_op);
			file_line++;
		}
	}
	fclose(file);
	return (0);
}
