/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:33 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/10 23:28:57 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expandDollar(t_frame *f, char *tmp, int dollar)
{
	char	*tmp2;
	t_token	*node;

	node = f->token;
	if (tmp)
	{
		if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
			tmp2 = ft_strjoin(tmp, "$");
		else
		{
			if (0 /*get_env*/ )
				tmp2 = ft_strjoin(tmp, /*get_env*/ ft_substr(node->token_str, dollar + 1, f->pos - dollar - 1));
			else
				tmp2 = tmp;
		}
		printf("\nEXPAND DOLLAR... \nLido antes e depois de $: %s\n", tmp2);
		if (tmp2 != tmp)
			free(tmp);
	}
	else
	{
		if (ft_strlen(ft_substr(node->token_str, dollar, f->pos - dollar)) < 2)
			tmp2 = ft_strdup("$");
		else
		{
			if (0 /* get_env */)
				tmp2 = /*get_env*/ ft_substr(node->token_str, dollar + 1, f->pos - dollar - 1);
			else
				return (NULL);
		}
		//printf("\nEXPAND DOLLAR... \nLido depois de $: %s\n", ft_substr(node->token_str, dollar + 1, f->pos - dollar - 1)); exit(-1);
	}
	return (tmp2);
}


/* da return positivo em caso de erro: $var igual a nada */
int	parseDollar(t_frame *f)
{
	int	dollar;
	t_token *node;
	char	*tmp;
	char	*expand;
	char	*tmp2;

	node = f->token;
	dollar = f->pos;
	tmp = NULL;
	if (f->pos - f->wd_begin)
		tmp = ft_substr(node->token_str, f->wd_begin, (f->pos) - f->wd_begin);
	printf("pos: %i - char: %c\n", f->pos, node->token_str[f->pos]);
	f->pos++;
	if (node->token_str[f->pos] == '?')
	{
		f->pos++;
		if (tmp)
			tmp2 = ft_strjoin(tmp, ft_itoa(f->last_pid));
		else
			tmp2 = ft_strdup(ft_itoa(f->last_pid));
	}
	else
	{
		while (node->token_str[f->pos] != '\"' && node->token_str[f->pos] != ' ' && node->token_str[f->pos] != '\'' && node->token_str[f->pos])
			f->pos++;
		tmp2 = expandDollar(f, tmp, dollar);
	}
	expand = ft_substr(node->token_str, f->pos, ft_strlen(node->token_str) - f->pos);
	free(node->token_str);
	if (!(tmp2) && !(expand))
		return (1);
	if (tmp2)
		node->token_str = ft_strjoin(tmp2, expand);
	else
		node->token_str = expand;
	if (tmp2)
		free(tmp2);
	printf("expand$: %s\n", node->token_str);
	return (0);
}

int	countPairs(char *s)
{
	int	i;
	int	pairs;
	char	c;

	i = 0;
	pairs = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
		{
			c = s[i];
			i++;
			pairs++;
			while (s[i] != c)
				i++;
		}
		i++;
	}
	return (pairs);
}

void	rmvQuotes(t_frame *f)
{
	int	i;
	int	j;
	char c;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ((ft_strlen(f->token->token_str) - (countPairs(f->token->token_str) * 2) + 1)));
	while (f->token->token_str[i] != '\0')
	{
		if (f->token->token_str[i] == 34 || f->token->token_str[i] == 39)
		{
			c = f->token->token_str[i++];
			while (f->token->token_str[i] != c)
				new_str[j++] = f->token->token_str[i++];
			i++;
		}
		else
			new_str[j++] = f->token->token_str[i++];
	}
	free(f->token->token_str);
	new_str[j] = '\0';
	f->token->token_str = new_str;
}

/* trata de "" return positivo em caso de erro; */
int	parseDoubleQuotes(t_frame *f)
{
	t_token *node;

	node = f->token;
	f->pos++;
	while (node->token_str[f->pos] != 34 && node->token_str[f->pos])
	{
		if (node->token_str[f->pos] == '$')
		{
			if (parseDollar(f))
				return (1);
			f->pos++;
		}
		else	
			f->pos++;
	}
	f->pos++;
	return (0);
}

/* lida com '$' e '=' ; 1 = erro $var = null*/
int	lexWord(t_frame *f)
{
	t_token *node;

	node = f->token;
	if (!(f->token))
		return (1);
	f->pos = 0;
	f->wd_begin = 0;
	while (node->token_str[f->pos])
	{
		if (node->token_str[f->pos] == 39) /* '' */
		{
			f->pos++;
			while (node->token_str[f->pos] != 39)
				f->pos++;
			f->pos++;
		}
		else if (node->token_str[f->pos] == 34) /* "" */
			parseDoubleQuotes(f);
		/*else if (node->token_str[f->pos] == '$')  input normal 
		{
			if (parseDollar(f))
				return (1);
		}*/
		else
			f->pos++;
	}
	rmvQuotes(f); /* aspas so sao removidas no final*/
	return (0);
}
