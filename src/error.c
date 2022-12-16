#include "../inc/minishell.h"

int	parserError(char *error)
{
	if (!(ft_strcmp(error, "\'")) || !(ft_strcmp(error, "\"")))
		write(1, "minishell: unexpected EOF while looking for matching '", 54);
	else
		write(1, "minishell:syntax error near unexpected token '", 46);
	ft_putstr_fd(error, 1);
	write(1, "\'", 1);
	write(1, "\n", 1);
	return (1);
}

