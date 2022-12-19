/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:40 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/19 20:54:59 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* return 1 se input acabar por ser nulo */
int	sort_input(t_sh *f)
{
	if (create_words(f))
	{
		g_status = 2;
		return (1);
	}
	if (_expander(f))
		return (1);
	if (parsecmd(f) != 0)
		return (1);
	return (0);
}
