/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 02:04:22 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/17 14:52:09 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirec_infile(char *pathname, t_cmd *node, t_token *token)
{
	if (access(pathname, F_OK) == 0) /* existe ficheiro */
	{
		if (access(pathname, R_OK) == 0) /* podemos ler */
		{
			node->in_file = open(pathname, O_RDONLY, 0644);
			return (0); /* no error ? */
		}
		printf("minishell: %s: Permission denied\n", token->word);
		return (3); /* permission denied */
	}
	printf("minishell: %s: No such file.\n", token->word);
	node->in_file = -2;
	return (3); /* no such file or  ? */
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redir_in(t_sh *f, t_cmd *node, t_token *token)
{
	DIR		*dir;
	char	*path;
	char	*pathname;
	int		i;

	path = NULL;
	path = get_filepath(f, token);
	printf("path: %s\n", path);
	if (access(path, F_OK) == 0) //path to dir exists
	{
		if (access(path, R_OK) == 0)
		{
			dir = opendir(path);
			pathname = get_filepathname(path, token);
			free(path);
			i = redirec_infile(pathname, node, token);
			closedir(dir);
			free(pathname);
			return (i); //se nao for 0, erro
		}
		free(path);
		printf("minishell: %s: Permission denied\n", token->word);
		return (2); //access denied
	}
	printf("minishell: %s: No such file.\n", token->word);
	return (1); //file or dir not exist
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redir_out(t_sh *f, t_cmd *node, t_token *token)
{
	DIR		*dir;
	char	*path;
	char	*pathname;
	int		i;

	pathname = NULL;
	path = NULL;
	path = get_filepath(f, token);
	printf("path: %s\n", path);
	if (access(path, F_OK) == 0) //path to dir exists
	{
		if (access(path, W_OK) == 0)
		{
			dir = opendir(path);
			pathname = get_filepathname(path, token);
			free(path);
			i = redirec_outfile(pathname, node, token);
			closedir(dir);
			free(pathname);
			return (i); //se nao for 0, erro
		}
		free(path);
		printf("minishell: %s: Permission denied\n", token->word);
		return (2); //access denied
	}
	printf("minishell: %s: No such file or directory\n", token->word);
	return (1);
}

int	parse_redirecs(t_sh *f, t_cmd *node, t_token *token)
{
	if (ft_strcmp(token->word, ">") == 0
		|| ft_strcmp(token->word, ">>") == 0)
		return (redir_out(f, node, token->next));
	if (ft_strcmp(token->word, "<") == 0)
		return (redir_in(f, node, token->next));
	return (0);
}
