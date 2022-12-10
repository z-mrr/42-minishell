#include "../include/minishell.h"

void	printList(t_token *head)
{
	printf("\n                     ###########################################################\n");
	printf("\n                                          Mem                                    \n");
	while (head != NULL)
	{
		printf("\nIS TOKEN! ; ADRESS: %p; | ", &(head));
		printf("token_str: %s ; ADRESS: %p; | ", head->token_str, &(head->token_str));
		printf("token_type: %c ; ADRESS %p: \n", head->token_type, &(head->token_type));
		head = head->next;
	}
	printf("\n                     ###########################################################\n");
}

/* free lista de tokens - imcompleto */
void	free_dll(t_frame *f)
{
	while (f->token->next != NULL)
	{
		printf("vou dar free a %s\n", f->token->token_str);
		f->token = f->token->next;
		free(f->token->prev->token_str);
		f->token->prev->next = NULL;
		free(f->token->prev);
		f->token->prev = NULL;
	}
	printf("vou dar free a %s\n", f->token->token_str);
	free(f->token->token_str);
	free(f->token);
	f->token = NULL;
}

/* adiciona node de cmd */
void append_dll_cmd(t_frame *f, t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->full_cmd = NULL;
	new_node->path = NULL;
	new_node->in_fd = 0;
	new_node->out_fd = 1;
	new_node->err_fd = 2;
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

/* adiciona tipo de token */
void	addType_ll(t_frame *f, char type)
{
	t_token	*head;

	head = f->token;
	while (head->next != NULL)
		head = head->next;
	head->token_type = type;
}

/* adiciona mais um node (do tipo neutro) a lista de tokens */
void append_dll(t_frame *f, t_token **head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = NULL;
	new_node = (t_token *)malloc(sizeof(t_token));

	new_node->token_str = s;
	new_node->token_type = 'N';
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		new_node->next = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}
