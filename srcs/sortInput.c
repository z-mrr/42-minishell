/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/11 19:31:13 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    printListCmd(t_cmd *head);

void	initCmd(t_cmd *node)
{
	node->full_cmd = NULL;
	node->path = NULL;
	node->in_fd = 0;
	node->out_fd = 1;
	node->err_fd = 2;
	node->next = NULL;
	node->prev = NULL;
}

void	ddl_append(t_cmd *last)
{
	t_cmd	*new_node;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));

	new_node->next = NULL;
	new_node->prev = last->prev;
	last->prev->next = new_node;
}


/* adiciona token a cmd struct, se | cria novo node da cmd struct*/
void	parseCmds(t_frame *f)
{

	t_token *token;
	t_cmd *head;

	token = f->token;
	head = NULL;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	initCmd(head);
	while (token != NULL)
	{
		if (token->token_type == 'O')
		{
			if (ft_strcmp(token->token_str, "|"))
			{
				ddl_append(head);
				head = head->next;
				initCmd(head);
			}
		}
		else
			addStrCmd(head, token->token_str);
		if (token->next == NULL)
			break ;
		token = token->next;
	}	
	while (head->prev != NULL)
		head = head->prev;
	f->cmds = head;
}


/* separa input por palaras; se algum par de quotes não fechar da erro */
void	createWords(t_frame *f)
{
	while (f->str[f->pos] != '\0')
	{
		if (f->str[f->pos] == '\'' || f->str[f->pos] == '\"') /* errno */
			lexQuote(f);
		else if (findOperator(f->str[f->pos]))
			lexOp(f);
		else if (f->str[f->pos] == ' ')
			lexWdend(f);
		else
			f->pos++;
	}
	if (f->pos - f->wd_begin)
		append_dll(f, &(f->token), ft_substr(f->str, f->wd_begin, f->pos - f->wd_begin)); //ultima palavra 
	printf("current f->pos: %i - %c\n", f->pos, f->str[f->pos]);
}

/* return se input acabar por ser nulo */
void	sortInput(t_frame *f)
{
	printf("\n\n                                       ### WORDS ###                         \n\n");
	createWords(f);
	printList(f->token);
	printf("\n\n                                       ### LEXER ###                         \n\n");
	lexer(f);
	printList(f->token);
	printf("\n\n                                       ### PARSER ###                        \n\n");
	parseCmds(f);
	printf("\n\n                                       ### NO FINAL ###                      \n\n");
	printList(f->token);
	printListCmd(f->cmds);
	printf("\n                                        ...free...                              \n");
	freeTokens(f);
}
