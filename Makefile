all:
	@gcc include/minishell.h libft/*.h libft/*.c srcs/*.c -lreadline -o minishell
	@echo "Compiled"
fclean:
	@rm -rf minishell

re: fclean all

e:
	@./minishell
