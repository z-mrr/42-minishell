#include "../include/minishell.h"

/*
void	mini_parser(char *lr)
{
	//	netstat | grep tcp > file1
	//define command table -> 0 | netstat | NULL
	//			  1 | grep    | tcp | NULL
	//			I/O | in: dflt | out:file1 | err: dflt 
	//handle word expansion -> ls *.c == ls 1.c 2.c 3.c (etc)	
}*/

//tokenize input (split into words) -> spaces, tabs, "" and '' | tokens must be known by the shell ?? 
void	ft_tokenize(char **env)
{
	execve("/bin/ls", NULL, env);
}

//READ-EVAL-PRINT-LOOP
//have a working history
void	ft_repl(char **env)
{
	char	*line_r;
	int	fork_id;

	printf("\x1B[32m%s\x1b[0m", getenv("USER"));
	line_r = readline("\x1B[34m~\x1b[0m$ ");
	while (line_r != NULL)
	{
		fork_id = fork();
		if (fork_id == 0)
			ft_tokenize(env);
		else
			kill(fork_id, 0);
		printf("\x1B[32m%s\x1b[0m", getenv("USER"));
		line_r = readline("\x1B[34m~\x1b[0m$ ");
	}
}

int	main(int argc, char **argv, char **env)
{
	//start Read-Eval-Print-Loop
	ft_repl(env);
	//parser 
		//saves inputs as commands history
		//divides input into commands and adjacent flags && args
	//executor
		//executes commands in order, 1 by 1, piping I/O if necessary 

	//break loop with "exit", "shutdown", "reboot";
}
