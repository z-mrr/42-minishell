/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:46 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* check for operators */
int	find_operator(char c)
{
	if (c == 60)
		return (1);
	if (c == 62)
		return (1);
	if (c == 124)
		return (1);
	return (0);
}

/* separa palavra antes de operador e o operador */
void	lex_op(t_sh *f)
{
	if (f->parser->pos - f->parser->wd_b)
		append_dll(f, &(f->token), ft_substr(f->parser->str,
				f->parser->wd_b, f->parser->pos - f->parser->wd_b));
	f->parser->wd_b = f->parser->pos;
	if (f->parser->str[f->parser->pos] == 60
		|| f->parser->str[f->parser->pos] == 62)
	{
		if (f->parser->str[f->parser->pos + 1]
			== f->parser->str[f->parser->pos])
			f->parser->pos += 2;
		else
			f->parser->pos++;
	}
	else
		f->parser->pos++;
	append_dll(f, &(f->token), ft_substr(f->parser->str,
			f->parser->wd_b, f->parser->pos - f->parser->wd_b));
	f->parser->wd_b = f->parser->pos;
	add_type_ll(f, 'O');
}

/* separa palavra normal + espacos entre palavras */
void	lex_wdend(t_sh *f)
{
	if (f->parser->pos - f->parser->wd_b)
		append_dll(f, &(f->token), ft_substr(f->parser->str,
				f->parser->wd_b, f->parser->pos - f->parser->wd_b));
	while (f->parser->str[f->parser->pos] == ' ')
		f->parser->pos++;
	f->parser->wd_b = f->parser->pos;
}

/* separa desde 1a aspa ate proxima aspa, return 1 falta de aspas */
int	lex_quote(t_sh *f)
{
	if (f->parser->str[f->parser->pos] == 34)
	{
		f->parser->pos++;
		while (f->parser->str[f->parser->pos] != 34)
		{
			if (f->parser->str[f->parser->pos] == '\0')
				return (parser_error(f, "\""));
			f->parser->pos++;
		}
	}
	else if (f->parser->str[f->parser->pos] == 39)
	{
		f->parser->pos++;
		while (f->parser->str[f->parser->pos] != 39)
		{
			if (f->parser->str[f->parser->pos] == '\0')
				return (parser_error(f, "\'"));
			f->parser->pos++;
		}
	}
	f->parser->pos++;
	return (0);
}

/* separa input por palaras; se algum par de quotes não fechar da erro */
int	create_words(t_sh *f)
{
	f->parser->pos = 0;
	f->parser->wd_b = 0;
	while (f->parser->str[f->parser->pos] != '\0')
	{
		if (f->parser->str[f->parser->pos] == '\''
			|| f->parser->str[f->parser->pos] == '\"')
		{
			if (lex_quote(f))
				return (1);
		}
		else if (find_operator(f->parser->str[f->parser->pos]))
			lex_op(f);
		else if (f->parser->str[f->parser->pos] == ' ')
			lex_wdend(f);
		else
			f->parser->pos++;
	}
	if (f->parser->pos - f->parser->wd_b)
		append_dll(f, &(f->token), ft_substr(f->parser->str,
				f->parser->wd_b, f->parser->pos - f->parser->wd_b));
	return (0);
}
