/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:25 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/11 20:05:02 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int	charArrayLen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

/* adiciona mais uma palavra ao cmd/args faz ja update do f->token */
void	addStrCmd(t_cmd *node, char *s)
{
	char	**new_cmd;
	int	i;

	i = 0;
	if (node->full_cmd == NULL)
	{
		node->full_cmd = (char **)malloc(sizeof(char *) * 2);
		node->full_cmd[0] = ft_strdup(s);
		node->full_cmd[1] = 0;
		return ;
	}
	new_cmd = (char **)malloc(sizeof(char *) * ((charArrayLen(node->full_cmd) + 2)));
	while (node->full_cmd[i])
	{
		new_cmd[i] = ft_strdup(node->full_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(s);
	new_cmd[++i] = 0;
	free(node->full_cmd);
	node->full_cmd = new_cmd;
}

void	initCmd(t_cmd *node)
{
	node->full_cmd = NULL;
	node->path = NULL;
	node->in_fd = 0;
	node->out_fd = 1;
	node->err_fd = 2;
	node->next = NULL;
	node->prev = NULL;
}

void	ddl_append(t_cmd *last)
{
	t_cmd	*new_node;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));

	new_node->next = NULL;
	new_node->prev = last;
	last->next = new_node;
	printf("new_node adress: %p\n", new_node);
}
