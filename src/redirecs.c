#include "../inc/minishell.h"

/* confirma se ja trás pathname; se nao adiciona pwd; se string começar por  */
char	*getFilePath(t_sh *f, t_token *token, int mode)
{
	char	*path;
	char	*tmp;

	if (token->token_str[0] == '/')
		return (ft_strdup(token->token_str));
	if (token->token_str[0] == '~' && token->token_str[1] == '/')
		path = get_env("HOME",f );
	else
		path = get_env("PWD", f);
	tmp = ft_strjoin(path, "/");
	free(path);
	if (mode == 0)
		return (tmp);
	if (token->token_str[0] == '~' && token->token_str[1] == '/')
		path = ft_strjoin(tmp, token->token_str + 2);
	else
		path = ft_strjoin(tmp, token->token_str);
	free(tmp);
	return (path);
}

/* tenta aceder para ao file em W mode, se conseguir, open fd */
int	redirOutFile(char *path, t_sh *f, t_cmd *node, t_token *token)
{
	int	fd;
	char	*pathname;

	pathname = NULL,
	pathname = getFilePath(f, token, 1);
	if (pathname[ft_strlen(pathname) - 1] == '/')
		{printf("is a dir\n"); return (1);} //error is a dir
	if (access(path, W_OK) == 0)
	{
		if (!(ft_strcmp(token->token_str, ">>")))
			fd = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (ft_strcmp(token->token_str, ">"))
			fd = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
		printf("fd: %i\n",fd);
		write(fd, "eque", 3);
		write(fd, "append", 3);
		node->out_file = fd;
		free(pathname);
		free(path);
		return (0);
	}
	printf("error: permission denied\n");exit(-1);
	return (-1);
}

/* redirec para outfile: '>' '>>'; confirma se pode aceder ao dir (senao devolve erro); dir ou vem no token ou é pwd */
int	redirOut(t_sh *f, t_cmd *node, t_token *token)
{
	DIR	*dir;
	char	*path;

	path = NULL;
	path = getFilePath(f, token, 0);
	printf("path: %s\n", path);
	if (access(path, F_OK) < 0)
		{free(path);printf("no such file or dir\n"); return (1);} //error: no such file or dir
	dir = opendir(path);
	if (redirOutFile(path, f, node, token))
		return (1);
	closedir(dir);
	return (0); 
}


int	parseRedirecs(t_sh *f, t_cmd *node, t_token *token)
{
	if (!(ft_strcmp(token->token_str, ">")) || !(ft_strcmp(token->token_str, ">>")));
		return (redirOut(f, node, token->next));
	if (!(ft_strcmp(token->token_str, "<")));
		return (redirOut(f, node, token->prev));
}
