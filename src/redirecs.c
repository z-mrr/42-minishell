#include "../inc/minishell.h"

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
