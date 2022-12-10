#include "../include/minishell.h"

/* da free aos **cmds/args */
/*void	freeCmds(t_frame *f)
{
	int	i;

	i = 0;
	while (f->cmds->full_cmd[i] != 0)
		i++;
	while (i-- >= 0)
		free(f->cmds->full_cmd[i]);
	free(f->cmds->full_cmd);
}*/

int	charArrayLen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

/* cria mais um node de cmd */
void append_dll_cmd(t_frame *f, t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->full_cmd = NULL;
	new_node->path = NULL;
	new_node->in_fd = 0;
	new_node->out_fd = 1;
	new_node->err_fd = 2;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

/* adiciona mais uma palavra ao cmd/args */
void	addStrCmd(t_frame *f)
{
	char	**new_cmd;
	int	i;

	i = 0;
	if (f->cmds->full_cmd == NULL)
	{
		f->cmds->full_cmd = (char **)malloc(sizeof(char *) * 2);
		f->cmds->full_cmd[0] = ft_strdup(f->token->token_str);
		f->cmds->full_cmd[1] = 0;
		return ;
	}
	new_cmd = (char **)malloc(sizeof(char *) * ((charArrayLen(f->cmds->full_cmd) + 2)));
	while (f->cmds->full_cmd[i])
	{
		new_cmd[i] = ft_strdup(f->cmds->full_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(f->token->token_str);
	new_cmd[++i] = 0;
	free(f->cmds->full_cmd);
	f->cmds->full_cmd = new_cmd;
}

/* se N adiciona ao cmd/args ate ao prox OP ou fim */
void	parseCmds(t_frame *f)
{
	append_dll_cmd(f, &(f->cmds));
	int	i = 0;
	while (f->token->next != NULL)
	{
		if (f->token->token_type == 'O' && ft_strcmp(f->token->token_str, "| "))
		{
			append_dll_cmd(f, &(f->cmds));
			f->cmds = f->cmds->next;
			i = 0;
			f->token = f->token->next;
			printf("fazer pipe\n");
		}
		else
		{
		addStrCmd(f);
		printf("cmd: %s\n", f->cmds->full_cmd[i]);i++;
		f->token = f->token->next;
		}
	}
	addStrCmd(f);
	printf("cmd: %s\n", f->cmds->full_cmd[i]);
}
