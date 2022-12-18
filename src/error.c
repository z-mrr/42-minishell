#include "../inc/minishell.h"

/*
void	redirecErros(char *error, int redir)
{
	if (redir == 1)
		write(1, )
}
*/

int	parserError(t_sh *f, char *error)
{
	if (!(ft_strcmp(error, "\'")) || !(ft_strcmp(error, "\"")))
	{
		write(1, "minishell: unexpected EOF while looking for matching '", 54);
		ft_putstr_fd(error, 1);
		write(1, "\'\n", 2);
	}
	else if (!(ft_strcmp(error, "|")))
		write(1, "minishell: syntax error near unexpected token '|'\n", 50);
	/*else if (redir != 0)
		redirecErrors(error, redir);*/
	if (f->token)
		free_token(f);
	if (f->cmd)
		free_cmd(f);
	return (1);
}

void	p_error(int status, char *str)
{
	g_status = errno;
	if (status != -2)
		g_status = status;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
}
