/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:18:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/13 16:23:13 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*redirect -> is builtin -> path -> check fork -> fd/dup fork -> exec*/

int	is_builtin(t_sh *sh)
{
	if (!strcmp(sh->cmd->full_cmd[0], "echo"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "cd"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "pwd"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "export"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "unset"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "env"))
		return (1);
	else if (!strcmp(sh->cmd->full_cmd[0], "exit"))
		return (1);
	else
		return (0);
}

void	builtin(t_sh *sh)
{
	if (!strcmp(sh->cmd->full_cmd[0], "echo"))
		ft_echo(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "cd"))
		ft_cd(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "pwd"))
		ft_pwd();
	else if (!strcmp(sh->cmd->full_cmd[0], "export"))
		ft_export(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "unset"))
		ft_unset(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "env"))
		ft_env(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "exit"))
		ft_exit(sh);
}

void	execInput(t_sh *sh)
{
	t_cmd	*node;

	node = sh->cmd;
	while (node)
	{
		if (is_builtin(sh))
			builtin(sh);
		node = node->next;
	}
	free_list(sh);
}
