/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:11 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 13:17:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*export no options. mudar test para sh->cmds->content->args*/
int	ft_export(t_sh *sh)
{
	int		n;
	int		i;
	int		j;
	char	*var;
	char	*value;

	n = mtr_len(sh->test);
	if (n > 1)
	{
			i = 0;
			while (++i < n)
			{
				j = ft_strichr(sh->test[i], '=');
				if (j < 1)
					return (0);//
				var = ft_substr(sh->test[i], 0, j);
				value = ft_strdup(sh->test[i] +  (j + 1));
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
int	ft_exit(t_sh *sh)
{
	int	status;
	int	n;

	n = mtr_len(sh->test);
	if (n > 2)
	{
		mtr_free(sh->test);
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		return (1);
	}
	status = 0;
	if (n == 2)
	{
		exit_check(sh->test);
		status = ft_atoi(sh->test[1]);
	}
	mtr_free(sh->test);
	exit(status);
}

/*exit -1 if argument isnt valid*/
void	exit_check(char **str)
{
	int	i;

	i = 0;
	while (str[1][i] == ' ' || str[1][i] == '\t')
		i++;
	if (str[1][i] == '+' || str[1][i] == '-')
		i++;
	while(str[1][i])
	{
		if (!ft_isdigit(str[1][i]) || i >= 20)
		{
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd(str[1], 1);
			ft_putendl_fd(": numeric argument required", 1);
			mtr_free(str);
			exit(-1);
		}
		i++;
	}
}
