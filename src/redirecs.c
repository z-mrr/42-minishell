#include "../inc/minishell.h"

char	*getFilePath(t_sh *f, t_cmd *node, t_token *token, int mode)
{
	char	*path;
	int	i;
	char	*tmp;

	path = NULL;
	if (token->token_str[0] == '/')
	{
		i = ft_strlen(token->token_str) - 1;
		while (i > -1 && token->token_str[i] != '/')
			i--;
		path = ft_substr(token->token_str, 0, i + 1);
	}
	else
		path = get_env("PWD", f);
	if (mode > 0)
	{
		if (token->token_str[0] == '/')
		{
			free(path);
			path = ft_strdup(token->token_str);
			printf("pathname: %s\n", path);
			return (path);
		}
		tmp = ft_strdup(path);
		free(path);
		path = ft_strjoin(tmp, token->token_str);
		free(tmp);
		printf("pathname: %s\n", path);
	}
	return (path);
}

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirecOutFile(char *pathname, t_cmd *node, t_token *token)
{
	int	perm;

	perm = 0;
	if (access(pathname, F_OK) == 0) //existe ficheiro
	{
		if (access(pathname, W_OK) == 0)
		{
			if (!(ft_strcmp(token->token_str, ">")))
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
			return (0); //no error ?
		}
		printf("access denied\n");
		return (3); //permission denied
	}
	if (!(ft_strcmp(token->token_str, ">")))
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (0); //no erro ?
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redirOut(t_sh *f, t_cmd *node, t_token *token)
{
	DIR	*dir;
	char	*path;
	int	i;

	path = NULL;
	path = getFilePath(f, node, token, 0);
	printf("path: %s\n", path);
	if (access(path, F_OK) == 0) //path to dir exists
	{
		if (access(path, W_OK) == 0)
		{
			dir = opendir(path);
			free(path);
			path = getFilePath(f, node, token, 1);
			i = redirecOutFile(path, node, token);
			closedir(dir);
			write(node->out_file, "fode te", 7); //loladas !
			return (i); //se nao for 0, erro
		}
		free(path);
		printf("access denied\n");
		return (2); //access denied
	}
	printf("file nor dir exists\n");
	return (1); //file or dir not exist
}


int	parseRedirecs(t_sh *f, t_cmd *node, t_token *token)
{
	if (!(ft_strcmp(token->token_str, ">")) || !(ft_strcmp(token->token_str, ">>")));
		return (redirOut(f, node, token->next));
	if (!(ft_strcmp(token->token_str, "<")));
		return (redirOut(f, node, token->prev));
}
