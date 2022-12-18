/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_unset_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:56:42 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 04:58:51 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*env no options or arguments*/
int	ft_env(t_sh *sh)
{
	int	i;

	if (!*sh->envp)
		return (0);//
	i = -1;
	while(sh->envp[++i] && ft_strchr(sh->envp[i], '='))
		ft_putendl_fd(sh->envp[i], 1);
	return (0);
}

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

	printf("0: %s\n", cmd->full_cmd[0]);
	printf("1: %s\n", cmd->full_cmd[1]);
	printf("2: %s\n", cmd->full_cmd[2]);
	i = 0;
	n = mtr_len(cmd->full_cmd);
	printf("n: %d\n", n);
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
