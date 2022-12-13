all:
	@gcc -ggdb -g -Wall include/minishell.h libft/*.h libft/*.c srcs/*.c -lreadline -o minishell
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
gdb:
	@valgrind --vgdb=yes --vgdb-error=0 ./minishell
fsanitize:
	@gcc -ggdb -fsanitize=address -g include/minishell.h libft/*.h libft/*.c srcs/*.c -lreadline -o minishell
argv:
	@valgrind ./minishell "fs f$se$<<|<\f<<|<< <<<wefwef $wefwef wf ew"
