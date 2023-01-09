/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:24:53 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:30:38 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	strn(char const *s, char c)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if ((s[i + 1] == c && s[i] != c) || (s[i + 1] == '\0' && s[i] != c))
			n++;
		i++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		n;
	char				**tab;

	n = 0;
	i = 0;
	j = 0;
	tab = malloc(sizeof(char *) * (strn(s, c) + 1));
	if (!tab)
		return (NULL);
	while (n < strn(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		tab[n] = ft_substr(s, j, i - j);
		if (!tab[n])
			return (NULL);
		n++;
	}
	tab[n] = 0;
	return (tab);
}
