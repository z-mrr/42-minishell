#include "../include/minishell.h"
void	expand_quote(t_frame *f)
{
	//if () // $" $ "
	//if // $?
	//if //$var expand_dollar()
}

void	next_quote(t_frame *f)
{
	if (f->str[f->pos] == 34)
	{
		f->pos++;
		while (f->str[f->pos] != 34 && f->str[f->pos])
		{
			//if (f->str[f->pos] == '$')
				//quote_expand(frame);
			//else
				f->pos++;
		}
	}
	else
	{
		f->pos++;
		while (f->str[f->pos] != 39 && f->str[f->pos])
			f->pos++;
	}
	if (f->str[f->pos] == '\0')
		{printf("err quotes");exit(-1);}
	while (f->str[f->pos] != ' ' && f->str[f->pos])
		f->pos++;
}
