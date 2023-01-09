/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:56:44 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_dash(t_sh *sh, t_cmd *cmd)
{
	char	*temp;

	temp = cmd->full_cmd[1];
	cmd->full_cmd[1] = get_env("OLDPWD", sh);
	free(temp);
	if (!cmd->full_cmd[1])
		return (p_error("minishell: cd: OLDPWD not set", NULL, NULL, 1));
	temp = getcwd(NULL, 0);
	if (chdir(cmd->full_cmd[1]) == -1)
	{
		free(temp);
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		return (p_error(cmd->full_cmd[1], ": ", strerror(errno), 1));
	}
	set_env("OLDPWD", temp, sh);
	free (temp);
	temp = getcwd(NULL, 0);
	set_env("PWD", temp, sh);
	ft_putendl_fd(temp, STDOUT_FILENO);
	free (temp);
	return (g_status = 0);
}

/*cd with only a relative or absolute path*/
int	ft_cd(t_sh *sh, t_cmd *cmd)
{
	int		n;
	char	*pwd;
	char	*oldpwd;

	n = mtr_len(cmd->full_cmd);
	if (n > 2)
		return (p_error("minishell: cd: too many arguments", NULL, NULL, 1));
	if (n == 1)
		cd_home(sh, cmd);
	if (cmd->full_cmd[1] && !ft_strncmp(cmd->full_cmd[1], "-", 1)
		&& ft_strlen(cmd->full_cmd[1]) == 1)
		return (cd_dash(sh, cmd));
	oldpwd = getcwd(NULL, 0);
	if (chdir(cmd->full_cmd[1]) == -1)
	{
		free (oldpwd);
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		return (p_error(cmd->full_cmd[1], ": ", strerror(errno), 1));
	}
	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd, sh);
	set_env("OLDPWD", oldpwd, sh);
	free(pwd);
	free(oldpwd);
	return (g_status = 0);
}

int	cd_home(t_sh *sh, t_cmd *cmd)
{
	char	*home;

	home = get_env("HOME", sh);
	if (!home)
		return (p_error ("minishell: cd: HOME not set", NULL, NULL, 1));
	cmd->full_cmd = mtr_add(home, cmd->full_cmd);
	free(home);
	if (!cmd->full_cmd)
		return (g_status = 1);
	return (g_status = 0);
}
