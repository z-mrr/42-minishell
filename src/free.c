#include "../inc/minishell.h"

void	freeTokens(t_sh *f)
{
	t_token *node;
	t_token	*tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->token_str);
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	f->token = NULL;
}

void	free_list(t_sh *sh)
{
	t_cmd	*node;
	t_cmd	*tmp;
	node = sh->cmd;
	while(node != NULL)
	{
		tmp = node;
		node = node->next;
		mtr_free(tmp->full_cmd);
		free(tmp->path);
		tmp->path = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	sh->cmd = NULL;
}
