/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/06 14:14:09 by jdias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SYNTAX_ERR "minishell: syntax error near unexpected token"

typedef struct s_shell
{
	t_list	*cmds;
	char	**envp;
}			t_shell;

//env.c
char	*get_env(char *var, char **envp);
void	set_env(char *var, char *value, char **envp);

//mtr_utils.c
int		mtr_len(char **m);
void	free_mtr(char **m);
char	**mtr_dup(char **m);

//readline.c
char	*get_str(void);
char	*resolve_str(char	*line);
char	*get_prompt(void);

//signal.c
void sig_handler(int signal);
void handle_sig();

//main.c"
void	init_shell(int argc, char **argv, char **envp, t_shell *shell);

#endif
