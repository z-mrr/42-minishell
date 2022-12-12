/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/12 23:52:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	sh->cmds = NULL;
	sh->token = NULL;
//	sh->envp = envp;//que é isto?
	sh->last_pid = 0;
	sh->str = NULL;
	sh->pos = 0;
	sh->wd_begin = 0;
}


/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	init_sh(argc, argv, envp, &sh);
	//TESTS <================================================================
//	tests(&sh);
	while(1)
	{
		handle_sig();
		sh.str = get_str(&sh);
		if (!sh.str)//isto pq lexer n tava a lidar com \0 after strtrim
			continue ;
		sortInput(&sh);
		free(sh.str);
	}
	mtr_free(sh.envp);
	exit(g_status);//
}
