#include "../include/minishell.h"

/* check for operators */
int	findOperator(char c)
{
	/*if (c == 61)  // =
		return (1);
	if (c == 36)  // $ 
		return (1); */
	if (c == 60)  /* < */
		return (1);
	if (c == 62)  /* > */
		return (1);
	if (c == 124) /* | */
		return (1);
	return (0);
}

/* separa palavra antes de operador e o operador */
void	lexOp(t_frame *f)
{
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //palavra ate operator
	f->wd_begin = f->pos;
	if (f->str[f->pos] == 60 || f->str[f->pos] == 62) /* >> << */
	{
		if (f->str[f->pos + 1] == f->str[f->pos])
			f->pos += 2;
		else
			f->pos++;
	}
	else
		f->pos++;
	append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //operator
	f->wd_begin = f->pos;
	addType_ll(f, 'O');
}

/* separa palavra normal + espacos entre palavras */
void	lexWdend(t_frame *f)
{
	if (f->pos - f->wd_begin)
		append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
	while (f->str[f->pos] == ' ')
		f->pos++;
	f->wd_begin = f->pos;
}

/* separa desde 1a aspa ate proxima aspa*/
void	lexQuote(t_frame *f)
{
	if (f->str[f->pos] == 34)
	{
		f->pos++;
		while (f->str[f->pos] != 34 && f->str[f->pos])
				f->pos++;
	}
	else
	{
		f->pos++;
		while (f->str[f->pos] != 39 && f->str[f->pos])
			f->pos++;
	}
	if (f->str[f->pos] == '\0')
		{printf("err quotes");exit(-1);}
	f->pos++;
	while (f->str[f->pos] != ' ' && f->str[f->pos])
		f->pos++;
	append_ll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
	f->wd_begin = f->pos;
}
