/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:56:44 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 20:50:35 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cd_dash(t_sh *sh, t_cmd *cmd)
{
	char	*temp;

	if (cmd->full_cmd[1] && !ft_strncmp(cmd->full_cmd[1], "-", 1))
	{
		temp = cmd->full_cmd[1];
		cmd->full_cmd[1] = get_env("OLDPWD", sh);
		free(temp);
		if (!cmd->full_cmd[1])
			return (0);
	}
	return (1);
}

/*cd with only a relative or absolute path*/
int	ft_cd(t_sh *sh, t_cmd *cmd)
{
	int		n;
	char	*pwd;
	char	*oldpwd;

	n = mtr_len(cmd->full_cmd);
	if (n > 2)
		return (p_error("minishell: cd: too many arguments", NULL, NULL, NULL, 1));
	if (n == 1)
		cd_home(sh, cmd);
	if (!cd_dash(sh, cmd))
		return(p_error("minishell: cd: OLDPWD not set", NULL, NULL, NULL, 1));
	if(chdir(cmd->full_cmd[1]) == -1)
		return (p_error("minishell: ", cmd->full_cmd[1], ": ", strerror(errno), 1));
	pwd = getcwd(NULL, 0);
	set_env("PWD", pwd, sh);
	oldpwd = get_env("PWD", sh);
	set_env("OLDPWD", oldpwd, sh);
	free(pwd);
	free(oldpwd);
	return (g_status = 0);
}

int	cd_home(t_sh *sh, t_cmd *cmd)
{
	char	*home;

	home = get_env("HOME", sh);
	if(!home)
		return (p_error("minishell: cd: HOME not set", NULL, NULL, NULL, 1));
	cmd->full_cmd = mtr_add(home, cmd->full_cmd);
	free(home);
	if (!cmd->full_cmd)
		return (g_status = 1);
	return (g_status = 0);
}
