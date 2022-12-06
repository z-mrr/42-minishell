/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:34:21 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/06 14:24:32 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *var, char **envp)
{
	int	len;
	int	i;

	len = ft_strlen(var);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return(ft_strdup(envp[i] + (len + 1)));
	}
	return (NULL);
}

void	set_env(char *var, char *value, char **envp)
{
	int		len;
	int		i;
	char	*aux[2];

	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	len = ft_strlen(var);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len))
		{
			aux[0] = envp[i];
			envp[i] = aux[1];
			free(aux[0]);
			return ;
		}
	}
	free(aux[1]);
}
