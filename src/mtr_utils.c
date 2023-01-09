/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:21:59 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*nao esquecer que devolve o numero de matrizes nao o index*/
int	mtr_len(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
}

void	mtr_free(char **m)
{
	int	i;

	i = -1;
	if (!m)
		return ;
	while (m[++i])
		free(m[i]);
	free(m);
	m = NULL;
}

/*duplica matriz*/
char	**mtr_dup(char **m)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (mtr_len(m) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (m[++i])
	{
		ret[i] = ft_strdup(m[i]);
		if (!ret[i])
		{
			mtr_free(ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}

/*adiciona string a matriz*/
char	**mtr_add(char *str, char **old)
{
	char	**new;
	int		len;
	int		i;

	len = mtr_len(old) + 1;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (old[++i])
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
		{
			mtr_free(new);
			mtr_free(old);
			return (NULL);
		}
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	if (!new[i])
		mtr_free(new);
	mtr_free(old);
	return (new);
}

/*remove string[pos] de matriz*/
char	**mtr_rmv(int pos, char **old)
{
	char	**new;
	int		i;
	int		len;

	len = mtr_len(old) - 1;
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (old[++i] && i < len)
	{
		if (i < pos)
			new[i] = ft_strdup(old[i]);
		else
			new[i] = ft_strdup(old[i + 1]);
		if (!new[i])
		{
			mtr_free(new);
			mtr_free(old);
			return (NULL);
		}
	}
	new[i] = NULL;
	mtr_free(old);
	return (new);
}
