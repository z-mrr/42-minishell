#include "libft.h"
/*
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!(s1) || !(s2))
		return (0);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i])
		return (0);
	return (1);
}*/

/*compara strings*/
int	ft_strcmp(char *s1, char *s2)
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
