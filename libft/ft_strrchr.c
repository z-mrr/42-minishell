/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:09:02 by jdias-mo          #+#    #+#             */
/*   Updated: 2021/10/26 17:22:05 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*a;
	unsigned int	i;

	a = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			a = (char *)s + i;
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (a);
}
