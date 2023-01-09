/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

/*elimina envs sem value e retira value do OLDPWD*/
void	oldpwd(t_sh *sh)
{
	int		i;

	i = -1;
	while (sh->envp[++i])
	{
		if (!ft_strchr(sh->envp[i], '='))
			sh->envp = mtr_rmv(i, sh->envp);
	}
	if (pos_env("OLDPWD", sh->envp) < 0)
		set_env("OLDPWD", NULL, sh);
}

/*aumenta shlvl*/
void	shlvl(t_sh *sh)
{
	char	*temp;
	int		shlvl;

	temp = get_env("SHLVL", sh);
	if (!temp)
		return ;
	shlvl = ft_atoi(temp);
	shlvl++;
	free(temp);
	temp = ft_itoa(shlvl);
	set_env("SHLVL", temp, sh);
	free(temp);
}

/*inicializa variaveis, duplica envp, incrementa $SHLVL em envp*/
int	init(int argc, char **argv, char **envp, t_sh *sh)
{
	(void)argc;
	(void)argv;
	g_status = 0;
	sh->pid = 0;
	sh->i = 0;
	sh->cmd = NULL;
	sh->token = NULL;
	sh->parser = NULL;
	sh->parser = malloc(sizeof(t_parser));
	if (!sh->parser)
		return (g_status = 1);
	sh->parser->str = NULL;
	sh->parser->pos = 0;
	sh->parser->wd_b = 0;
	sh->envp = mtr_dup(envp);
	if (!(sh->envp))
		exit(g_status = 1);
	shlvl(sh);
	oldpwd(sh);
	return (g_status);
}

/*CTRL+C quebra de nova linha limpa*/
void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_sh	sh;

	init(argc, argv, envp, &sh);
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		sh.parser->str = get_str(&sh);
		if (!sh.parser->str)
			continue ;
		if (sort_input(&sh) == 0)
			exec_input(&sh);
		ft_wait(&sh);
		free(sh.parser->str);
		free_tokens(&sh);
		free_cmd(&sh);
	}
	return (0);
}
