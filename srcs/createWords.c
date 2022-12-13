/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createWords.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:46 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/12 18:14:33 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"
/* check for operators */
int	findOperator(char c)
{
	if (c == 60)  /* < */
		return (1);
	if (c == 62)  /* > */
		return (1);
	if (c == 124) /* | */
		return (1);
	return (0);
}

/* separa palavra antes de operador e o operador */
void	lexOp(t_sh *f)
{
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //palavra ate operator
	f->wd_begin = f->pos;
	if (f->str[f->pos] == 60 || f->str[f->pos] == 62) /* << >> */
	{
		if (f->str[f->pos + 1] == f->str[f->pos])
			f->pos += 2;
		else
			f->pos++;
	}
	else
		f->pos++;
	
	append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //operator
	f->wd_begin = f->pos;
	addType_ll(f, 'O');
}

/* separa palavra normal + espacos entre palavras */
void	lexWdend(t_sh *f)
{
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin));
	while (f->str[f->pos] == ' ')
		f->pos++;
	f->wd_begin = f->pos;
}

/* separa desde 1a aspa ate proxima aspa*/
void	lexQuote(t_sh *f)
{
	if (f->str[f->pos] == 34)
	{
		f->pos++;
		while (f->str[f->pos] != 34)
		{
			if (f->str[f->pos] == '\0')
				{printf("err quotes");exit(-1);}	
			f->pos++;
		}
	}
	else if (f->str[f->pos] == 39)
	{
		f->pos++;
		while (f->str[f->pos] != 39)
		{
			if (f->str[f->pos] == '\0')
				{printf("err quotes");exit(-1);}	
			f->pos++;
		}
	}
	f->pos++;
}

/* separa input por palaras; se algum par de quotes não fechar da erro */
void	createWords(t_sh *f)
{
	f->pos = 0;
	f->wd_begin = 0;
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') /* errno */
			lexQuote(f);
		else if (findOperator(f->str[f->pos]))
			lexOp(f);
		else if (f->str[f->pos] == ' ')
			lexWdend(f);
		else
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
}
