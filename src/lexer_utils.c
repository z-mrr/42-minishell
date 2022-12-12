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
void	rmvQuotes(t_sh *f)
{
	int	i;
	int	j;
	char c;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ((ft_strlen(f->token->token_str) - (countPairs(f->token->token_str) * 2) + 1)));
	while (f->token->token_str[i] != '\0')
	{
		if (f->token->token_str[i] == 34 || f->token->token_str[i] == 39)
		{
			c = f->token->token_str[i++];
			while (f->token->token_str[i] != c)
				new_str[j++] = f->token->token_str[i++];
			i++;
		}
		else
			new_str[j++] = f->token->token_str[i++];
	}
	free(f->token->token_str);
	new_str[j] = '\0';
	f->token->token_str = new_str;
}
