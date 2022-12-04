#include "libft.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	if (dest == NULL)
		dest = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
