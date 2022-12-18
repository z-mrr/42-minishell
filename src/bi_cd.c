/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:56:44 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 13:20:13 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*cd with only a relative or absolute path*/
int	ft_cd(t_sh *sh, t_cmd *cmd)
{
	int		n;
	char	*pwd;
	char	*oldpwd;

	n = mtr_len(cmd->full_cmd);
	if (n > 2)
		return (p_error("minishell: cd: too many arguments\n", NULL, NULL, NULL, 1));
	if (n == 1)
		cd_home(sh, cmd);
	if(chdir(cmd->full_cmd[1]) == -1)
		return (p_error("minishell: ", cmd->full_cmd[1], ": No such file or directory\n", NULL, 1));
	pwd = getcwd(NULL, 0);
	oldpwd = get_env("PWD", sh);
	set_env("OLDPWD", oldpwd, sh);
	set_env("PWD", pwd, sh);
	free(pwd);
	free(oldpwd);
	return (g_status = 0);
}

int	cd_home(t_sh *sh, t_cmd *cmd)
{
	char	*home;

	home = get_env("HOME", sh);
	if(!home)
		return (p_error("minishell: cd: HOME not set\n", NULL, NULL, NULL, 1));
	cmd->full_cmd = mtr_add(home, cmd->full_cmd);
	free(home);
	if (!cmd->full_cmd)
		return (p_error("minishell: cd: error setting HOME\n", NULL, NULL, NULL, 1));
	return (g_status = 0);
}
