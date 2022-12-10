/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/10 20:41:35 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_dll(t_frame *f)
{
	t_token **head;
	t_token *tmp;

	head = &(f->token);
	if ((*head)->prev == NULL && (*head)->next == NULL) /* unico*/
	{
		printf("[1]REMOVE NODE: %p\n", *head);
		free(*head);
		f->token = NULL;
	}
	else if ((*head)->prev == NULL && (*head)->next != NULL) /* se for o 1 */
	{
		tmp = *head;
		*head = (*head)->next;
			printf("[2]REMOVE NODE: %p\n", tmp);
		free(tmp);
		(*head)->prev = NULL;
			printf("[2]REMOVE NODE - NEW 1st NODE: %p\n", f->token);
		printList(f->token);
	}
	else if ((*head)->next == NULL && (*head)->prev != NULL) /* se for o ultimo */
	{
		tmp = *head;
		*head = (*head)->prev;
			printf("[3]REMOVE NODE: %p\n", tmp);
		free(tmp);
		(*head)->next = NULL;
			printf("[3]REMOVE NODE - NEW last NODE: %p\n", *head);
		printList(f->token);
	}
	else /* qq outro */
	{
		tmp = *head;
		*head = (*head)->next;
			printf("[4]REMOVE NODE: %p\n", tmp);
		(*head)->prev->next = (*head)->next;
		(*head)->next->prev = (*head)->prev;
		free(tmp);
		//exit(-1);
		//printList(f->token);
	}
}

/* return em caso de !str */
int	lexer(t_frame *f)
{
	printf("..lexer..\n");
	printList(f->token);
	while (f->token->next != NULL)
	{
		if (tokenizeWord(f))
			remove_dll(f);
		else
			f->token = f->token->next;
	}
	if (tokenizeWord(f))
		remove_dll(f);
	if (f->token == NULL)
	{	
		printf("\nNo match found\n");
		return (1);
	}
	while (f->token->prev != NULL) /*man de dll*/
		f->token = f->token->prev;
	return (0);
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

/* return se input acabar por ser nulo */
void	sortInput(t_frame *f)
{
	createWords(f);
	printf("\n##########################################################\n");
	if (lexer(f))
		return ;
	printf("\n##########################################################\n");
	printf("\nBEFORE PARSER\n");
	printList(f->token);
	free(f->str); // DAR FREE A STR DO READLINE!
	printf("\n##########################################################\n");
	parseCmds(f);
	printf("\n##########################################################\n");
}
