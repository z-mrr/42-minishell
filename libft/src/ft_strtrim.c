/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 13:10:15 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:30:38 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const s1, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (check(s1[i], set) == 1)
		i++;
	if (i >= ft_strlen(s1))
		return (str = ft_substr(s1, 0, 0));
	j = ft_strlen(s1);
	while (check(s1[j - 1], set) == 1)
		j--;
	str = ft_substr(s1, i, j - i);
	return (str);
}
