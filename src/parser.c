/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:16:25 by gde-alme          #+#    #+#             */
/*   Updated: 2022/12/16 02:11:36 by gde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
int	charArrayLen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

/* adiciona mais uma palavra ao cmd/args faz ja update do f->token */
void	addStrCmd(t_cmd *node, char *s)
{
	char	**new_cmd;
	int	i;

	i = 0;
	if (node->full_cmd == NULL)
	{
		node->full_cmd = (char **)malloc(sizeof(char *) * 2);
		node->full_cmd[0] = ft_strdup(s);
		node->full_cmd[1] = 0;
		return ;
	}
	new_cmd = (char **)malloc(sizeof(char *) * ((charArrayLen(node->full_cmd) + 2)));
	while (node->full_cmd[i])
	{
		new_cmd[i] = ft_strdup(node->full_cmd[i]);
		free(node->full_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(s);
	new_cmd[++i] = 0;
	free(node->full_cmd);
	node->full_cmd = mtr_dup(new_cmd);
	mtr_free(new_cmd);
}


/* parse dos ops, se | cria novo cmd*/
int parseOperators(t_sh *f, t_cmd *node, t_token *token)
{
	if (token->next == NULL)
		{printf("minishell: syntax error near unexpected token '%s'\n", token->token_str);return (1);}
	else
	{
		if (token->next->token_type == 'O' || token->prev == NULL)
			{printf("minishell: syntax error near unexpected token '%s'\n", token->token_str);return (1);}
	}
	if (!(ft_strcmp(token->token_str, "|")))
	{
		ddl_append(&(f->cmd));
		node = node->next;
		initCmd(node);
	}
	else
		return (parse_redirecs(f, node, token));
	return (0);
}

/* adiciona token a cmd struct, se OP cria novo node da cmd struct*/
int	parsecmd(t_sh *f)
{

	t_token *token;
	t_cmd *node;

	token = f->token;
	node = NULL;
	ddl_append(&(f->cmd));
	node = f->cmd;
	initCmd(node);
	while (token != NULL)
	{
		if (token->token_type == 'O') /* op */
		{
			if (parseOperators(f, node, token))
				printf("erno\n");//return (1); //erro apenas neste cmd 
			if (node->next)
				node = node->next;
			if (ft_strcmp(token->token_str, "|") != 0 && token->next)
				token = token->next;
		}
		else
			addStrCmd(node, token->token_str);
		token = token->next;
	}
	return (0);
}
