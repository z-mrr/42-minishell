/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:19 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/10 20:10:28 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsePipes(t_frame *f)
{
	append_dll_cmd(f, &(f->cmds));
	f->cmds = f->cmds->next;
	f->token = f->token->next;
	printf("fazer pipe\n");
}

/* se N adiciona ao cmd/args ate ao prox OP ou fim */
void	parseCmds(t_frame *f)
{
	printf("\n...Parser...\n");
	append_dll_cmd(f, &(f->cmds));
	int	i = 0;
	while (f->token->next != NULL)
	{
		if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
		{
			parsePipes(f);	
			i = 0;
		}
		else
		{
			addStrCmd(f);
			printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
		}
	}
	if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
	{
		parsePipes(f);	
		i = 0;
	}
	else
	{
		addStrCmd(f);
		printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
	}
}
