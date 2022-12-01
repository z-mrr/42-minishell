#include "../include/minishell.h"

void	mini_parser(char *lr)
{
	//history
	
	
}

void	mini_repl(char **env)
{
	char	*lr;

	printf("\x1B[32m%s\x1b[0m", getenv("USER"));
	lr = readline("\x1B[34m~\x1b[0m$ ");
	while (lr != NULL)
	{
		printf("\x1B[32m%s\x1b[0m", getenv("USER"));
		lr = readline("\x1B[34m~\x1b[0m$ ");
	}
}

int	main(int argc, char **argv, char **env)
{
	//start Read-Eval-Print-Loop
	mini_repl(env);
	//read_line -> parser -> executor

	//parser 
		//saves inputs in saved_commands file
		//divides input into commands and adjacent flags && args
	//executor
		//executes commands in order, 1 by 1, piping I/O if necessary 

	//break loop with "exit", "shutdown", "reboot";
}
