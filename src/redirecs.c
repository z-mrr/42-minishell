#include "../inc/minishell.h"

/* devolve pathname inteiro do ficheiro */
char	*getFilePathName(char *path, t_sh *f, t_cmd *node, t_token *token)
{
	char	*pathname;

	pathname = NULL;
	if (token->token_str[0] == '/' || (token->token_str[0] == '.' && token->token_str[1] == '/'))
	{
		pathname = ft_strdup(token->token_str);
		printf("pathname: %s\n", pathname);
		return (pathname);
	}
	pathname = ft_strjoin(path, token->token_str);
	printf("pathname: %s\n", pathname);
	return (pathname);
}

/* devolve path dor dir onde se vai escrever */
char	*getFilePath(t_sh *f, t_cmd *node, t_token *token)
{
	char	*path;
	int	i;
	char	*tmp;

	path = NULL;
	if (token->token_str[0] == '/' || (token->token_str[0] == '.' && token->token_str[1] == '/'))
	{
		i = ft_strlen(token->token_str) - 1;
		while (i > -1 && token->token_str[i] != '/')
			i--;
		path = ft_substr(token->token_str, 0, i + 1);
		return (path);
	}
	tmp = get_env("PWD", f);
	path = ft_strjoin(tmp, "/");
	free(tmp);
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
			if (!(ft_strcmp(token->prev->token_str, ">>")))
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0); //no error ?
		}
		printf("access denied\n");
		return (3); //permission denied
	}
	if (!(ft_strcmp(token->token_str, ">>")))
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0); //no erro ?
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redirOut(t_sh *f, t_cmd *node, t_token *token)
{
	DIR	*dir;
	char	*path;
	char	*pathname;
	int	i;

	path = NULL;
	path = getFilePath(f, node, token);
	printf("path: %s\n", path);
	if (access(path, F_OK) == 0) //path to dir exists
	{
		if (access(path, W_OK) == 0)
		{
			dir = opendir(path);
			pathname= getFilePathName(path, f, node, token);
			free(path);
			i = redirecOutFile(pathname, node, token);
			closedir(dir);
			free(pathname);
			write(node->out_file, "1texto", 7); //!
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
	return (0);
}
