/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:45:04 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (node->in_file = -2);
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
