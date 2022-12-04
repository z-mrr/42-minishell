all:
	@gcc include/minishell.h libft/*.h libft/*.c srcs/*.c -lreadline -o minishell
	@echo "Compiled"
fclean:
	@rm -rf minishell

re: fclean all

val:
	@valgrind ./minishell
valtrack:
	@valgrind --track-origins=yes ./minishell
valleak:
	@valgrind --leak-check=full ./minishell
