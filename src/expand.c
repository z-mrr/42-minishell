/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:50:32 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 01:00:02 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* devolve expansao ou null */
char	*_get_expansion(char *old_str, t_sh *f)
{
	char	*expansion;
	char	*env;
	int		i;

	i = f->parser->pos;
	expansion = NULL;
	env = NULL;
	if (end_varpos(old_str, i + 1) != '$')
		expansion = ft_substr(old_str, i,  end_varpos(old_str, i + 1) - i);
	else
		expansion = ft_substr(old_str, i,  end_varpos(old_str, i + 1) - 1);
	if (ft_strcmp(expansion, "$?") == 0)
	{
		free(expansion);
		return (ft_itoa(g_status));
	}
	if (!(ft_strcmp(expansion, "$")))
		return (expansion);
	env = get_env(expansion + 1, f);
	free(expansion);
	if (env)
		return (env);
	return (NULL);
}

char	*_getRest(char *old_str, t_sh *f)
{
	int	start;
	char	*left;

	left = NULL;
	start = f->parser->pos;
	while (old_str[f->parser->pos] != '\0' && old_str[f->parser->pos] != '$')
	{
		if (old_str[f->parser->pos] == 39)
		{
			f->parser->pos++;
			while (old_str[f->parser->pos] != 39)
				f->parser->pos++;
			f->parser->pos++;
		}
		else
			f->parser->pos++;
	}
	if (f->parser->pos > start)
	{
		left = ft_substr(old_str, start, f->parser->pos - start);
		return (left);
	}
	else
		return (NULL);
}

char	*_getFullRest(t_sh *f, char *old_str)
{
	char	*frest;
	char	*parsed;
	char	*expansion;

	frest = NULL;
	parsed = _getRest(old_str, f);
	expansion = _get_expansion(old_str, f);
	if (expansion && parsed)
	{
		frest = ft_strjoin(parsed, expansion);
		free(parsed);
		free(expansion);
	}
	else if (parsed)
	{
		frest = ft_strdup(parsed);
		free(parsed);
	}
	else if (expansion)
	{
		frest = ft_strdup(expansion);
		free(expansion);
	}
	return (frest);
}


/* recebe uma str,  expande todos os $ */
char	*_expandStr(t_sh *f, char *old_str)
{
	char	*rest;
	char	*new_str;
	char	*tmp;

	new_str = NULL;
	rest = NULL;
	f->parser->pos = 0;
	while (old_str[f->parser->pos])
	{
		rest = _getFullRest(f, old_str);
		if (rest)
		{
			if (new_str)
			{
				tmp = ft_strdup(new_str);
				free(new_str);
				new_str = ft_strjoin(tmp, rest);
				free(tmp);
			}
			else
				new_str = ft_strdup(rest);
			free(rest);//mudei free. tava double free
		}
		f->parser->pos = end_varpos(old_str, f->parser->pos + 1);
	}
	return (new_str);
}


/* remove nodes */
int	rmvNodes(t_sh *f)
{
	t_token *node;
	t_token *tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node->next;
		if (!node)
			break ;
		if (!(node->word))
			ddl_remove_token(&(f->token), node);
		node = tmp;
	}
	if (f->token == NULL)
		return (1);
	return (0);
}


/* token a token , expande os $ na str, remove quotes e elimina tokens vazios */
int	_expander(t_sh *f)
{
	t_token *node;
	char	*tmp;

	node = NULL;
	node = f->token;
	while (node != NULL)
	{
		if (ft_strchr(node->word, '$'))
		{
			tmp = ft_strdup(node->word);
			free(node->word);
			node->word = _expandStr(f, tmp);
			free(tmp);
		}
		if (node->word)
			rmv_quotes(node);
		node = node->next;
	}
	if (rmvNodes(f))
		return (1);
	return (0);
}
