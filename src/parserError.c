#include "../inc/minishell.h"

int	parserError(char error)
{
	write(1, "minishell: unexpected EOF while looking for matching '", 54);
	write(1, &error, 1);
	write(1, "\'", 1);
	write(1, "\n", 1);
	return (1);
}
