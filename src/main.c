/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/07 19:28:56 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*inicializa variaveis, duplica envp, incrementa $SHLVL em envp*/
void	init_sh(int argc, char **argv, char **envp, t_sh *sh)
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
	//tests
	/*
	int i = 0;
	while ((sh->envp)[i])
		printf("%s\n", (sh->envp)[i++]);
	printf("\n");
	printf("\tLEN = %d\n", mtr_len(sh->envp));
	printf("\n\n");
	printf("\tpos = %d\n", pos_env("_", envp));
	sh->envp = rmv_env("_", sh->envp);
	printf("\tLEN = %d\n", mtr_len(sh->envp));
	printf("\n");
	i = 0;
	while ((sh->envp)[i])
		printf("%s\n", (sh->envp)[i++]);
	*/
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;
	char	*str;

	init_sh(argc, argv, envp, &sh);
	while(1)
	{
		handle_sig();
		str = get_str();
		if(!str)//case ;
			continue ;
		free(str);
	}
	return (0);
}
