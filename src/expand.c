/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:50:32 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tmpstr(char *new_str, char *rest)
{
	char	*tmp;

	tmp = NULL;
	if (new_str)
	{
		tmp = ft_strdup(new_str);
		free(new_str);
		new_str = ft_strjoin(tmp, rest);
		free(tmp);
	}
	else
		new_str = ft_strdup(rest);
	free(rest);
	return (new_str);
}

/* recebe uma str,  expande todos os $ */
char	*_expand_str(t_sh *f, char *old_str)
{
	char	*rest;
	char	*new_str;

	new_str = NULL;
	rest = NULL;
	f->parser->pos = 0;
	while (old_str[f->parser->pos])
	{
		rest = _get_full_rest(f, old_str);
		if (rest)
			new_str = tmpstr(new_str, rest);
		f->parser->pos = end_varpos(old_str, f->parser->pos + 1);
	}
	return (new_str);
}

/* token a token , expande os $ na str, remove quotes e elimina tokens vazios */
int	_expander(t_sh *f)
{
	t_token	*node;
	char	*tmp;

	node = NULL;
	node = f->token;
	while (node != NULL)
	{
		if (ft_strchr(node->word, '$'))
		{
			tmp = ft_strdup(node->word);
			free(node->word);
			node->word = _expand_str(f, tmp);
			free(tmp);
		}
		if (node->word)
			rmv_quotes(node);
		node = node->next;
	}
	if (rmv_nodes(f))
		return (1);
	return (0);
}
