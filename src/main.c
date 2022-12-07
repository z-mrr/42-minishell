/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/07 22:49:02 by jdias-mo         ###   ########.fr       */
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
	temp = get_env("SHLVL", sh);
	shlvl = ft_atoi(temp);
	shlvl++;
	free(temp);
	temp = ft_itoa(shlvl);
	set_env("SHLVL", temp, sh);
	free(temp);
//	tests
/*	int i = 0;
	char *test;
	while ((sh->envp)[i])
		printf("%s\n", (sh->envp)[i++]);
	printf("\n");
	test = get_env("SHLL", sh);
	if (test)
		free(test);
	rmv_env("_", sh);
	set_env("SHELL", "done", sh);
	set_env("Ricardo", "Maior", sh);
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
