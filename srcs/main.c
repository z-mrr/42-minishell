/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 16:42:26 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sh	*create_frame(t_sh *frame, char **envp)
{
	frame = (t_sh *)malloc(sizeof(t_sh));
	if (!(frame))
		exit(1);
	frame->cmds = NULL;
	frame->token = NULL;
	frame->envp = envp;
	frame->last_pid = 0;
	frame->str = NULL;
	frame->pos = 0;
	frame->wd_begin = 0;
	return (frame);
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_sh	*frame;

	(void)argc;
	(void)argv;
	(void)envp;
	//init envs

	while(1)
	{
		handle_sig();
		if (argc > 1)
			str = ft_strdup(argv[1]);
		else
			str = get_str();
		frame = create_frame(frame, envp);
		if (str[0] == ' ')
			return (1);
		frame->str = ft_strdup(str);
		free(str);
		sortInput(frame);
		free(frame->str);
		free(frame);
		if (argc > 1)
			exit(-1);
	}
	return (0);
}
