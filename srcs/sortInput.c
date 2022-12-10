#include "../include/minishell.h"

void	remove_dll(t_frame *f)
{
	t_token **head;

	head = &(f->token);
	if ((*head)->prev == NULL && (*head)->next == NULL) /* se for o 1 */
	{
		free(*head);
		f->token = NULL;
	}
	else if ((*head)->prev == NULL) /* se for o 1 e noa unico*/
	{
		f->token = f->token->next;
		free(f->token->prev);
		f->token->prev = NULL;
	}
	else if ((*head)->next == NULL) /* se for o ultimo */
	{
		(*head)->prev->next = NULL;
		free(*head);
	}
	else
	{
		(*head)->prev->next = (*head)->next;
		(*head)->next->prev = (*head)->prev;
		free(*head);
	}
}

/*  */
void	lexer(t_frame *f)
{
	while (f->token->next != NULL)
	{
		if (tokenizeWord(f))
			remove_dll(f);
		if (f->token->next != NULL)
			f->token = f->token->next;
	}
	if (tokenizeWord(f))
		remove_dll(f);
	if (f->token == NULL)
	{	
		printf("nada para lexar\n");
		exit(-1);
	}
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
	//fill cmd struct
	printf("\nBEFORE PARSER\n");
}

/*  */
void	createWords(t_frame *f) //os operadores definem o resto dos tokens!!
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') //dentro de quotes 
			lexQuote(f);
		else if (findOperator(f->str[f->pos])) //operador
			lexOp(f);
		else if (f->str[f->pos] == ' ') //final de word
			lexWdend(f);
		else //args
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
}

void	sortInput(t_frame *f)
{
	createWords(f);
	lexer(f);
	printList(f->token);
	parseCmds(f);
}
