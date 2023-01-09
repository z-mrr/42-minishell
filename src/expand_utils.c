/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:32:21 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		expansion = ft_substr(old_str, i, end_varpos(old_str, i + 1) - i);
	else
		expansion = ft_substr(old_str, i, end_varpos(old_str, i + 1) - 1);
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

char	*_get_rest(char *old_str, t_sh *f)
{
	char	*left;
	int		start;

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

char	*_get_full_rest(t_sh *f, char *old_str)
{
	char	*frest;
	char	*parsed;
	char	*expansion;

	frest = NULL;
	parsed = _get_rest(old_str, f);
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
