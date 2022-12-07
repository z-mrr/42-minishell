#include "../include/minishell.h"
/*
char	first_quote(char *s)
{
	
}

char	*trim_quotes(char *s)
{
	char	c;
	int	i;

	i = 0;
	c = first_quote(s);
} */

int	lexer(char *s)
{
	int	pos;
	int	wd_begin;
	t_token *token;

	token = NULL;
	pos = 0;
	wd_begin = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == '\'' || s[pos] == '\"') //dentro de quotes 
		{
			pos = next_quote(s, pos);
			if (pos < 0)
				return (1); //tratar de separar $..
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			wd_begin = pos;
		}
		else if (s[pos] == '$') //operators
		{
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin)); //palavra ate operator
			wd_begin = pos;
			pos++;
			append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin)); //operator
			wd_begin = pos;
		}
		else if (s[pos] == ' ') //final de word
		{
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			while (s[pos] == ' ')
				pos++;
			wd_begin = pos;
		}
		else //args
			pos++;
	}
	if (pos - wd_begin)
		append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin)); //ultima palavra
	printf("current pos: %i - %c\n", pos, s[pos]);
	printList(token);
	return (0);
}
