/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:02:23 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 15:02:33 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	if (cmd->in_file == -1 || cmd->out_file == -1)
		return (0);
	else if ((cmd->path && !access(cmd->path, X_OK) && !is_dir(cmd->path))
			|| check_builtin(cmd))
		ft_fork(sh, cmd, fd);
	else if (!cmd->path && ft_strchr(cmd->full_cmd[0], '/'))
		p_error("minishell: ", cmd->full_cmd[0], ": No such file or directory", NULL, 127);
	else if (!cmd->path && !ft_strchr(cmd->full_cmd[0], '/'))
		p_error(cmd->full_cmd[0], ": command not found\n", NULL, NULL, 127);
	else if (is_dir(cmd->path))
		p_error("minishell: ", cmd->full_cmd[0], ": Is a directory\n", NULL, 126);
	else if (access(cmd->path, X_OK))
		p_error("minishell: ", cmd->full_cmd[0], ": Permission denied\n", NULL, 126);
	return (1);
}

void	ft_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(fd[READ]);
		close(fd[WRITE]);
		g_status = errno;
	}
	else if (!pid)
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
	if (cmd->in_file != STDIN_FILENO)//redirect in ou fd[read] de pipe
	{
		if (dup2(cmd->in_file, STDIN_FILENO) == -1)
			g_status = errno;
		close(cmd->in_file);
	}
	if (cmd->out_file != STDOUT_FILENO)//redirect out
	{
		if (dup2(cmd->out_file, STDOUT_FILENO) == -1)
			g_status = errno;
		close(cmd->out_file);
	}
	else if (cmd->next)//pipe
	{
		if (dup2(fd[WRITE], STDOUT_FILENO) == -1)
			g_status = errno;
	}
	close(fd[WRITE]);
	close(fd[READ]);
}
