/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdias-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 11:42:14 by jdias-mo          #+#    #+#             */
/*   Updated: 2022/12/07 22:04:56 by jdias-mo         ###   ########.fr       */
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

typedef struct	s_sh
{
	t_list	*cmds;//lista de nodes t_cmd, novo node a cada pipe
	char	**envp;//duplicado de **envp
}				t_sh;

typedef struct	s_cmd
{
	char	**args;//comando e argumentos
	char	*path;//path do comando a executar no caso de nao ser um builtin
	int		in;//default se nao houver redirect/pipe
	int		out;//default se nao houver redirect/pipe
}				t_cmd;

//env.c
char	*get_env(char *var, t_sh *sh);
int		pos_env(char *var, char **envp);
void	set_env(char *var, char *value, t_sh *sh);
void	rmv_env(char *var, t_sh *sh);

//mtr.c
int		mtr_len(char **m);
void	mtr_free(char **m);
char	**mtr_dup(char **m);
char	**mtr_rmv(int pos, char **old);
char	**mtr_add(char *str, char **old);

//readline.c
char	*get_str(void);
char	*resolve_str(char	*line);
char	*get_prompt(void);

//signal.c
void sig_handler(int signal);
void handle_sig();

//main.c"
void	init_sh(int argc, char **argv, char **envp, t_sh *sh);

#endif
