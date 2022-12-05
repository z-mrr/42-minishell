#include "../include/minishell.h"

void	printList(t_token *head)
{
	while (head != NULL)
	{
		printf("token: <<%s>>\n", head->token_str);
		head = head->next;
	}
}
/*
void	free_ll(t_token **head)
{
	while ((*head)->next != NULL)
	{
		
	}
}
*/

void append_ll(t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = NULL;
	new_node = (t_token *)malloc(sizeof(t_token *));

	last = *head;
	new_node->token_str = ft_strdup(s);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

int	lexer(char *s)
{
	int	pos;
	int	wd_begin;
	t_token *token;

	token = NULL;
	pos = 0;
	wd_begin = 0;
	while (s[pos] != '\0')
	{
		if (s[pos] == '\'' || s[pos] == '\"') //dentro de quotes 
		{
			pos = next_quote(s, pos);
			if (pos < 0)
				return (1); //$
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			wd_begin = ++pos;
		}
		else if (s[pos] == '$') //operators
		{
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			wd_begin = pos;
			pos++;
			append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			wd_begin = pos;
		}
		else if (s[pos] == ' ') //final de word
		{
			if (pos - wd_begin)
				append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin));
			while (s[pos] == ' ')
				pos++;
			wd_begin = pos;
		}
		else //args
			pos++;
	}
	if (pos - wd_begin)
		append_ll(&(token), ft_substr(s, wd_begin, pos - wd_begin)); //ultima palavra
	printf("current pos: %i - %c\n", pos, s[pos]);
	printList(token);
	return (0);
}
