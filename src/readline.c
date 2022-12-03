/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:15:40 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/03 01:04:31 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*user e dir no prompt, através da getenv=$USER e getcwd=wd*/
char	*get_prompt(void)
{
	char	*user;
	char	*dir;
	char	*prompt;
	char	buf[1024];

	user = ft_strjoin(getenv("USER"), " ► ");
	dir = getcwd(buf, 1024);
	while (*dir)
		dir++;
	while (*dir != '/')
		dir--;
	dir = ft_strjoin(dir, " ► ");
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

/*prompt, readline, adiciona à história line já tratada*/
char	*get_str(void)
{
	char	*str;
	char	*line;
	char	*prompt;

	prompt = get_prompt();
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
