/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 20:50:09 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 00:26:50 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_tokens(t_sh *f)
{
	t_token	*node;
	t_token	*tmp;

	node = f->token;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp->word);
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	f->token = NULL;
}

void	free_cmd(t_sh *sh)
{
	t_cmd	*node;
	t_cmd	*tmp;

	node = sh->cmd;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->full_cmd)
			mtr_free(tmp->full_cmd);
		if (tmp->path)
			free(tmp->path);
		tmp->path = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	sh->cmd = NULL;
}

void	free_all(t_sh *sh)
{
	if (!sh)
		return ;
	free_tokens(sh);
	free_cmd(sh);
	mtr_free(sh->envp);
	if (sh->parser)
		free(sh->parser);
	sh->parser = NULL;
	sh = NULL;
}

void	ft_ctrld(t_sh *sh)
{
	clear_history();
	free_all(sh);
	exit(g_status);
}
