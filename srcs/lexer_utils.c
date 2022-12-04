#include "../include/minishell.h"

int	ft_countWords(char const *s, char c)
{
	size_t	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (i > 0 && s[i] && s[i - 1] == c)
			nbr++;
		if (s[i])
			i++;
	}
	if (nbr == 0 && s[i - 1] == c)
		return (0);
	if (s[0] != c)
		nbr++;
	return (nbr);
}

void	ft_split_free(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	while (i > 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

void	ft_ll_free(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int	ft_ll_append(t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->token_str = ft_strdup(s);
	free(s);
	//printf("fl_ll_append->new_node_str:%s\n", new_node->token_str);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	return (ft_countWords(new_node->token_str, ' '));
}
