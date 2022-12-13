#include "../inc/minishell.h"

void	freeCmds(t_sh *f)
{
	t_cmd	*node;
	t_cmd	*tmp;

	node = f->cmds;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

void	freeTokens(t_sh *f)
{
	t_token *node;
	t_token *tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->token_str);
		free(tmp);
	}
}

void	freeParser(t_sh *f)
{
	freeTokens(f);
	free(f->parser->str);
	f->token = NULL;
}
