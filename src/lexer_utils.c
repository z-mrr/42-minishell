/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:37:01 by gde-alme          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ddl_remove_token(t_token **head, t_token *node)
{
	if (*head == NULL || node == NULL)
		return ;
	if (*head == node)
		*head = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node);
}

int	end_varpos(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39
			|| s[pos] == ' ' || s[pos - 1] == '?')
			return (pos);
		pos++;
	}
	return (pos);
}

int	count_pairs(char *s)
{
	char	c;
	int		i;
	int		pairs;

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

/* remove pares de quotes */
void	rmv_quotes(t_token *n)
{
	char	c;
	char	*nstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nstr = (char *)malloc(sizeof(char) * ((ft_strlen(n->word)
					- (count_pairs(n->word) * 2) + 1)));
	while (n->word[i] != '\0')
	{
		if (n->word[i] == 34 || n->word[i] == 39)
		{
			c = n->word[i++];
			while (n->word[i] != c)
				nstr[j++] = n->word[i++];
			i++;
		}
		else
			nstr[j++] = n->word[i++];
	}
	free(n->word);
	nstr[j] = '\0';
	n->word = nstr;
}
