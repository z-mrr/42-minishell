/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-alme <gde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:25 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/11 08:34:26 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parsePipes(t_frame *f)
{
	append_dll_cmd(f, &(f->cmds));
	f->cmds = f->cmds->next;
	f->token = f->token->next;
	printf("fazer pipe\n");
}

int	charArrayLen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

/* adiciona mais uma palavra ao cmd/args faz ja update do f->token */
void	addStrCmd(t_frame *f)
{
	char	**new_cmd;
	int	i;

	i = 0;
	if (f->cmds->full_cmd == NULL)
	{
		f->cmds->full_cmd = (char **)malloc(sizeof(char *) * 2);
		f->cmds->full_cmd[0] = ft_strdup(f->token->token_str);
		f->cmds->full_cmd[1] = 0;
		f->token = f->token->next;
		return ;
	}
	new_cmd = (char **)malloc(sizeof(char *) * ((charArrayLen(f->cmds->full_cmd) + 2)));
	while (f->cmds->full_cmd[i])
	{
		new_cmd[i] = ft_strdup(f->cmds->full_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(f->token->token_str);
	new_cmd[++i] = 0;
	free(f->cmds->full_cmd);
	f->cmds->full_cmd = new_cmd;
}
