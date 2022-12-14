/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:18:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/14 22:58:33 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*redirect -> is builtin -> path -> check fork -> fd/dup fork -> exec*/

int	is_builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->full_cmd[0], "echo"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "cd"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "pwd"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "export"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "unset"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "env"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "exit"))
		return (1);
	else
		return (0);
}

int	ft_builtin(t_sh *sh, t_cmd *cmd)
{
	if (!strcmp(sh->cmd->full_cmd[0], "echo"))
		ft_echo(cmd);
	else if (!strcmp(sh->cmd->full_cmd[0], "cd"))
		ft_cd(sh, cmd);
	else if (!strcmp(sh->cmd->full_cmd[0], "pwd"))
		ft_pwd();
	else if (!strcmp(sh->cmd->full_cmd[0], "export"))
		ft_export(sh, cmd);
	else if (!strcmp(sh->cmd->full_cmd[0], "unset"))
		ft_unset(sh, cmd);
	else if (!strcmp(sh->cmd->full_cmd[0], "env"))
		ft_env(sh);
	else if (!strcmp(sh->cmd->full_cmd[0], "exit"))
		ft_exit(cmd);
	return (0);
}

char	*get_path(t_sh *sh, t_cmd *cmd)
{
	char	**paths;
	char	*tmp;
	char	*path;
	char	*env;
	int		i;

	env = get_env("PATH", sh);
	paths = ft_split(env, ':');
	free(env);
	i = -1;
	while(paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd->full_cmd[0]);
		free(tmp);
		if(!access(path, 0))
		{
			mtr_free(paths);
			return (path);
		}
		free(path);
	}
	mtr_free(paths);
	return (NULL);
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
		ft_child(sh, cmd, fd);
		printf("Hello from child\n");
	}
}

int	check_fork(t_sh *sh, t_cmd *cmd, int *fd)
{
	DIR *dir;

	dir = NULL;
	if (cmd->full_cmd)
		dir = opendir(cmd->full_cmd[0]);
	if (cmd->in_file == -1 || cmd->out_file == -1)
		return (0);
	if ((cmd->path && !access(cmd->path, X_OK)) || is_builtin(cmd))
		ft_fork(sh, cmd, fd);
	else if (!is_builtin(cmd) && ((cmd->path && !access(cmd->path, F_OK)) || dir))
		g_status = 126;//
	else if (cmd->path && !is_builtin(cmd))
		g_status = 127;//
	if (dir)
		closedir(dir);
	return (1);
}

void	execInput(t_sh *sh)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = sh->cmd;
	while (cmd)
	{
		if (!(is_builtin(cmd)))
			cmd->path = get_path(sh, cmd);//checkar erros, usar DIR?
		if (pipe(fd) == -1)
			return ;//
		if (!check_fork(sh, cmd, fd))
			return ;
		close(fd[WRITE]);
		if (cmd->next && (cmd->next->in_file == STDIN_FILENO))//caso pipe
			cmd->next->in_file = fd[READ];
		else
			close(fd[READ]);
		if (cmd->in_file > 2)//redirect
			close(cmd->in_file);//fd do open
		if (cmd->out_file > 2)//redirect
			close(cmd->out_file);//fd do open
		cmd = cmd->next;
		waitpid(-1, &g_status, 0);//
	}

}
