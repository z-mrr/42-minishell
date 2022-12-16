#include "../inc/minishell.h"

/* devolve pathname inteiro do ficheiro */
char	*get_filepathname(char *path, t_token *token)
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
char	*get_filepath(t_sh *f, t_token *token)
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
int	redirec_outfile(char *pathname, t_cmd *node, t_token *token)
{
	if (access(pathname, F_OK) == 0) //existe ficheiro
	{
		if (access(pathname, W_OK) == 0)
		{
			if (ft_strcmp(token->prev->token_str, ">>") == 0)
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
			else
				node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
			return (0); //no error ?
		}
		printf("minishell: %s: Permission denied\n", token->token_str);
		return (3); //permission denied
	}
	if (ft_strcmp(token->token_str, ">>") == 0)
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		node->out_file = open(pathname, O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (0); //no erro ?
}
