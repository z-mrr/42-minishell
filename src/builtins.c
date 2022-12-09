/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 01:56:42 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/09 03:13:10 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*pwd with no options*/
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);//
	ft_putendl_fd(pwd, 1);
	free (pwd);
	return (0);
}

/*unset with no options*/
int	ft_unset(t_sh *sh, char **test)
{
	int		i;
	int		n;

	n = mtr_len(test);
	if (n > 1)
	{
		i = 0;
		while (test[++i])
			rmv_env(test[i], sh);
	}
	return (0);
}

/*echo with option -n*/

/*exit with no options*/

/*cd with only a relative or absolute path*/
