/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:37:29 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* devolve pathname inteiro do ficheiro */
char	*get_filepathname(char *path, t_token *token)
{
	char	*pathname;

	pathname = NULL;
	if (token->word[0] == '/' || (token->word[0] == '.'
			&& token->word[1] == '/') || (token->word[0] == '~'
			&& token->word[1] == '/'))
	{
		pathname = ft_strdup(token->word);
		return (pathname);
	}
	pathname = ft_strjoin(path, token->word);
	return (pathname);
}

/* devolve path dor dir onde se vai escrever */
char	*get_filepath(t_sh *f, t_token *token)
{
	char	*path;
	int		i;
	char	*tmp;

	path = NULL;
	if (token->word[0] == '/' || (token->word[0] == '.'
			&& token->word[1] == '/') || (token->word[0] == '~'
			&& token->word[1] == '/'))
	{
		i = ft_strlen(token->word) - 1;
		while (i > -1 && token->word[i] != '/')
			i--;
		path = ft_substr(token->word, 0, i + 1);
		return (path);
	}
	tmp = get_env("PWD", f);
	path = ft_strjoin(tmp, "/");
	free(tmp);
	return (path);
}

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirec_infile(char *pathname, t_cmd *node, t_token *token)
{
	if (access(pathname, F_OK) == 0)
	{
		if (access(pathname, R_OK) == 0)
		{
			node->in_file = open(pathname, O_RDONLY, 0644);
			return (0);
		}
		node->in_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1));
	}
	node->in_file = -2;
	return (p_error("minishell: ", token->word,
			": No such file or directory", 1));
}

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirec_outfile(char *pathname, t_cmd *n, t_token *token)
{
	if (is_dir(pathname) == 1)
	{
		n->out_file = -2;
		return (p_error("minishell: ", token->word, ": Is a dir", 1));
	}
	if (access(pathname, F_OK) == 0)
	{
		if (access(pathname, W_OK) == 0)
		{
			if (ft_strcmp(token->prev->word, ">>") == 0)
				n->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				n->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0);
		}
		n->out_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1));
	}
	if (ft_strcmp(token->word, ">>") == 0)
		n->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		n->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0);
}
