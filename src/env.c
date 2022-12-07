/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:34:21 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/07 19:26:37 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*return valor de env*/
char	*get_env(char *var, char **envp)
{
	int		len;
	int		i;
	char	*aux;

	aux = ft_strjoin(var, "=");
	len = ft_strlen(aux);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], aux, len))
		{
			free(aux);
			return(ft_strdup(envp[i] + len));
		}
	}
	return (NULL);
}


/*modifica valor de env já existente*/
void	set_env(char *var, char *value, char **envp)
{
	int		len;
	int		i;
	char	*aux[3];

	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	len = ft_strlen(aux[0]);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], aux[0], len))
		{
			aux[2] = envp[i];
			envp[i] = aux[1];
			free(aux[2]);
			free(aux[0]);
			return ;
		}
	}
	free(aux[1]);
	free(aux[0]);
}

/*adiciona nova env*/
char	**add_env(char *var, char *value, char **envp)
{
	char	*aux[2];
	char	**ret;

	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	ret = mtr_add(aux[1], envp);
	free(aux[1]);
	return (ret);
}
/*remove env*/
char	**rmv_env(char *var, char **envp)
{
	int		pos;
	char	**ret;

	pos = pos_env(var, envp);
	ret = mtr_rmv(pos, envp);
	return (ret);
}

/*verifica se ha e return pos, é preciso para dar a pos no mtr_rmv*/
int	pos_env(char *var, char **envp)
{
	char	*aux;
	int		i;
	int		len;

	aux = ft_strjoin(var, "=");
	len = ft_strlen(aux);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], aux, len))
			break ;
		i++;
	}
	free(aux);
	return (i);
}
