#include "../include/minishell.h"

/* criar cms struct, se for para child chama fork*/

typedef struct s_node {
	struct s_cmd *cmds;
	struct s_node *next;  //separa por |
} t_node;


/* caso <<*/
void	parseOpDsmaller(t_frame *f)
{
	
}


void	parseCmds(t_frame *f)
{
	t_node
	while (f->token->next != NULL)
	{
		//case <<
		if (f->token->token_type == 'O' && f->token->token_str[1] == 60)
			parseOpDsmaller(f);
		//case < 
		//case >
		//case >>
		f->token = f->token->next;
	}	
	while (f->token->prev != NULL)
		f->token = f->token->prev;
}
