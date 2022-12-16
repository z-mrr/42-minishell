/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 19:02:23 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/16 00:36:31 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	if (cmd->in_file == -1 || cmd->out_file == -1)//open erros
		return (0);
	else if ((cmd->path && !access(cmd->path, X_OK) && !is_dir(cmd->path))
			|| check_builtin(cmd))
		ft_fork(sh, cmd, fd);
	else if (!cmd->path)
		g_status = 127;//error file not found
	else if (access(cmd->path, X_OK))
		g_status = 126;//error permission denied
	else if (is_dir(cmd->path))
		g_status = 126;//error is a dir
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
		perror("fork error");//
	}
	else if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_fd(cmd, fd);
		if (!check_builtin(cmd))
			execve(cmd->path, cmd->full_cmd, sh->envp);
		else if (check_builtin(cmd) > 0)
			ft_builtin(sh, cmd);
		exit(g_status);//status?
	}
}

void	child_fd(t_cmd *cmd, int *fd)
{
	if (cmd->in_file != STDIN_FILENO)//redirect in ou fd[read] de pipe
	{
		if (dup2(cmd->in_file, STDIN_FILENO) == -1)
			perror("dup error");//g_status = 1;
		close(cmd->in_file);
	}
	if (cmd->out_file != STDOUT_FILENO)//redirect out
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
