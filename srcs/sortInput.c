/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/11 08:39:31 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parseCmds(t_frame *f)
{
	printf("...Parser...\n");
	append_dll_cmd(f, &(f->cmds));
	int	i = 0;
	while (f->token->next != NULL)
	{
		if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
		{
			parsePipes(f);	
			i = 0;
		}
		else
		{
			addStrCmd(f);
			f->token = f->token->next;
			printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
		}
	}
	if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
	{
		parsePipes(f);	
		i = 0;
	}
	else
	{
		addStrCmd(f);
		if (f->token->next != NULL)
			f->token = f->token->next;
		printf("cmd/arg~%i: %s\n",i, f->cmds->full_cmd[i]);i++;
	}
	while (f->token->prev != NULL)
		f->token = f->token->prev;
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
	printf("\n### WORDS ###\n");
	createWords(f);

	printf("\n### LEXER ###\n");
	lexer(f);

	printf("\n### BEFORE PARSER ###\n");
	printList(f->token);
	printf("\n### PARSER ###\n");
	parseCmds(f);
	freeTokens(f);
}
