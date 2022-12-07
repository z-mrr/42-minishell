/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:21:59 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/07 12:42:00 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mtr_len(char **m)
{
	int	i = 0;

	while (m && m[i])
		i++;
	return (i);
}

void	free_mtr(char **m)
{
	int	i;

	i = -1;
	if (!m)
		return ;
	while (m[++i])
		free(m[i]);
	free(m);
}

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
			free_mtr(ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}
