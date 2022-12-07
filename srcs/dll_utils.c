#include "../include/minishell.h"

void	printList(t_token *head)
{
	while (head != NULL)
	{
		printf("token: \"  %s  \"\n", head->token_str);
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
	new_node = (t_token *)malloc(sizeof(t_token));

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
