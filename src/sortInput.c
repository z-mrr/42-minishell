/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/13 23:18:56 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* adiciona token a cmd struct, se OP cria novo node da cmd struct*/
void	parsecmd(t_sh *f)
{

	t_token *token;
	t_cmd *head;

	token = f->token;
	head = NULL;
	head = (t_cmd *)malloc(sizeof(t_cmd));
	f->cmd = head;
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

/* return 1 se input acabar por ser nulo */
int	sortInput(t_sh *f)
{
	printf("\n\n                                       ### WORDS ###                         \n\n");
	if (createWords(f))
		return (1);
	printList(f->token);
	printf("\n\n                                       ### LEXER ###                         \n\n");
	//lexer(f);
	_expander(f);
	printList(f->token);
	printf("\n\n                                       ### PARSER ###                        \n\n");
	parsecmd(f);
	printf("\n\n                                       ### NO FINAL ###                      \n\n");
	printList(f->token);
	printListCmd(f->cmd);
	printf("\n                                        ...free...                              \n");
	freeTokens(f);
	return (0);
}
