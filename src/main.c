/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 03:08:49 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*tests*/
void	test(char **argv, t_sh *sh)
{
	(void)argv;
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
		printf("%s\n", (sh->envp)[i++]);*/
	char	**test;
	test = malloc(sizeof(char *) * 3);
	test[0] = ft_strdup("export");
	test[1] = ft_strdup("a=5");
	test[2] = NULL;
	ft_export(sh, test);
	printf("\n\texported a=5\n");
	char	**test2;
	test2 = malloc(sizeof(char *) * 3);
	test2[0] = ft_strdup("export");
	test2[1] = NULL;
//	printf("\n\tENV\n\n");
//	ft_env(sh);
	printf("\n\tEXPORT\n\n");
	ft_export(sh, test2);
	char **test3;
	test3=malloc(sizeof(char *) * 4);
	test3[0]= ft_strdup("unset");
	test3[1]= ft_strdup("b");
	test3[2]= ft_strdup("a");
	test3[3]= NULL;
	ft_unset(sh, test3);
	printf("\n\tunseted a\n");
	ft_export(sh, test2);
	printf("\n\tpwd\n");
	ft_pwd();
	mtr_free(test);
	mtr_free(test2);
	mtr_free(test3);
}

void	shlvl(t_sh *sh)
{
	char	*temp;
	int		shlvl;

	temp = get_env("SHLVL", sh);
	if(!temp)
	{
	//	perror("shlvl");
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
	//	perror("envp");
		return ;
	}
	shlvl(sh);
	//test
	test(argv, sh);
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
	exit(g_status);//
}
