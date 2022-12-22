/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 01:23:06 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/19 02:36:25 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_wait(t_sh *sh)
{
	int	wstatus;

	while (sh->i)
		{
			wait(&wstatus);
			if (WIFSIGNALED(wstatus))
				wstatus += 128;
			if (sh->fork)
				g_status = wstatus;
			sh->i--;
		}
		if (g_status > 255)
			g_status = g_status / 255;
		if (g_status == 13)
			g_status = 0;
}

void	ft_ctrld(t_sh *sh)
{
	clear_history();
	free_all(sh);
	exit(g_status);
}

int	is_dir(char *path)
{
	DIR	*dir;
	int	ret;

	if (!path)
		return (0);
	ret = 0;
	dir = opendir(path);
	if (dir)
		ret = 1;
	closedir(dir);
	return (ret);
}

/*returna primeiro index de char na string*/
int	ft_strichr(char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

/*compara strings*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	n;
	int	len[2];

	if (!s1 || !s2)
		return (-1);
	len[0] = ft_strlen(s1);
	len[1] = ft_strlen(s2);
	if (len[0] > len[1])
		n = len[0];
	else
		n = len[1];
	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (i == n)
		i--;
	return (s1[i] - s2[i]);
}
