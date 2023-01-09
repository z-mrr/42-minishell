/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:11 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*export no options. mudar test para sh->cmd->full_cmdcmd->content->args*/
int	ft_export(t_sh *sh, t_cmd *cmd)
{
	int		n;
	int		i;
	int		j;
	char	*var;
	char	*value;

	n = mtr_len(cmd->full_cmd);
	if (n > 1)
	{
		i = 0;
		while (++i < n)
		{
			j = ft_strichr(cmd->full_cmd[i], '=');
			if (j <= 0)
				return (export_novalue(sh, cmd->full_cmd[i]));
			var = ft_substr(cmd->full_cmd[i], 0, j);
			value = ft_strdup(cmd->full_cmd[i] + (j + 1));
			set_env(var, value, sh);
			free(var);
			free(value);
		}
	}
	else
		print_export(sh);
	return (g_status = 0);
}

int	export_novalue(t_sh *sh, char *var)
{
	if (!ft_strichr(var, '='))
	{
		ft_putstr_fd("minishell: ", STDOUT_FILENO);
		return (p_error("export: `", var, "': not a valid identifier", 1));
	}
	set_env(var, NULL, sh);
	return (g_status = 0);
}

/*print export with no args, ordered and with var="value"*/
void	print_export(t_sh *sh)
{
	char	**env;
	int		i;
	int		j;
	char	*aux;

	env = set_export(sh);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			continue ;
		ft_putstr_fd("declare -x ", 1);
		aux = ft_strchr(env[i], '=');
		j = -1;
		while (env[i][++j] && env[i][j] != '=')
			ft_putchar_fd(env[i][j], 1);
		if (aux)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(aux + 1, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	mtr_free(env);
}

/*envs to export format*/
char	**set_export(t_sh *sh)
{
	char	**env;
	int		i;
	int		j;
	char	*temp;

	env = mtr_dup(sh->envp);
	i = -1;
	while (env[++i])
	{
		j = i;
		while (env[++j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
		}
	}
	return (env);
}
