/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/17 21:44:10 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status;

void	oldpwd(t_sh *sh)
{
	int	i;
	char	*temp;

	i = -1;
	while (sh->envp[++i])
	{
		if(!ft_strncmp("OLDPWD", sh->envp[i], 6) && ft_strchr(sh->envp[i], '='))
		{
			temp = sh->envp[i];
			sh->envp[i] = ft_strdup("OLDPWD");
			free(temp);
		}
	}
	i = -1;
	while (sh->envp[++i])
	{
		if (!ft_strchr(sh->envp[i], '=') && ft_strncmp("OLDPWD", sh->envp[i], 6))
			sh->envp = mtr_rmv(i, sh->envp);
	}
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
void	init(int argc, char **argv, char **envp, t_sh *sh)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	sh->cmd = NULL;
	sh->token = NULL;
	sh->parser = NULL;
	sh->parser = malloc(sizeof(t_parser));
	if(!sh->parser)
	{
		//perror
		return ;
	}
	sh->parser->str = NULL;
	sh->parser->pos = 0;
	sh->parser->wd_begin = 0;
	sh->envp = mtr_dup(envp);
	if (!(sh->envp))
	{
		perror("fatal");
		exit(1);//
	}
	shlvl(sh);
	oldpwd(sh);
}

/*CTRL+C quebra de nova linha limpa*/
void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh		sh;

	init(argc, argv, envp, &sh);
	while(1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		sh.parser->str = get_str(&sh);
		if (!sh.parser->str)//nao passam string nulas ou vazias
			continue ;
		sortInput(&sh);
		free_str(sh.parser->str);
		execInput(&sh);
		free_token(&sh);
		free_cmd(&sh);
	}
	return (0);
}


