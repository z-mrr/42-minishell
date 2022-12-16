/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/16 12:34:39 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

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

void	init_sh(t_sh *sh, char **envp)
{
	sh->envp = mtr_dup(envp);
	if (!(sh->envp))
	{
	//	perror("envp");
		return ;
	}
	sh->cmd = NULL;
	sh->token = NULL;
	sh->parser = NULL;
}

void init_parser(t_sh *sh)
{
	sh->parser = malloc(sizeof(t_parser));
	if(!sh->parser)
	{
		//perror
		return ;
	}
	sh->parser->str = NULL;
	sh->parser->pos = 0;
	sh->parser->wd_begin = 0;
}

/*inicializa variaveis, duplica envp, incrementa $SHLVL em envp*/
void	init(int argc, char **argv, char **envp, t_sh *sh)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	init_sh(sh, envp);
	init_parser(sh);
	shlvl(sh);
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh		sh;

	init(argc, argv, envp, &sh);
	while(1)
	{
		handle_sig();
		sh.parser->str = get_str(&sh);
		//sh.parser->str = argv[1];
		if (!sh.parser->str)//isto pq lexer n tava a lidar com \0 after strtrim. nao passam string nulas ou vazias
			continue ;
		sortInput(&sh);
		execInput(&sh);
		free(sh.parser->str);
		free_lists(&sh);
	}
	free_sh(&sh);
	exit(g_status);//
}


