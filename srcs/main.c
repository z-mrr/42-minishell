#include "../include/minishell.h"

void printList(t_token *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->token_str);
		head = head->next;
	}
}

void	ft_ll_append(t_token *head, char *s)
{
	t_token	*new_node;
	t_token	*last;

	new_node = (t_token *)malloc(sizeof(t_token));
	last = (t_token *)malloc(sizeof(t_token));
	new_node->token_str = ft_strdup(s);
	free(s);
	new_node->next = NULL;
	if (head == NULL)
	{
		head = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

int	ft_token_word(t_mainf *main_f, char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	/*if (s[i] != c)
		readline(">"); */ //add loop to readline until match if found
	ft_ll_append(main_f->token_f, ft_substr(s, 0, i));
	return (i);
}

//read input, tokenizing (split) by spaces except if single or double quote found
void	ft_tokenizer(t_mainf *main_f, char *line_r)
{
	int	i;
	int	wsize;

	i = 0;
	while (line_r[i] != '\0')
	{
		if (line_r[i] == '\"')
			wsize = ft_token_word(main_f, line_r + i + 1, '\"');
		/*else if (line_r[i] == '\'')
			wsize = ft_token_word(main_f, line_r[++i], '\'');
		else if(line_r[i] == ' ')
			wsize = ft_token_word(main_f, line_r[++i], ' ');*/
		printf("i = %i\n", i);
		i += wsize + 2;
		printf("i = %i\n", i);
	}
}

/*
READ-EVAL-PRINT-LOOP:
	->Loop between reading, tokenizing and executing | no
	-> have a working history | no
*/
void	ft_repl(t_mainf *main_f, char **env)
{
	char	*line_r;

	printf("\x1B[32m%s\x1b[0m", getenv("USER"));
	line_r = readline("\x1B[34m~\x1b[0m$ ");
	while (line_r != NULL)
	{
		ft_tokenizer(main_f, line_r);
		//printList(main_f->token_f);
		printf("\x1B[32m%s\x1b[0m", getenv("USER"));
		line_r = readline("\x1B[34m~\x1b[0m$ ");
	}
}

int	main(int argc, char **argv, char **env)
{
	//declare main frame
	t_mainf	*main_f;

	main_f = (t_mainf *)malloc(sizeof(t_mainf));

	//start Read-Eval-Print-Loop
	ft_repl(main_f, env);

	//parser 
		//divides input into commands and adjacent flags && args
	//executor
		//executes commands in order, 1 by 1, piping I/O if necessary 

	//break loop with "exit", "shutdown", "reboot";
}
