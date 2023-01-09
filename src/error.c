/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:29:06 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	redir_error(char *word, char *error, )

*/

int	parser_error(t_sh *f, char *error)
{
	if (!(ft_strcmp(error, "\'")) || !(ft_strcmp(error, "\"")))
	{
		write(1, "minishell: unexpected EOF while looking for matching '", 54);
		ft_putstr_fd(error, 1);
		write(1, "\'\n", 2);
	}
	else if (!(ft_strcmp(error, "|")))
		write(1, "minishell: syntax error near unexpected token '|'\n", 50);
	if (f->token)
		free_tokens(f);
	if (f->cmd)
		free_cmd(f);
	return (1);
}

int	p_error(char *s1, char *s2, char *s3, int status)
{
	ft_putstr_fd(s1, STDERR_FILENO);
	ft_putstr_fd(s2, STDERR_FILENO);
	ft_putstr_fd(s3, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (g_status = status);
}
