#include "../include/minishell.h"

/*
void	mini_parser(char *lr)
{
	//	netstat | grep tcp > file1
	//define command table -> 0 | netstat | NULL
	//			  1 | grep    | tcp | NULL
	//			I/O | in: dflt | out:file1 | err: dflt 
}*/

//READ-EVAL-PRINT-LOOP
//have a working history
void	ft_repl(t_mainf *main_f, char **env)
{
	char	*line_r;

	printf("\x1B[32m%s\x1b[0m", getenv("USER"));
	line_r = readline("\x1B[34m~\x1b[0m$ ");
	while (line_r != NULL)
	{
		main_f->token_l = ft_split(line_r, ' '); //tokenize input word by word
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
