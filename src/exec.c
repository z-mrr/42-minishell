/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:18:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 05:35:02 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*redirect -> is builtin -> path -> check fork -> fork -> fd/dup -> exec*/
/*>0 to fork , <0 not fork*/
int	check_builtin(t_cmd *cmd)
{
	if (!strcmp(cmd->full_cmd[0], "echo"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "cd"))
		return (-1);
	else if (!strcmp(cmd->full_cmd[0], "pwd"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "export"))
	{
		if (cmd->full_cmd[1])
			return (-1);
		else
			return (1);
	}
	else if (!strcmp(cmd->full_cmd[0], "unset"))
		return (-1);
	else if (!strcmp(cmd->full_cmd[0], "env"))
		return (1);
	else if (!strcmp(cmd->full_cmd[0], "exit"))
		return (-1);
	else
		return (0);
}

/*returnar gstatus?*/
int	ft_builtin(t_sh *sh, t_cmd *cmd)
{
	if (!strcmp(cmd->full_cmd[0], "echo"))
		ft_echo(cmd);
	else if (!strcmp(cmd->full_cmd[0], "cd"))
		ft_cd(sh, cmd);
	else if (!strcmp(cmd->full_cmd[0], "pwd"))
		ft_pwd();
	else if (!strcmp(cmd->full_cmd[0], "export"))
		ft_export(sh, cmd);
	else if (!strcmp(cmd->full_cmd[0], "unset"))
		ft_unset(sh, cmd);
	else if (!strcmp(cmd->full_cmd[0], "env"))
		ft_env(sh);
	else if (!strcmp(cmd->full_cmd[0], "exit"))
		ft_exit(cmd);
	return (0);
}

char	*get_path(t_sh *sh, t_cmd *cmd)
{
	char	**paths;
	char	*aux[3];
	int		i;

	if (ft_strchr(cmd->full_cmd[0], '/') && !access(cmd->full_cmd[0], F_OK))//se o cmd for uma path para ficheiro executavel
		return(ft_strdup(cmd->full_cmd[0]));
	aux[2] = get_env("PATH", sh);
	if (!aux[2])
		return (NULL);
	paths = ft_split(aux[2], ':');
	free(aux[2]);
	i = -1;
	while(paths[++i])
	{
		aux[0] = ft_strjoin(paths[i], "/");
		aux[1] = ft_strjoin(aux[0], cmd->full_cmd[0]);
		free(aux[0]);
		if (!access(aux[1], F_OK))
		{
			mtr_free(paths);
			return (aux[1]);
		}
		free(aux[1]);
	}
	mtr_free(paths);
	return (NULL);
}

void	parent_fd(t_cmd *cmd, int *fd)
{
		close(fd[WRITE]);
		if (cmd->next && (cmd->next->in_file == STDIN_FILENO))//caso pipe
			cmd->next->in_file = fd[READ];
		else
			close(fd[READ]);//caso no pipe
		if (cmd->in_file > 2)//redirect in
			close(cmd->in_file);//fd do open
		if (cmd->out_file > 2)//redirect out
			close(cmd->out_file);//fd do open
}

void	execInput(t_sh *sh)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = sh->cmd;
	while (cmd)
	{
		if (check_builtin(cmd) < 0  && !cmd->next)//builtins q nao forkam e nao funcionam com pipe a seguir
			ft_builtin(sh, cmd);
		else if (cmd->in_file != -2 && cmd->out_file != -2)
		{
			signal(SIGINT, SIG_IGN);//test
			signal(SIGQUIT, SIG_IGN);
			if (!check_builtin(cmd))
				cmd->path = get_path(sh, cmd);
			if (pipe(fd) == -1)
				return ;//
			if (!check_fork(sh, cmd, fd))
				return ;//
			parent_fd(cmd, fd);
			wait(&g_status);
			if (g_status > 255)
				g_status = g_status / 255;
		}
		cmd = cmd->next;
	}
}
