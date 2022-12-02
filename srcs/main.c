#include "../include/minishell.h"


//	netstat | grep tcp > file1
//define command table -> 0 | netstat | NULL
//			  1 | grep    | tcp | NULL
//			I/O | in: dflt | out:file1 | err: dflt 
void	ft_parser(t_mainf *main_f)
{
	int	i;

	i = 0;
	while (main_f->token_l[i] != NULL)
	{
		printf("%s\n", main_f->token_l[i]);
		i++;
	}
}

void	ft_tokenizer(t_mainf *main_f, char *line_r)
{
	main_f->token_l = ft_split(line_r, ' '); //tokenize input word by word
}

//READ-EVAL-PRINT-LOOP
//have a working history
void	ft_repl(t_mainf *main_f, char **env)
{
	char	*line_r;

	printf("\x1B[32m%s\x1b[0m", getenv("USER"));
	line_r = readline("\x1B[34m~\x1b[0m$ ");
	while (line_r != NULL)
	{
		ft_tokenizer(main_f, line_r);
		ft_parser(main_f);
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
