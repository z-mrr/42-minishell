/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:45:04 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/23 02:45:26 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*heredoc_nstr(char *str, char *buffer)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strjoin(str, "\n");
	free(str);
	str = ft_strjoin(tmp, buffer);
	free(tmp);
	return (str);
}

int	heredocfd(t_cmd *node, char *str)
{
	char	*tmp;
	int		fd[2];

	tmp = NULL;
	if (node->in_file != STDIN_FILENO
		&& node->in_file != -2 && node->in_file != -1)
		close(node->in_file);
	if (pipe(fd) == -1)
		return (g_status = 1);
	if (str)
	{
		tmp = ft_strjoin(str, "\n");
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
		write(fd[WRITE], str, ft_strlen(str));
		free(str);
		close(fd[WRITE]);
		node->in_file = fd[READ];
	}
	else
		node->in_file = -2;
	return (0);
}

int	handle_quit(t_cmd *node, char *buff, char *s, char *eof)
{
	printf("-minishell: warning: heredoc delimited by EOF (wanted `%s')\n", eof);
	free(buff);
	free(s);
	return (node->in_file = -2);
}

/* heredoc: writes to a str lines read by newline until eof */
int	redir_heredoc(t_cmd *node, char *eof)
{
	char	*str;
	char	*buffer;

	g_status = 0;
	str = NULL;
	buffer = NULL;
	while (g_status != 130)
	{
		buffer = readline("> ");
		if (!buffer)
			return (handle_quit(node, buffer, str, eof));
		if (str && ft_strcmp(buffer, eof) != 0)
			str = heredoc_nstr(str, buffer);
		else if (ft_strcmp(buffer, eof) != 0)
			str = ft_strdup(buffer);
		if (ft_strcmp(buffer, eof) == 0)
		{
			free(buffer);
			return (heredocfd(node, str));
		}
		free(buffer);
		if (g_status == 130)
			free(str);
	}
	return (1);
}
