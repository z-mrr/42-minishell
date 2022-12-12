/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 09:18:40 by jdias-mo          #+#    #+#             */
/*   Updated: 2021/10/26 17:21:16 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*a;
	size_t	i;

	a = malloc(nmemb * size);
	if (!a)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		a[i] = 0;
		i++;
	}
	return ((void *)a);
}
