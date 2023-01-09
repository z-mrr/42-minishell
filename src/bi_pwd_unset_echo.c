/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_pwd_unset_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:56:42 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*env no options or arguments*/
int	ft_env(t_sh *sh)
{
	int	i;

	if (!*sh->envp)
		return (g_status = 0);
	i = -1;
	while (sh->envp[++i] && ft_strchr(sh->envp[i], '='))
		ft_putendl_fd(sh->envp[i], 1);
	return (g_status = 0);
}

/*pwd with no options*/
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (p_error("minishell: ", strerror(errno), NULL, 1));
	ft_putendl_fd(pwd, 1);
	free (pwd);
	return (g_status = 0);
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
	return (g_status = 0);
}

/*echo with option -n*/
int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n;
	int	opt;

	if (!cmd->full_cmd[1])
		return (g_status = 0);
	i = 0;
	n = mtr_len(cmd->full_cmd);
	opt = ft_strncmp(cmd->full_cmd[1], "-n", 2);
	if (n < 2 || (!opt && n < 3))
		return (g_status = 0);
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
	return (g_status = 0);
}
