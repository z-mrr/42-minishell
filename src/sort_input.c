/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 22:24:43 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_operators(t_sh *f)
{
	t_token	*node;

	node = NULL;
	node = f->token;
	while (node != NULL)
	{
		if (node->type == 'O')
		{
			if (node->next == NULL || node->next->type == 'O'
				|| (node->prev == NULL && ft_strcmp(node->word, "<<") != 0))
			{
				g_status = 2;
				printf("minishell: syntax errornear unexpected token '%s'\n",
					node->word);
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}

/* return 1 se input acabar por ser nulo */
int	sort_input(t_sh *f)
{
	if (create_words(f))
	{
		g_status = 2;
		return (1);
	}
	if (check_operators(f))
		return (1);
	if (_expander(f))
		return (1);
	if (parsecmd(f) != 0)
		return (1);
	print_list(f->token);
	print_listcmd(f->cmd);
	return (0);
}
