/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:02:23 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	if (cmd->in_file == -1 || cmd->out_file == -1)
		return (0);
	else if ((cmd->path && !access(cmd->path, X_OK) && !is_dir(cmd->path))
		|| check_builtin(cmd))
	{
		ft_fork(sh, cmd, fd);
		sh->i++;
		sh->fork = 1;
	}
	else if (!cmd->path && ft_strchr(cmd->full_cmd[0], '/'))
		p_error("minishell: ", cmd->full_cmd[0],
			": No such file or directory", 127);
	else if (!cmd->path && !ft_strchr(cmd->full_cmd[0], '/'))
		p_error(cmd->full_cmd[0], ": command not found", NULL, 127);
	else if (is_dir(cmd->path))
		p_error("minishell: ", cmd->full_cmd[0], ": Is a directory", 126);
	else if (access(cmd->path, X_OK))
		p_error("minishell: ", cmd->full_cmd[0], ": Permission denied", 126);
	return (1);
}

void	ft_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	sh->pid = fork();
	if (sh->pid == -1)
	{
		close(fd[READ]);
		close(fd[WRITE]);
		g_status = 1;
	}
	else if (!sh->pid)
	{
		child_fd(cmd, fd);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!check_builtin(cmd))
			execve(cmd->path, cmd->full_cmd, sh->envp);
		else if (check_builtin(cmd) > 0)
			ft_builtin(sh, cmd);
		exit(g_status);
	}
}

void	child_fd(t_cmd *cmd, int *fd)
{
	if (cmd->in_file != STDIN_FILENO)
	{
		if (dup2(cmd->in_file, STDIN_FILENO) == -1)
			g_status = 1;
		close(cmd->in_file);
	}
	if (cmd->out_file != STDOUT_FILENO)
	{
		if (dup2(cmd->out_file, STDOUT_FILENO) == -1)
			g_status = 1;
		close(cmd->out_file);
	}
	else if (cmd->next)
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			g_status = 1;
	}
	close(fd[WRITE]);
	close(fd[READ]);
}
