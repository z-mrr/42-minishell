/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:11 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 04:37:00 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returna primeiro index de char na string*/
int	ft_strichr(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

/*compara strings*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	n;
	int	len[2];

	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (len[0] > len[1])
		n = len[0];
	else
		n = len[1];
	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		i--;
	return (s1[i] - s2[i]);
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

/*export no options. mudar test para sh->cmds->content->args*/
int	ft_export(t_sh *sh, char **test)
{
	int		n;
	int		i;
	int		j;
	char	*var;
	char	*value;

	n = mtr_len(test);
	if (n > 1)
	{
			i = 0;
			while (++i < n)
			{
				j = ft_strichr(test[i], '=');
				if (j < 1)
					return (0);//
				var = ft_substr(test[i], 0, j);
				value = ft_strdup(test[i] +  (j + 1));
				set_env(var, value, sh);
				free(var);
				free(value);
			}
	}
	else
		print_export(sh);
	return (0);
}
