#include "../include/minishell.h"

/* free do que foi usado*/
void	free_f(t_sh *f)
{
	free(f->str);
}

/* da aos tokens e suas str */
void	freeTokens(t_sh *f)
{
	while (f->token->next != NULL)
	{
		printf("free token: %s\n", f->token->token_str);
		f->token = f->token->next;
		free(f->token->prev->token_str);
		f->token->prev->token_str = NULL;
		f->token->prev->next = NULL;
		free(f->token->prev);
		f->token->prev = NULL;
	}
	printf("free token: %s\n", f->token->token_str);
	free(f->token->token_str);
	free(f->token);
	f->token = NULL;
}
