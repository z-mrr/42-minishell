/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/12 23:01:39 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* adiciona token a cmd struct, se OP cria novo node da cmd struct*/
void	parseCmds(t_sh *f)
{

	t_token *token;
	t_cmd *head;

	token = f->token;
	head = NULL;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	f->cmds = head;
	initCmd(head);
	while (token != NULL)
	{
		if (token->token_type == 'O') /* op */
		{
			if (token->next == NULL)
				break ;
			if (ft_strcmp(token->token_str, "|"))
			{
				ddl_append(head);
				head = head->next;
				initCmd(head);
				//printf("gdb");exit(-1);
			}
		}
			else
				addStrCmd(head, token->token_str);
		token = token->next;
	}
}

/* return se input acabar por ser nulo */
void	sortInput(t_sh *f)
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
