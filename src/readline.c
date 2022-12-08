/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:15:40 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/08 12:55:31 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*gets dir for prompt, replace home with ~*/
char	*get_dir(t_sh *sh)
{
	char	*pwd;
	char	*home;
	char	*dir;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅");
	home = get_env("HOME", sh);
	if (home && !(ft_strncmp(pwd, home, ft_strlen(home))))
	{
		temp = ft_strjoin("~", pwd + ft_strlen(home));
		dir = ft_strjoin(temp, " ► ");
		free(temp);
	}
	else
		dir = ft_strjoin(pwd, " ► ");
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
		user = ft_strjoin(user, " ► ");
	else
		user =  ft_strjoin("guest", " ► ");
	return (user);
}

/*user e dir no prompt, através da getenv=$USER e getcwd=pwd*/
char	*get_prompt(t_sh *sh)
{
	char	*prompt;
	char	*user;
	char	*dir;

	user = get_user();
	dir = get_dir(sh);
	prompt = ft_strjoin(user, dir);
	free(user);
	free(dir);
	return(prompt);
}

/*retira os espaços no inicio e final da str
dá erro de syntax se str começar por ; tal como bash*/
char	*resolve_str(char	*line)
{
	char	*str;

	str = ft_strtrim(line, " ");
	if (*str == ';')
	{
		printf("%s `;'\n", SYNTAX_ERR);
		free(str);
		str = NULL;
	}
	return (str);
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
		exit(0);
	str = resolve_str(line);
	if(str && *str)
		add_history(str);
	free(line);
	free(prompt);
	return (str);
}
