#include "../inc/minishell.h"

int	countPairs(char *s)
{
	int	i;
	int	pairs;
	char	c;

	i = 0;
	pairs = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34 || s[i] == 39)
		{
			c = s[i];
			i++;
			pairs++;
			while (s[i] != c)
				i++;
		}
		i++;
	}
	return (pairs);
}


/* remove pares de quotes */
void	rmvQuotes(t_token *node)
{
	int	i;
	int	j;
	char c;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ((ft_strlen(node->token_str) - (countPairs(node->token_str) * 2) + 1)));
	while (node->token_str[i] != '\0')
	{
		if (node->token_str[i] == 34 || node->token_str[i] == 39)
		{
			c = node->token_str[i++];
			while (node->token_str[i] != c)
				new_str[j++] = node->token_str[i++];
			i++;
		}
		else
			new_str[j++] = node->token_str[i++];
	}
	free(node->token_str);
	new_str[j] = '\0';
	node->token_str = new_str;
}
