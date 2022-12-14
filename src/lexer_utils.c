#include "../inc/minishell.h"

void	ddl_removeToken(t_token **head, t_token *node)
{
	if (*head == NULL || node == NULL)
		return ;
	if (*head == node)
		*head = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	free(node);
}

int	_endVarPos(char *s, int pos)
{
	while (s[pos] != '\0')
	{
		if (s[pos] == '$' || s[pos] == 34 || s[pos] == 39 || s[pos] == ' ' || s[pos - 1] == '?')
			return (pos);
		pos++;
	}
	return (pos);
}

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
