/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/08 15:32:48 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*tests*/
void	test(t_sh *sh)
{
	int i = 0;
/*	char *test;
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
	i = 0;*/
	while ((sh->envp)[i])
		printf("%s\n", (sh->envp)[i++]);

}

void	shlvl(t_sh *sh)
{
	char	*temp;
	int		shlvl;

	temp = get_env("SHLVL", sh);
	if(!temp)
	{
		perror("shlvl");
		return ;
	}
	shlvl = ft_atoi(temp);
	shlvl++;
	free(temp);
	temp = ft_itoa(shlvl);
	set_env("SHLVL", temp, sh);
	free(temp);
}

/*inicializa variaveis, duplica envp, incrementa $SHLVL em envp*/
void	init_sh(int argc, char **argv, char **envp, t_sh *sh)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	sh->cmds = NULL;
	sh->envp = mtr_dup(envp);
	if (!(sh->envp))
	{
		perror("envp");
		return ;
	}
	shlvl(sh);
	//test
//	test(sh);
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
		str = get_str(&sh);
		free(str);
	}
	exit(g_status);
}
