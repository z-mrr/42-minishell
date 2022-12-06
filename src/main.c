/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:16 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/06 14:24:30 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell, char *str)
{
	free (str);
	free_mtr(shell->envp);
}

/*inicia variaveis, duplica envp, incrementa $SHLVL em envp*/
void	init_shell(int argc, char **argv, char **envp, t_shell *shell)
{
	char	*temp;
	int		shlvl;

	(void)argc;
	(void)argv;
	shell->cmds = NULL;
	shell->envp = mtr_dup(envp);
	temp = get_env("SHLVL", shell->envp);
	shlvl = ft_atoi(temp);
	free(temp);
	shlvl++;
	temp = ft_itoa(shlvl);
	set_env("SHLVL", temp, shell->envp);
	free(temp);
}

/*trata dos sinais, corta espaços no inicio e fim da string, adiciona à history,
dá erro se for ;, prompt personalizado com user e dir*/
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*str;

	init_shell(argc, argv, envp, &shell);
	while(1)
	{
		handle_sig();
		str = get_str();
		if(!str)//case ;
			continue ;
		free_shell(&shell, str);
	}
	return (0);
}
