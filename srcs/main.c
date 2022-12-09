/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 20:55:12 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_frame	*create_frame(t_frame *frame, char **envp, char *s)
{
	frame = (t_frame *)malloc(sizeof(t_frame));
	if (!(frame))
		exit(1);
	frame->cmds = NULL;
	frame->token = NULL;
	frame->envp = envp;
	frame->last_pid = 0;
	frame->str = ft_strdup(s);
	free(s);
	frame->new_str = NULL;
	frame->pos = 0;
	frame->wd_begin = 0;
	return (frame);
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_frame	*frame;

	(void)argc;
	(void)argv;
	(void)envp;
	//init envs

	while(1)
	{
		handle_sig();
		str = get_str();
		frame = create_frame(frame, envp, str);
		tokenizer(frame);
		free(frame->str);
		free(frame);
	}
	return (0);
}
