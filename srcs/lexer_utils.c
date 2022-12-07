#include "../include/minishell.h"

void	printList(t_token *head)
{
	while (head != NULL)
	{
		printf("token: <<%s>>\n", head->token_str);
		head = head->next;
	}
}

void	free_ll(t_token *head)
{
	t_token *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void append_ll(t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = NULL;
	new_node = (t_token *)malloc(sizeof(t_token *));

	new_node->token_str = ft_strdup(s);
	new_node->token_type = NULL;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

int	next_quote(char *s, int pos)
{
	int	sig;

	sig = 1;
	if (s[pos] == 34)
	{
		pos++;
		while (s[pos] != 34 && s[pos])
		{
			if (s[pos + 1] == 34)
				sig = 0;
			//if (s[pos] == '$') handle token
			pos++;
		}
	}
	else
	{
		pos++;
		while (s[pos] != 39 && s[pos])
		{
			if (s[pos + 1] == 39)
				sig = 0;
			pos++;
		}
	}
	if (sig)
		return (-1);
	while (s[pos] != ' ' && s[pos])
		pos++;
	return (pos);
}
