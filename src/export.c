/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:15:11 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 00:19:52 by jdias-mo         ###   ########.fr       */
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
		if (str[i] == 'c')
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

/*compara strings*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	unsigned int		n;

	i = 0;
	n = ft_strlen(s1) + ft_strlen(s2);
	if (n == 0)
		return (0);
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

/*print export*/
int	print_export(t_sh *sh)
{
	char	**env;
	int		i;

	env = set_export(sh);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "_=", 2))
			continue ;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putchar_fd('\n', 1);
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
			i = -1;
			while (++i < n)
			{
				j = ft_strichr(test[i], '=');
				if(j < 1)
					return (0);//
				var = ft_substr(test[i], 0, j);
				value = ft_strdup(test[i] +  (j + 1));
				set_env(var, value, sh);
			}
	}
	else
		print_export(sh);
	return (0);
}
