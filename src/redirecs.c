#include "../inc/minishell.h"

/* se o file ja existe, ve se csg aceder, senao da erro */
int	redirecInFile(char *pathname, t_cmd *node, t_token *token)
{
	if (access(pathname, F_OK) == 0) //existe ficheiro
	{
		if (access(pathname, R_OK) == 0) //podemos ler
		{
			node->in_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0); //no error ?
		}
		printf("minishell: %s: Permission denied\n", token->token_str);
		return (3); //permission denied
	}
	printf("minishell: %s: No such file.\n", token->token_str);
	return (3); //no such file or  ?
}

/* ve se dir existe, se conseguir tenta escrever no dir, se sim continua*/
int	redirIn(t_sh *f, t_cmd *node, t_token *token)
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
		if (access(path, R_OK) == 0)
		{
			dir = opendir(path);
			pathname= getFilePathName(path, f, node, token);
			free(path);
			i = redirecInFile(pathname, node, token);
			closedir(dir);
			free(pathname);
			write(node->in_file, "readfile\n", 9); //!
			return (i); //se nao for 0, erro
		}
		free(path);
		printf("minishell: %s: Permission denied\n", token->token_str);
		return (2); //access denied
	}
	printf("minishell: %s: No such file.\n", token->token_str);
	return (1); //file or dir not exist
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
			write(node->out_file, "aDireita", 7); //!
			return (i); //se nao for 0, erro
		}
		free(path);
		printf("minishell: %s: Permission denied\n", token->token_str);
		return (2); //access denied
	}
	printf("minishell: %s: No such file or directory\n", token->token_str);
	return (1); //file or dir not exist
}


int	parseRedirecs(t_sh *f, t_cmd *node, t_token *token)
{
	int	i;

	if (ft_strcmp(token->token_str, ">") == 0 || ft_strcmp(token->token_str, ">>") == 0)
		return (redirOut(f, node, token->next));
	if (ft_strcmp(token->token_str, "<") == 0)
		return (redirIn(f, node, token->next));
	//return (redirOut(f, node, token->next));
	return (0);
}
