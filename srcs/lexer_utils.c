#include "../include/minishell.h"

void	next_quote(t_frame *f)
{
	if (f->str[f->pos] == 34)
	{
		f->pos++;
		while (f->str[f->pos] != 34 && f->str[f->pos])
		{
			if (f->str[f->pos] == '$')
			{
				append_ll(&(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
				f->pos++;
				f->wd_begin = f->pos;
			}
			else
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
