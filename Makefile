all:
	gcc include/minishell.h srcs/*.c -lreadline -o minishell

fclean:
	rm -rf minishell

re: fclean all
