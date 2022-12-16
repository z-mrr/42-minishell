/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_unset_echo_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:56:42 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/16 00:29:08 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*pwd with no options*/
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);//
	ft_putendl_fd(pwd, 1);
	free (pwd);
	return (0);
}

/*unset with no options*/
int	ft_unset(t_sh *sh, t_cmd *cmd)
{
	int		i;
	int		n;

	n = mtr_len(cmd->full_cmd);
	if (n > 1)
	{
		i = 0;
		while (cmd->full_cmd[++i])
			rmv_env(cmd->full_cmd[i], sh);
	}
	return (0);
}

/*echo with option -n*/
int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n;
	int	opt;

	i = 0;
	n = mtr_len(cmd->full_cmd);
	opt = ft_strncmp(cmd->full_cmd[1], "-n", 2);
	if (n < 2 || (!opt && n < 3))
		return (0);
	if (!opt)
		i++;
	while (cmd->full_cmd[++i])
	{
		ft_putstr_fd(cmd->full_cmd[i], 1);
		if (cmd->full_cmd[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (opt)
		ft_putchar_fd('\n', 1);
	return (0);
}

/*cd with only a relative or absolute path*/
int	ft_cd(t_sh *sh, t_cmd *cmd)
{
	int		n;
	char	*pwd;
	char	*oldpwd;

	n = mtr_len(cmd->full_cmd);
	if (n > 2)
	{
		perror("cd error too many args");//
		return (0);//
	}
	if (n == 1)
		cd_home(sh, cmd);
	if(chdir(cmd->full_cmd[1]) == -1)
	{
		perror("cd error wrong path");//
		return (0);//
	}
	pwd = getcwd(NULL, 0);
	oldpwd = get_env("PWD", sh);
	set_env("OLDPWD", oldpwd, sh);
	set_env("PWD", pwd, sh);
	free(pwd);
	free(oldpwd);
	return (0);
}

int	cd_home(t_sh *sh, t_cmd *cmd)
{
	char	*home;

	home = get_env("HOME", sh);
	if(!home)
	{
		perror("cd error setting home");
		return (0);//
	}
	cmd->full_cmd = mtr_add(home, cmd->full_cmd);
	free(home);
	if (!cmd->full_cmd)
	{
		perror("cd error setting home");//
		return (0);//
	}
	return (0);
}
