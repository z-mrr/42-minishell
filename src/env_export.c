/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:51:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/08 21:35:36 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*env no options or arguments*/
int	ft_env(t_sh *sh)
{
	int	i;

	if (!*sh->envp)
		return (0);//
	i = -1;
	while(sh->envp[++i])
	{
		ft_putstr_fd(sh->envp[i], 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}

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
		return (i)
	return (-1);
}

/*print declare -x envs oredered by ascii*/
int	print_export(t_sh *sh)
{
	return (0);
}

/*export no options*/
int	ft_export(t_sh *sh)
{
	int		n;
	int		i;
	int		j;
	char	*var;
	char	*value;

	n = mtr_len(sh->cmds->content->args);
	if (n > 1)
	{
			i = -1;
			while (++i < n)
			{
				j = ft_strichr(sh->cmds->content->args[i], '=');
				if(j < 1)
					return (0);
				var = ft_substr(sh->cmds->content->args[i], 0, j);
				value = ft_strdup(sh->cmds->content->args[i] +  (j + 1));
				set_env(var, value, sh);
			}
	}
	else
		print_export(t_sh *sh);
	return (0);
}

/*unset no options*/

/*pwd no options*/

/*cd one_relativer_or_absolute_path*/

/*echo -n*/

/*exit no options*/


