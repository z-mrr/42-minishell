/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 23:32:06 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/05 20:01:45 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*CTRL+C quebra de nova linha limpa*/
void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
/*interceta sinais CTRL+C e CTRL+\, ignorando o último.
não precisa de intercetar CTRL+D, pois o seu comportamento é o esperado*/
void handle_sig()
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
