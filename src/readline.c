/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:15:40 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/18 17:12:22 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*gets dir for prompt, replace home with ~*/
char	*get_dir(t_sh *sh)
{
	char	*pwd;
	char	*home;
	char	*dir;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅");
	home = get_env("HOME", sh);
	if (home && !(ft_strncmp(pwd, home, ft_strlen(home))))
		dir = ft_strjoin("~", pwd + ft_strlen(home));
	else
		dir = ft_strdup(pwd);
	free(pwd);
	free(home);
	return (dir);
}

/*gets user for prompt, guest if no user env*/
char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (user)
		user = ft_strdup(user);
	else
		user =  ft_strdup("guest");
	return (user);
}

/*$ azul sem erro, vermelho se erro*/
char	*get_prompt(t_sh *sh)
{
	char	*aux[3];

	aux[2] = get_user();
	aux[0] = ft_strjoin(WHT, aux[2]);
	free(aux[2]);
	aux[1] = ft_strjoin(aux[0], BLK);
	free(aux[0]);
	aux[0] = ft_strjoin(aux[1], " ● ");
	free(aux[1]);
	aux[1] = ft_strjoin(aux[0], WHT);
	free(aux[0]);
	aux[2] = get_dir(sh);
	aux[0] = ft_strjoin(aux[1], aux[2]);
	free(aux[2]);
	free(aux[1]);
	if (!g_status)
		aux[1] = ft_strjoin(aux[0], BLU);
	else
		aux[1] = ft_strjoin(aux[0], RED);
	free(aux[0]);
	aux[0] = ft_strjoin(aux[1], " $ ");
	free(aux[1]);
	aux[1] = ft_strjoin(aux[0], DEFAULT);
	free(aux[0]);
	return(aux[1]);
}

/*prompt, readline, adiciona à história line já tratada
sem espaços ou se for ;*/
char	*get_str(t_sh *sh)
{
	char	*str;
	char	*line;
	char	*prompt;

	prompt = get_prompt(sh);
	line = readline(prompt);
	if (!line)//case CTRL+D
	{
		ft_putendl_fd("exit", 1);
		exiting(sh);
	}
	str = ft_strtrim(line, " \t");
	if (*str == '\0')//isto pq lexer n tava a lidar com \0 after strtrim
	{
		free(str);
		str = NULL;
	}
	if(str && *str)
		add_history(str);
	free(line);
	free(prompt);
	return (str);
}
