#include "../include/minishell.h"
void	next_quote(t_frame *f)
{
	char	*tmp;
	char	tmp2[5] = "name";
	char	*tmp3;

	f->in_quote = 1;
	if (f->str[f->pos] == 34)
	{
		f->pos++;
		while (f->str[f->pos] != 34 && f->str[f->pos])
		{
			if (f->str[f->pos] == '$')
			{
				if (f->str[f->pos] == 34 || f->str[f->pos] == ' ')
				{
					append_ll(&(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
					f->in_quote = 0;
				}
				else
					tmp = ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin); //antes do $
				f->pos++;
				f->wd_begin = f->pos;
				while (f->str[f->pos] != ' ' && f->str[f->pos] && f->str[f->pos] != 34)
				{
					if (f->str[f->pos + 1] == 34)
						f->in_quote = 0;
					f->pos++;
				}
				tmp3 = ft_strjoin(tmp, getenv(tmp2));
				f->wd_begin = f->pos;
				while (f->str[f->pos] && f->str[f->pos] != 34)
				{
					if (f->str[f->pos + 1] == 34)
						f->in_quote = 0;
					f->pos++;
				}
				append_ll(&(f->token), ft_strjoin(tmp3, ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)));
				f->wd_begin = f->pos;
				if (f->in_quote)
					{printf("eeor qts");exit(-1);}
			}
			else
				f->pos++;
		}
	}
	else
	{
		f->pos++;
		while (f->str[f->pos] != 39 && f->str[f->pos])
		{
			if (f->str[f->pos] == 39)
				f->in_quote = 0;
			f->pos++;
		}
	}
	if (f->in_quote)
		{printf("err quotes");exit(-1);}
	while (f->str[f->pos] != ' ' && f->str[f->pos])
		f->pos++;
}
