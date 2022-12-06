/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/06 15:04:15 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_sh *sh, char *str)
{
	free (str);
	free_mtr(sh->envp);
}

/*inicializa variaveis, duplica envp, incrementa $SHLVL em envp*/
void	init_shell(int argc, char **argv, char **envp, t_sh *sh)
{
	char	*temp;
	int		shlvl;

	(void)argc;
	(void)argv;
	sh->cmds = NULL;
	sh->envp = mtr_dup(envp);
	temp = get_env("SHLVL", sh->envp);
	shlvl = ft_atoi(temp);
	free(temp);
	shlvl++;
	temp = ft_itoa(shlvl);
	set_env("SHLVL", temp, sh->envp);
	free(temp);
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;
	char	*str;

	init_shell(argc, argv, envp, &sh);
	while(1)
	{
		handle_sig();
		str = get_str();
		if(!str)//case ;
			continue ;
		free_shell(&sh, str);
	}
	return (0);
}
