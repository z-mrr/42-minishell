/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:51:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return valor de env*/
char	*get_env(char *var, t_sh *sh)
{
	int	pos;

	pos = pos_env(var, sh->envp);
	if (pos < 0 || !ft_strchr(sh->envp[pos], '='))
		return (NULL);
	return (ft_strdup(sh->envp[pos] + (ft_strlen(var) + 1)));
}

/*modifica valor de env se já existente ou adiciona env se nao existe*/
int	set_env(char *var, char *value, t_sh *sh)
{
	int		pos;
	char	*aux[2];

	pos = pos_env(var, sh->envp);
	if (!value)
	{
		if (pos < 0)
			sh->envp = mtr_add(var, sh->envp);
		return (0);
	}
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	if (pos < 0)
	{
		sh->envp = mtr_add(aux[1], sh->envp);
		free(aux[1]);
		return (0);
	}
	aux[0] = sh->envp[pos];
	sh->envp[pos] = aux[1];
	free(aux[0]);
	return (0);
}

/*remove env*/
void	rmv_env(char *var, t_sh *sh)
{
	int		pos;

	pos = pos_env(var, sh->envp);
	if (pos < 0)
		return ;
	sh->envp = mtr_rmv(pos, sh->envp);
}

/*verifica se ha, return pos. -1 se nao houver*/
int	pos_env(char *var, char **envp)
{
	int		i;
	int		len;

	if (!envp || !*envp)
		return (-1);
	len = ft_strlen(var);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], var, len))
		{
			if (ft_strichr(envp[i], '=') == len
				|| ft_strichr(envp[i], '\0') == len)
				return (i);
		}
	}
	return (-1);
}
