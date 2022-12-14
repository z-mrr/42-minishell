/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:11 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/14 20:40:09 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
				if (j < 1)
					return (0);//
				var = ft_substr(cmd->full_cmd[i], 0, j);
				value = ft_strdup(cmd->full_cmd[i] +  (j + 1));
				set_env(var, value, sh);
				free(var);
				free(value);
			}
	}
	else
		print_export(sh);
	return (0);
}

/*print export with no args, ordered and with var="value"*/
int	print_export(t_sh *sh)
{
	char	**env;
	int		i;
	int		j;
	char	*value;
	char	*var;

	env = set_export(sh);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			continue ;
		ft_putstr_fd("declare -x ", 1);
		j = ft_strichr(env[i], '=');
		var = ft_substr(env[i], 0, j);
		value = ft_strdup(env[i] +  (j + 1));
		ft_putstr_fd(var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putstr_fd("\"\n", 1);
		free(var);
		free(value);
	}
	mtr_free(env);
	return (0);
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

/*exit with no options*/
int	ft_exit(t_cmd *cmd)
{
	int	status;
	int	n;

	n = mtr_len(cmd->full_cmd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (n > 2)
	{
		mtr_free(cmd->full_cmd);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	status = 0;
	if (n == 2)
	{
		exit_check(cmd->full_cmd);
		status = ft_atoi(cmd->full_cmd[1]);
	}
	mtr_free(cmd->full_cmd);
	exit(status);
}

/*exit -1 if argument isnt valid. i[1] is to not print spaces*/
void	exit_check(char **str)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[1][i[0]] == ' ' || str[1][i[0]] == '\t')
	{
		i[0]++;
		i[1]++;
	}
	if (str[1][i[0]] == '+' || str[1][i[0]] == '-')
		i[0]++;
	while(str[1][i[0]])
	{
		if (!ft_isdigit(str[1][i[0]]) || i[0] >= 20)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(str[1] + i[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			mtr_free(str);
			exit(-1);
		}
		i[0]++;
	}
}
