/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:04:03 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 12:09:45 by jdias-mo         ###   ########.fr       */
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


