/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 02:04:22 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 15:58:44 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirec_infile(char *pathname, t_cmd *node, t_token *token)
{
	if (access(pathname, F_OK) == 0 && pathname[ft_strlen(pathname) - 1] != '/') /* existe ficheiro e nao e um file !*/
	{
		if (access(pathname, R_OK) == 0) /* podemos ler */
		{
			node->in_file = open(pathname, O_RDONLY, 0644);
			return (0); /* no error ? */
		}
		node->in_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1)); //access denied
	}
	node->in_file = -2;
	return (p_error("minishell: ", token->word, ": No such file (or is a dir)", 1)); //no such file or ir a dir
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
	if (node->in_file != STDIN_FILENO && node->in_file != -2 && node->in_file != -1) // se fd ja foi aberto , fecha
		close(node->in_file);
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
		node->in_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1)); //access denied
	}
	node->in_file = -2;
	return (p_error("minishell: ", token->word, ": No such file or dir", 1)); //access denied
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
	if (node->out_file != STDOUT_FILENO && node->out_file != -2 && node->out_file != -1)
		close(node->out_file);
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
		node->out_file = -2;
		return (p_error("minishell: ", token->word, ": Permission denied", 1));
	}
	node->out_file = -2;
	return (p_error("minishell: ", token->word, ": No such file or directory", 1));
}

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
	int	fd[2];
	char	*tmp;

	tmp = NULL;
	if (node->in_file != STDIN_FILENO && node->in_file != -2 && node->in_file != -1)
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
	return (0); //ok
}

/* heredoc: writes to a str lines read by newline untill strcmp(lineread, "EOF") == 0 */
int	redir_heredoc(t_cmd *node, char *eof)
{
	char 	*str;
	char	*buffer;

	g_status = 0;
	str = NULL;
	buffer = NULL;
	while (g_status != 130)
	{
		buffer = readline("> ");
		if (!buffer)
			return (node->in_file = -2); //if empty
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
	}
	node->in_file = -2;
	return (0);
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
