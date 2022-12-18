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

int	p_error(char *s1, char *s2, char *s3, char *s4, int status)
{
	if (status)
		g_status = status;
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putstr_fd(s4, STDERR_FILENO);
	return (0);
}
