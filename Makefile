all:
	gcc include/minishell.h srcs/main.c -lreadline -o minishell

fclean:
	rm -rf minishell

re: fclean all
