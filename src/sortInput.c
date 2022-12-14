/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/14 17:11:35 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* return 1 se input acabar por ser nulo */
int	sortInput(t_sh *f)
{
	printf("\n\n                                       ### WORDS ###                         \n\n");
	if (createWords(f))
		return (1);
	printList(f->token);
	printf("\n\n                                       ### LEXER ###                         \n\n");
	if (_expander(f))
		return (1);
	printList(f->token);
	printf("\n\n                                       ### PARSER ###                        \n\n");
	if (parsecmd(f))
		return (1);
	printf("\n\n                                       ### NO FINAL ###                      \n\n");
	printList(f->token);
	printListCmd(f->cmd);
	printf("\n                                        ...free...                              \n");
	freeTokens(f);
	return (0);
}
