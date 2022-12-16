/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortInput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/16 20:19:08 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* return 1 se input acabar por ser nulo */
int	sortInput(t_sh *f)
{
	if (create_words(f))
		return (1);
	print_list(f->token);
	printf("\n\n                                       ### LEXER ###                         \n\n");
	if (_expander(f))
		return (1);
	print_list(f->token);
	printf("\n\n                                       ### PARSER ###                        \n\n");
	if (parsecmd(f) != 0)
		return (1);
	printf("\n\n                                       ### NO FINAL ###                      \n\n");
	print_listcmd(f->cmd);
	printf("\n                                        ...free...                              \n");
	return (0);
}
