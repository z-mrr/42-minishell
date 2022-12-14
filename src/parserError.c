#include "../inc/minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &(str[i]), 1);
		i++;
	}
}

int	parserError(t_sh *f, char *error)
{
	if (!(ft_strcmp(error, "\'")) || !(ft_strcmp(error, "\"")))
		write(1, "minishell: unexpected EOF while looking for matching '", 54);
	else
		write(1, "minishell: syntax error near unexpected token '", 47);
	ft_putstr(error);
	write(1, "\'", 1);
	write(1, "\n", 1);
	if (f->token)
		freeTokens(f);
	if (f->cmd)
		free_list(f);
	return (1);
}
