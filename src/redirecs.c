/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 02:04:22 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_opendir(char *path, t_cmd *node, t_token *token)
{
	DIR		*dir;
	char	*pathname;
	int		i;

	pathname = NULL;
	dir = opendir(path);
	pathname = get_filepathname(path, token);
	free(path);
	i = redirec_infile(pathname, node, token);
	closedir(dir);
	free(pathname);
	return (i);
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redir_in(t_sh *f, t_cmd *node, t_token *token)
{
	char	*path;

	path = NULL;
	path = get_filepath(f, token);
	if (node->in_file != STDIN_FILENO
		&& node->in_file != -2 && node->in_file != -1)
	{
		close(node->in_file);
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, R_OK) == 0)
			return (_opendir(path, node, token));
		free(path);
		node->in_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1));
	}
	node->in_file = -2;
	return (p_error("minishell: ", token->word, \
": No such file or directory", 1));
}

int	_opendirout(char *path, t_cmd *node, t_token *token)
{
	DIR		*dir;
	char	*pathname;
	int		i;

	pathname = NULL;
	dir = opendir(path);
	pathname = get_filepathname(path, token);
	free(path);
	i = redirec_outfile(pathname, node, token);
	closedir(dir);
	free(pathname);
	return (i);
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redir_out(t_sh *f, t_cmd *node, t_token *token)
{
	char	*path;

	path = NULL;
	path = get_filepath(f, token);
	if (node->out_file != STDOUT_FILENO
		&& node->out_file != -2 && node->out_file != -1)
	{
		close(node->out_file);
	}
	if (access(path, F_OK) == 0)
		return (_opendirout(path, node, token));
	node->out_file = -2;
	return (p_error("minishell: ", token->word,
			": No such file or directory", 1));
}

int	parse_redirecs(t_sh *f, t_cmd *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0
		|| ft_strcmp(token->word, ">>") == 0)
		return (redir_out(f, node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (redir_in(f, node, token->next));
	if (ft_strcmp(token->word, "<<") == 0)
		return (redir_heredoc(node, token->next->word));
	return (0);
}
