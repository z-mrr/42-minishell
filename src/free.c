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
		printf("free a token_str: %s\n", tmp->token_str);
		free(tmp->token_str);
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	f->token = NULL;
}

void	free_list(t_sh *sh)//?
{
	t_cmd	*tmp;
	while(sh->cmd)
	{
		tmp = sh->cmd->next;
		free(sh->cmd->path);
		sh->cmd->path = NULL;
		sh->cmd->prev = NULL;
		sh->cmd->next = NULL;
		mtr_free(sh->cmd->full_cmd);
		sh->cmd = tmp;
		free(tmp);
	}
	free(sh->cmd);
	sh->cmd = NULL;
}
