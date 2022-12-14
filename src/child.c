/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:02:23 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/14 22:47:26 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_fd(t_cmd *cmd, int *fd)
{
	if (cmd->in_file != STDIN_FILENO)//redirect ou fdread
	{
		if (dup2(cmd->in_file, STDIN_FILENO) == -1)
			perror("dup error");//g_status = 1;
		close(cmd->in_file);
	}
	if (cmd->out_file != STDOUT_FILENO)//redirect
	{
		if (dup2(cmd->out_file, STDOUT_FILENO) == -1)
			perror("dup error");//g_status = 1;
		close(cmd->out_file);
	}
	else if (cmd->next)//pipe
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			perror("dup error");//g_status = 1;
	}
	close(fd[WRITE]);
	close(fd[READ]);
}

void	ft_child(t_sh *sh, t_cmd *cmd, int *fd)
{
	check_fd(cmd, fd);
	if (!is_builtin(cmd))
		execve(cmd->path, cmd->full_cmd, sh->envp);
	else
	{
		ft_builtin(sh, cmd);
	}
	exit(0);//status
}

