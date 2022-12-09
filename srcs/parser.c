#include "../include/minishell.h"

/* caso <<*/
/*void	parseOpDsmaller(t_frame *f)
{
	
*/

void	printListCMD(t_cmd *head)
{
	int	i;

	i = 0;
	while (head != NULL)
	{
		while (head->full_cmd[i] != 0)
			printf("full cmd: %s, %i\n", head->full_cmd[i], i++);
		head = head->next;
	}
}

void append_dll_cmd(t_frame *f, t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = NULL;
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	//new_node->full_cmd = NULL;
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

int	charArrayLen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}

void	freeCmds(t_frame *f)
{
	int	i;

	i = 0;
	while (f->cmds->full_cmd[i] != 0)
		i++;
	while (i-- >= 0)
		free(f->cmds->full_cmd[i]);
	free(f->cmds->full_cmd);
}

void	addStrCmd(t_frame *f)
{
	char	**new_cmd;
	int	i;

	i = 0;
	exit(-1);
	if (f->cmds->full_cmd == NULL)
	{
		exit(-1);
		f->cmds->full_cmd = (char **)malloc(sizeof(char *) * 2);
		f->cmds->full_cmd[0] = ft_strdup(f->token->token_str);
		f->cmds->full_cmd[1] = 0;
		return ;
	}
	exit(-1);
	new_cmd = (char **)malloc(sizeof(char *) * (charArrayLen(f->cmds->full_cmd) + 1));
	while (f->cmds->full_cmd[i])
	{
		new_cmd[i] = ft_strdup(f->cmds->full_cmd[i]);
		i++;
	}
	new_cmd[i] = ft_strdup(f->token->token_str);
	new_cmd[i] = 0;
	free(f->cmds->full_cmd);
	f->cmds->full_cmd = new_cmd;
}

void	parseCmds(t_frame *f)
{
	f->cmds = NULL;
	append_dll_cmd(f, &(f->cmds));
	printf("wtf");
	exit(-1);
	while (f->token->next != NULL)
	{
		//case str
		exit(-1);
		while (f->token->token_type == 'N')
		{
			addStrCmd(f);
			f->token = f->token->next;
		}
		exit(-1);
		if (ft_strcmp(f->token->token_str, "|")) //case |
		{
			append_dll_cmd(f, &(f->cmds));
			f->cmds = f->cmds->next;
			f->token = f->token->next;
		}
	}	
	while (f->token->prev != NULL)
		f->token = f->token->prev;
	while (f->cmds->prev != NULL)
		f->cmds = f->cmds->prev;
	printListCMD(f->cmds);
}
