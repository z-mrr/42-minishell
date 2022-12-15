/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:06 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/15 20:07:37 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* adiciona tipo de token */
void	addType_ll(t_sh *f, char type)
{
	t_token	*head;

	head = f->token;
	while (head->next != NULL)
		head = head->next;
	head->token_type = type;
}

/* adiciona mais um node (do tipo neutro) a lista de tokens */
void append_dll(t_sh *f, t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	(void)f;
	new_node = NULL;
	new_node = (t_token *)malloc(sizeof(t_token));

	new_node->token_str = s;
	new_node->token_type = 'N';
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
