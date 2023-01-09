/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 04:55:48 by jdias-mo          #+#    #+#             */
/*   Updated: 2023/01/09 19:40:28 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*exit with no options*/
int	ft_exit(t_cmd *cmd)
{
	int	status;
	int	n;

	n = mtr_len(cmd->full_cmd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (n > 2)
		return (p_error("minishell: ", "exit: too many arguments", NULL, 1));
	status = 0;
	if (n == 2)
	{
		exit_check(cmd->full_cmd);
		status = ft_atoi(cmd->full_cmd[1]);
	}
	mtr_free(cmd->full_cmd);
	exit(g_status = status);
}

/*exit -1 if argument isnt valid. i[1] is to not print spaces*/
void	exit_check(char **str)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (str[1][i[0]] == ' ' || str[1][i[0]] == '\t')
	{
		i[0]++;
		i[1]++;
	}
	if (str[1][i[0]] == '+' || str[1][i[0]] == '-')
		i[0]++;
	while (str[1][i[0]])
	{
		if (!ft_isdigit(str[1][i[0]]) || i[0] >= 20)
		{
			p_error("minishell: exit: ", str[1] + i[1],
				": numeric argument required", 2);
			mtr_free(str);
			exit(g_status = 2);
		}
		i[0]++;
	}
}
