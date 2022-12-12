
#include "../include/minishell.h"

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
