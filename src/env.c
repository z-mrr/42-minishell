/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:51:07 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/17 21:51:58 by jdias-mo         ###   ########.fr       */
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

/*return valor de env*/
char	*get_env(char *var, t_sh *sh)
{
	int	pos;

	pos = pos_env(var, sh->envp);
	if (pos < 0)
	{
	//	perror("get_env");
		return (NULL);
	}
	return(ft_strdup(sh->envp[pos] + (ft_strlen(var) + 1)));//return de mallocd string after =
}

/*modifica valor de env se já existente ou adiciona env se nao existe*/
void	set_env(char *var, char *value, t_sh *sh)
{
	int		pos;
	char	*aux[2];

	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	pos = pos_env(var, sh->envp);
	if (pos < 0)
	{
		sh->envp = mtr_add(aux[1], sh->envp);
		free(aux[1]);
	}
	else
	{
		aux[0] = sh->envp[pos];
		sh->envp[pos] = aux[1];
		free(aux[0]);
	}
}

/*remove env*/
void	rmv_env(char *var, t_sh *sh)
{
	int		pos;

	pos = pos_env(var, sh->envp);
	if (pos < 0)
	{
	//	perror("rmv_env");
		return ;
	}
	sh->envp = mtr_rmv(pos, sh->envp);
}

/*verifica se ha, return pos. -1 se nao houver*/
int	pos_env(char *var, char **envp)
{
	char	*aux;
	int		i;
	int		len;

	if (!envp || !*envp)
		return (-1);
	aux = ft_strjoin(var, "=");
	len = ft_strlen(aux);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], aux, len))
		{
			free(aux);
			return (i);
		}
	}
	free(aux);
	return (-1);
}
