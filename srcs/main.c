/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/03 01:04:32 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_frame	*main_f = (t_frame *)malloc(sizeof(t_frame)); //gde

	(void)argc;
	(void)argv;
	(void)envp;
	//init envs
	while(1)
	{
		handle_sig();
		str = get_str();
		ft_lexer_split(main_f, str);
		if(!str)//case ;
			continue ;
		free(str);
	}
	return (0);
}
